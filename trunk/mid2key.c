#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wordexp.h>

#include <alsa/seq_event.h>
#include <alsa/seq_midi_event.h>
#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>

int main(int argc, char** argv)
{
    /*defines*/
    Display* xdp;
    FILE* midi;
    FILE* config;
    const char* file;
    KeyCode map[128];
    char buffer[128];
    char* keysym;
    int temp;
    snd_midi_event_t* parser;
    snd_seq_event_t event;
    wordexp_t file_expanded;

    /*usage*/
    if ((argc != 2) && (argc != 3)) {
        fprintf(stderr,"Usage: %s device [config]\n"
                       "Defaults to ~/.mid2key if config is unspecified.\n"
                       "Configuration example:\n"
                       "#set note #32 to spacebar\n"
                       "32=space\n"
                       "#set note #33 to keycode 67\n"
                       "33=67\n"
                       "#leave note #34 unset\n"
                       "34=\n"
                       "#also set note 35 to space\n"
                       "35=space\n"
                ,*argv);
        return 1;
    }

    /*display*/
    if (!(xdp = XOpenDisplay(getenv("DISPLAY")))) {
        fputs("Unable to open X display.",stderr);
        return 2;
    }

    /*config*/
    if (argc == 3) {
        file = argv[2];
    } else {
        file = "~/.mid2key";
    }
    wordexp(file, &file_expanded, 0);
    memset(map,0,sizeof(map));
    if (!(config = fopen(file_expanded.we_wordv[0],"r"))) {
        fprintf(stderr,"Unable to open configuration file '%s'\nUsing null mapping.\n",file);
    } else {
        while (fgets(buffer,128,config)) {
            if (*buffer != '#') {
                if ((keysym = strchr(buffer,'='))) {
                    temp = atoi(buffer);
                    if ((temp >= 0) && (temp <= 127)) {
                        ++keysym;
                        if (strchr(keysym,'\n')) *strchr(keysym,'\n') = '\0';
                        if ((map[temp] = XStringToKeysym(keysym))) {
                            if (!(map[temp] = XKeysymToKeycode(xdp,map[temp])))
                                fprintf(stderr,"No keycode for keysym '%s'\n",keysym);
                        } else if (*keysym) {
                            fprintf(stderr,"Undefined keysym '%s'\n",keysym);
                        }
                    }
                }
            }
        }
        fclose(config);
    }

    /*midi*/
    if (!(midi = fopen(argv[1],"rb"))) {
        fprintf(stderr,"Unable to open MIDI device '%s'\n",argv[1]);
        XCloseDisplay(xdp);
        return 3;
    }
    snd_midi_event_new(32,&parser);
    /*feed implied note on message*/
    snd_midi_event_encode_byte(parser,0x9A,&event);
    
    /*main loop*/
    fputs("Ready for midi input\n",stderr);
    while ((temp = fgetc(midi)) != EOF) {
        if (snd_midi_event_encode_byte(parser, temp, &event) == 1) {
            if (event.type == SND_SEQ_EVENT_NOTEON) {
                if ((event.data.note.note <= 127) && (event.data.note.velocity)) {
                    if ((temp = map[event.data.note.note])) {
                        XTestFakeKeyEvent(xdp,temp,1,CurrentTime);
                        XTestFakeKeyEvent(xdp,temp,0,CurrentTime);
                        XFlush(xdp);
                    }
                    printf("%i->%i\n",event.data.note.note,(int)map[event.data.note.note]);
                }
            }
        }
    }

    /*cleanup*/
    snd_midi_event_free(parser);
    fclose(midi);
    return 0;
}
