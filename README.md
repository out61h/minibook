# Minibook

Minibook is a text-to-image converter, written by Konstantin Polevik in C++.

## About the Project

Minibook can be used to read books on dumb cellphones that does not have a text reader, but has a built-in image viewer.

Minibook can beautifully format text and wrap words but optimized primarily for Cyrillic and English texts.

![Sample](./doc/sample.jpg)

## Dependencies
- Anti-Grain Geometry library
- FreeType library
- libpng library (optional)
- Niels Lohmann's JSON library
- STB_image library

## Building

## Usage

## TODO
```
- [ ] More Doxygen-style comments
- [ ] Support CR for line termination
- [ ] Use STL for working with Unicode
- [ ] Turn on and fix more compiler warnings
- [ ] More platform and compilers support
- [ ] Remove AGG inclusions from headers (using Pimpl?)
- [ ] Resolve TODO comments in code
- [ ] Replace non-printable symbols by whitespaces in input stream
- [ ] Imrove LineUnwrapper's logic
