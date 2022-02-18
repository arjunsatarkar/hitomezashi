# Hitomezashi

Library and CLI app to generate hitomezashi patterns like the following:

<img src="https://raw.githubusercontent.com/untir-l/hitomezashi/main/sample.png" alt="sample hitomezashi pattern" width="500" height="500">

Inspired by [Numberphile's video](https://www.youtube.com/watch?v=JbfhzlMk2eY) on hitomezashi stitch patterns.

Written in C11 with SDL2. Code style: whatever clang-format outputs.

Licensed under GPLv2 (see `LICENSE` file for full text). This project's source code is copyright © 2022-present Arjun Satarkar and potentially other future contributors.

## Usage

`hitomezashi.c` and `hitomezashi.h` are the library portion; running `make` will build `libhitomezashi.a` from these. See `hitomezashi_cli.c` for an example of how to use it (all relevant code is in `main()`; most of the rest of the file is cumbersome argument parsing).

`hitomezashi_cli.c` and corresponding header file are the CLI app. `make` will build it; run `./hitomezashi_cli -h` for help.

Output of the CLI app is a BMP image; you can convert it to something nicer like a PNG with FFmpeg or similar.

Additionally, the output is black and white - you can replace these colours using your tool of choice if desired.

## Todos/potential future additions
- Add documentation using Doxygen to both the library and CLI app
- Implement nicer argument parsing (I hear there are some nice Rust libraries for this; maybe rewrite the CLI app in that?)
- Add support for output to PNG/other formats to the CLI app
- Add support for choosing foreground and background colours
