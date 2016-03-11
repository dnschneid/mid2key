LDFLAGS=-Wall
LDLIBS=-lX11 -lXtst -lasound
mid2key: mid2key.c
clean: 
	rm -f mid2key
