# Minibook

Minibook is a text-to-image converter, written by Konstantin Polevik in C++.

## About the Project

Minibook can be used to read books on dumb cellphones that does not have a text reader, but has a built-in image viewer.

Minibook can beautifully format text and wrap words but optimized primarily for Cyrillic and English texts.

![Sample](./doc/sample.jpg)

## Dependencies

- [Anti-Grain Geometry library](https://github.com/ghaerr/agg-2.6)
- [FreeType library](http://freetype.org)
- [libpng library](http://www.libpng.org/pub/png/libpng.html) (optional)
- [Niels Lohmann's JSON library](https://github.com/nlohmann/json)
- [STB library](https://github.com/nothings/stb)
- [DroidSans font](https://fonts.adobe.com/fonts/droid-sans)

## Building

### Windows

Brief:
1. Install Windows SDK, Build Tools for Visual Studio
2. Install CMake
3. Download, build and install dependencies
4. Clone or export Minibook repo
5. Configure project with CMake
6. Build project with CMake

## Usage

1. Prepare text file (e.g. `book.txt`). It should be in UTF-8 encoding with BOM ([Byte Order Mark](https://en.wikipedia.org/wiki/Byte_order_mark))
2. Export default conversion parameters to JSON config file by using `--config` option:
```
Minibook --config=param.json 
```
3. Inspect JSON config file and adjust parameters values
4. Convert text to a set of images:
```
Minibook --config=param.json book.txt
```
5. Found the pictures in the directory `book`. You can direct set output directory name (e.g. `export`) by using option `--output`:
```
Minibook --config=param.json --output=export book.txt
```
6. Connect cell phone to computer via USB cable. Set connection mode to access phone filesystem. Copy directory with pictures to a phone `Photos` folder. 

### Notes

- Some phones support only JPEG images. Some others don't support nested folders in `Photos` directory. So you might have to adjust appropriate  arameters in JSON config.
- By default, Minibook uses `DroidSans.ttf` font for text rendering. You should download and place `DroidSans.ttf` to Minibook binary file location folder.

## TODO

```
- [ ] Update CMakeLists.txt
- [ ] Imrove LineUnwrapper's logic
- [ ] Fix wrong color components?
- [ ] Add detailed building instruction
- [ ] More Doxygen-style comments
- [ ] Support CR for line termination
- [ ] Use STL for working with Unicode
- [ ] Turn on and fix more compiler warnings
- [ ] More platform and compilers support
- [ ] Remove AGG inclusions from headers (using Pimpl?)
- [ ] Resolve TODO comments in code
- [ ] Replace non-printable symbols by whitespaces in input stream
- [ ] Add clang-tidy config
- [ ] Copy libpng binary files to binary output directory
