.POSIX:

CC = gcc
CFLAGS = -std=c11 -Wall -Wno-unused-function --pedantic-errors -O3 `sdl2-config --cflags` -I./lib/
LDLIBS = `sdl2-config --libs`
AR = ar
ARFLAGS = rcs

all: libhitomezashi.a hitomezashi_cli

libhitomezashi.a: hitomezashi.o
	$(AR) $(ARFLAGS) libhitomezashi.a hitomezashi.o

hitomezashi.o: lib/hitomezashi.c lib/hitomezashi.h
	$(CC) -c $(CFLAGS) lib/hitomezashi.c

hitomezashi_cli: hitomezashi_cli.o libhitomezashi.a
	$(CC) $(LDFLAGS) $(LDLIBS) -o hitomezashi_cli hitomezashi_cli.o libhitomezashi.a

hitomezashi_cli.o: cli/hitomezashi_cli.c cli/hitomezashi_cli.h
	$(CC) -c $(CFLAGS) -o hitomezashi_cli.o cli/hitomezashi_cli.c

format-code:
	clang-format -i --verbose **/*.c **/*.h

clean:
	rm -f *.a *.o hitomezashi_cli
