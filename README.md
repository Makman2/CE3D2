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

To install CE3D2, just type:

```
./make.sh install release
```

If you only want to install CE3D2, you don't need to build it even via
`./make.sh release`, the installation command does that automatically for you.

> **NOTE**
>
> The library is installed to */usr/local/lib/*. Some platforms don't have this
> path inside the environment variables so execution of programs using CE3D2
> result in a load-failure. This can be fixed often by modifying
> */etc/ld.so.conf* adding */usr/local/lib/*. Refer to the help of your
> platform.

## Documentation

HTML-documentation can be built easily with `./make.sh doc` into `build/doc`. To
display the documentation webpage, invoke your favorite browser with
`build/doc/html/index.html`.

CE3D2 uses doxygen to generate documenation.

## Debugging

If you want to debug CE3D2, you need to invoke `./make.sh debug` instead of
`./make.sh release`. The debug library is then located inside `build/debug`.

To install the debug libraries, pass `debug` instead of `release` to the install
target: `./make.sh install debug`

If you want to see all "build targets" of the make-script, type
`./make.sh help`.
