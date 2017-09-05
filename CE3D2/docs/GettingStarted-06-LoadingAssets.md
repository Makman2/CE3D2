# Getting Started - Part 6

## Loading Assets

CE3D2 provides some minimal asset loading capabilities.

### Loading Models

You can load Wavefront-OBJ-files with CE3D2 (generated for example with
*blender*). Just include the header:

```cpp
#include <CE3D2/models/loaders/WavefrontObj.h>
```

... and use it:

```cpp
auto models = Models::Loaders::load_wavefront_obj("your-model-file.obj");
```

As Wavefront-OBJ-files can hold multiple models, a list of them is returned.

Loading functions also accept streams instead of files.

### Being Smarter

Depending on the file extension of your stored assets, CE3D2 can handle loading
them automatically for you by picking the right asset loading function. Change
your code to 

```cpp
// This imports "all" available asset loaders of CE3D2.
#include <CE3D2/models/loaders/All.h>

// Automatically calls Models::Loaders::load_wavefront_obj(), because
// .obj-files are associated to Wavefront-OBJ-files.
auto models = Models::Loaders::load("your-model-file.obj");
```

Currently only Wavefront-OBJ-files (`.obj`) are supported, but this is the
recommended way of loading assets, as you don't have to deal with specific
asset importing code.
