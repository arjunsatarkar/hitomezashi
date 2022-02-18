# Hitomezashi

Library and CLI app to generate hitomezashi patterns like the following:

<img src="https://raw.githubusercontent.com/untir-l/hitomezashi/main/sample.png" alt="sample hitomezashi pattern" width="500" height="500">

Inspired by [Numberphile's video](https://www.youtube.com/watch?v=JbfhzlMk2eY) on hitomezashi stitch patterns.

Written in C11 with SDL2. Code style: whatever clang-format outputs.

Licensed under GPLv2 (see `LICENSE` file for full text). This project's source code is copyright © 2022-present Arjun Satarkar, except code contributed by others who retain their copyright.

## Usage

### libhitomezashi

This is in the `lib/` directory. For example usage, see the Hitomezashi CLI source (all the relevant code is in `main()`; most everything outside that is cumbersome argument parsing).

Running `make` in the project root will build this as `libhitomezashi.a`.

### Hitomezashi CLI

This is in the `cli/` directory. It is built by default when `make` is invoked in the project root. Run `./hitomezashi_cli -h` for usage info.

The output of the CLI app is a BMP image; you can convert it to something nicer like a PNG with FFmpeg or similar.

Additionally, the output is black and white - you can replace these colours using your tool of choice if desired.

## Todos/potential future additions
- Make a web app version
- Add support for output to PNG/other formats to the CLI app
- Add support for choosing foreground and background colours
