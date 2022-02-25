.POSIX:

CFLAGS = -std=c11 -Wall -Wno-unused-function --pedantic-errors -O3 `sdl2-config --cflags`
LDLIBS = `sdl2-config --libs`

ARFLAGS = rcs

all:

libhitomezashi.a: hitomezashi.o hitomezashi_utils.o
	$(AR) $(ARFLAGS) libhitomezashi.a hitomezashi.o hitomezashi_utils.o
hitomezashi.o: lib/hitomezashi.c lib/hitomezashi.h
	$(CC) -c $(CFLAGS) lib/hitomezashi.c
hitomezashi_utils.o: lib/hitomezashi_utils.c lib/hitomezashi_utils.h
	$(CC) -c $(CFLAGS) lib/hitomezashi_utils.c


hitomezashi_cli: hitomezashi_cli.o libhitomezashi.a
	$(CC) $(LDFLAGS) $(LDLIBS) -o hitomezashi_cli hitomezashi_cli.o libhitomezashi.a
hitomezashi_cli.o: cli/hitomezashi_cli.c cli/hitomezashi_cli.h
	$(CC) -c $(CFLAGS) -I./lib/ -I./cli/optparse/ -o hitomezashi_cli.o cli/hitomezashi_cli.c


hitomezashi_web.html: web/hitomezashi_web_shell.html hitomezashi_web.o libhitomezashi.a
	$(CC) $(LDFLAGS) $(LDLIBS) -O3 -s MINIFY_HTML=0 --shell-file ./web/hitomezashi_web_shell.html -o hitomezashi_web.html hitomezashi_web.o libhitomezashi.a
hitomezashi_web.o: web/hitomezashi_web.c web/hitomezashi_web.h
	$(CC) -c $(CFLAGS) -I./lib/ web/hitomezashi_web.c

format-code:
	clang-format -i --verbose **/*.c **/*.h

clean:
	rm -f *.a *.o *.js *.wasm *.html hitomezashi_cli
