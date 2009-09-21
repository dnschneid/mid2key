mid2key
=======

*Note: this program is really old, and is mainly here for archival purposes. It may or may not work.*

Small GNU/Linux program that captures live midi input (a device like /dev/midi1 ) and maps the notes to simulated key presses.
The map is set by a simple config file.

Requires X11 with the XTest extension and alsa.

Installation
------------

### From source

  * Make sure you have the X11 and alsa development files (libx11-dev and libasound2-dev in some distributions' repositories)
  * Download source from the download tab, extract somewhere.
  * Using the console, cd into the directory and run make
  * If nothing goes wrong, you should be able to run the application

### From binary

  * Make sure you have alsa installed (libasound2 in some repositories)
  * Extract the binary from the download page to a directory.
  * Make executable if necessary.
  * Run.

### Example usage

`./mid2key /dev/midi1 fofixdrums`

Where /dev/midi1 is the midi device, and fofixdrums is the path to the config file.

### Example config file

```
#set note #32 to spacebar
32=space
#set note #33 to keycode 67
33=67
#leave note #34 unset
34=
#also set note 35 to space
35=space
```

License
-------

This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to http://unlicense.org/
