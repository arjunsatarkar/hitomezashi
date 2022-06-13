# Hitomezashi

A small learning project to produce a form of generative art, hitomezashi patterns.

Here is an example of one such pattern generated using this tool:

<img src="https://raw.githubusercontent.com/untir-l/hitomezashi/main/sample.png" alt="sample hitomezashi pattern" width="500" height="500">

## What are hitomezashi patterns?

Consider a series of dashed lines, with alternating dashes and spaces of equal length. Let some number of these dashed lines emanate from the X axis, and some from the Y axis.

Now, assign a binary number to each of the lines on each axis. If the number is 0, let the first part of the line that is touching the axis be a dash, and the second a space. If the number is 1, offset the dashed line by one part so it begins with a space, followed by a dash.

The result is a hitomezashi pattern.

For video explanation and to see one drawn to paper, check out [the video that inspired this project](https://www.youtube.com/watch?v=JbfhzlMk2eY).

Hitomezashi patterns originated in Japan as a form of stitching. Thinking about the patterns as stitching helps explain the presence of what we approximate as dashed lines.

## Building and usage

### Building to native code

To build the core logic as a static library, run `CC=gcc make libhitomezashi.a`.
To build a CLI app exposing this logic, run `CC=gcc make hitomezashi_cli` and see
`./hitomezashi_cli -h` for usage info.

### Building for the Web

<img src="https://github.com/untir-l/hitomezashi/blob/main/screenshot_web.png?raw=true" width="500">

To build, first run `make clean` if you previously built to native code, then (with Emscripten SDK in your PATH) run `emmake make hitomezashi_web.html`.
Serve `hitomezashi_web.html`, `hitomezashi_web.js`, and `hitomezashi_web.html.wasm` from a web server to use the web app.

## Technical and copyright information

Written in C11 with SDL2, with some JavaScript in the web app.

Licensed under GPLv2 (see `LICENSE` file for full text). This project's source code is copyright © 2022-present Arjun Satarkar.
