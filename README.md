# CE3D2

**C**onsole **E**ngine **3D** 2.
A simple 3D engine for the console.

## About

CE3D2 is a leightweight 3D engine specifically designed for rendering
ASCII-art. Since it's not using heavy graphic pipelines and utilizes CPU only,
the vector arithmetic is very flexible.

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
> */etc/ld.so.conf* adding */usr/local/lib/* and executing `ldconfig` with
> elevated privileges. Refer to the help of your platform.

## Usage

After install you can use CE3D2 normally like any other library:

```cpp
#include <CE3D2/Vector.h>

int main()
{
    CE3D2::Vector vec;
    // Do fancy vector stuff.
    return 0;
}
```

Don't forget to link against CE3D2 and use C++11 (in `g++` use the flags
`-lCE3D2` and `-std=c++11`). Also you need Boost installed, since vector and
matrix arithmetic is performed using it.

## Documentation

HTML-documentation can be built easily with `./make.sh doc` into `build/doc`. To
display the documentation webpage, invoke your favorite browser with
`build/doc/html/index.html`.

CE3D2 uses doxygen (version 1.8.8 and above required) to generate documentation.
If you want to see the actual rendered formulas, you also need latex.

## Debugging

If you want to debug CE3D2, you need to invoke `./make.sh debug` instead of
`./make.sh release`. The debug library is then located inside `build/debug`.

To install the debug libraries, pass `debug` instead of `release` to the install
target: `./make.sh install debug`

If you want to see all "build targets" of the make-script, type
`./make.sh help`.
