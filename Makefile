.POSIX:

CC = gcc
CFLAGS = -std=c11 -Wall -Wno-unused-function --pedantic-errors -O3 `sdl2-config --cflags`
LDLIBS = `sdl2-config --libs`
AR = ar
ARFLAGS = rcs

all: libhitomezashi.a hitomezashi_cli

libhitomezashi.a: hitomezashi.o
	$(AR) $(ARFLAGS) libhitomezashi.a hitomezashi.o

hitomezashi.o: hitomezashi.c hitomezashi.h

hitomezashi_cli: hitomezashi_cli.o libhitomezashi.a

hitomezashi_cli.o: hitomezashi_cli.c hitomezashi_cli.h

format-code:
	clang-format -i --verbose *.c *.h

clean:
	rm -f *.a *.o hitomezashi_cli
