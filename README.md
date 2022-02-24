# Hitomezashi

Library, CLI and web app to generate hitomezashi patterns. These are an example of visually complex and structured patterns arising from simple rules.

Here is an example of such a pattern:

<img src="https://raw.githubusercontent.com/untir-l/hitomezashi/main/sample.png" alt="sample hitomezashi pattern" width="500" height="500">

## What is the pattern?

Consider a series of dashed lines, with alternating dashes and spaces of equal length. Let some number of these dashed lines emanate from the X axis, and some from the Y axis.

Now, assign a binary number to each of the lines on each axis. If the number is 0, let the first part of the line that is touching the axis be a dash, and the second a space. If it is 1, offset the dashed line by one part so it begins with a space, followed by a dash.

The result is a hitomezashi pattern.

For video explanation and to see one drawn to paper, check out [the video that inspired this project](https://www.youtube.com/watch?v=JbfhzlMk2eY).

Hitomezashi patterns originated in Japan as a form of stitching. Thinking about the patterns as stitching helps explain the presence of what we approximate as dashed lines.

## Building and usage

### libhitomezashi

This is in the `lib/` directory. For example usage, see the Hitomezashi CLI source (all the relevant code is in `main()`; most everything outside that is cumbersome argument parsing).

libhitomezashi can be compiled to WebAssembly for use on the web.

To build, run `CC=gcc make libhitomezashi.a`.

### Hitomezashi CLI

This is in the `cli/` directory. Run `./hitomezashi_cli -h` for usage info.

The output of the CLI app is a BMP image as this is supported by default in SDL2; this will change eventually to output PNGs since BMP is an antiquated format. For now, you can convert using FFmpeg or similar.

To build, run `CC=gcc make hitomezashi_cli`.

### Hitomezashi Web App

Try it: *link pending upload*.

To build, first run `make clean` if you previously built to native code, then (with Emscripten SDK in your PATH) run `emmake make hitomezashi_web.html`.

You will need to serve, from a web server: `hitomezashi_web.html`, `hitomezashi_web.js`, `hitomezashi_web.wasm` in order for it to work; the `file://` protocol may not cut it. Remember to follow the terms of the terms of the license if you host these publicly.

## Technical and copyright information

Written in C11 with SDL2. Code style: `make format-code` will run `clang-format` with the correct parameters.

Licensed under GPLv2 (see `LICENSE` file for full text). This project's source code is copyright © 2022-present Arjun Satarkar, except code contributed by others who retain their copyright.

## Todos/potential future additions
- Add support for output to PNG/other formats to the CLI app
- Add support for choosing foreground and background colours
