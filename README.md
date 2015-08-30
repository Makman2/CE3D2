# CE3D2

**C**onsole **E**ngine **3D** 2.
A simple 3D engine for the console.

## About

You ever wanted 3D ASCII graphics inside your terminal? CE3D2 is the solution!

## Build

Clone this repository, cd into and build it!

```
git clone https://github.com/Makman2/CE3D2
cd CE3D2
./make.sh release
```

The libary is located inside the `build/release` directory.

To build CE3D2 you need:
- a C++11 compiler
- Boost
- CMake

CE3D2 is only supported on linux platforms.

## Installation

Installation to the system is currently not supported, but will come shortly.

## Debugging

If you want to debug CE3D2, you need to invoke `./make.sh debug` instead of
`./make.sh release`. The debug library is then located inside `build/debug`.

If you want to see all "build targets" of the make-script, type
`./make.sh help`.
