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

**Note**: Some phones support only JPEG images. Some others don't support nested folders in `Photos` directory. So you might have to adjust appropriate  arameters in JSON config.

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
- [ ] Add clang-tidy config
