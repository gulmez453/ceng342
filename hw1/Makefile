CC=gcc
CFLAGS=-I.
DEPS = hellomake.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

18050171001: 18050171001.o hellofunc.o 
	$(CC) -o 18050171001 18050171001.o hellofunc.o 
