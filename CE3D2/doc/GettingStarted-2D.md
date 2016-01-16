# Getting Started - Part 1

This is a little guide that introduces into CE3D2. It covers both, 2D and 3D
graphics. Since 3D-graphics build upon the stuff of 2D-graphics, we start with
2D drawing.

## 2D rendering

CE3D2 does not use a pipeline system (so a single class that is responsible for
nearly everything regarding 3D where several steps are performed), so it's up to
you to create the "vector-data-flow". But this allows great flexibility inside
your application.

### Step 1: Set up a model

A model contains a bunch of vectors that make up your mesh. So let's define a
simple 2D geometry first:

```cpp
#include <CE3D2/models/Model.h>
#include <CE3D2/Vector.h>

using namespace CE3D2;

// Let's create a little helper function for instantiating vectors, since
// initializer lists are not supported from CE3D2::Vector. The issue is already
// addressed in https://github.com/Makman2/CE3D2/issues/52.
Vector create_2d_vector(float x, float y)
{
    Vector v(2);
    v[0] = x;
    v[1] = y;
    return v;
}

int main()
{
    Models::Model rectangle;
    auto& vectors = rectangle.vectors();

    vectors.push_back(create_2d_vector(0.0f, 0.0f));
    vectors.push_back(create_2d_vector(20.0f, 0.0f));
    vectors.push_back(create_2d_vector(20.0f, 5.0f));
    vectors.push_back(create_2d_vector(0.0f, 5.0f));

    return 0;
}
```

So what we have done? We declared and instantiated a new `Model` that shall hold
our geometry. Then we fill it up with vectors that make up a rectangle.

You can compile this already with `g++` and execute using the commands

```
g++ -std=c++11 -lCE3D2 <your-file.cpp> -o <output-name>
./<output-name>
```

Replace `<your-file.cpp>` with the filename where you stored the cpp-file and
`<output-name>` with the name of the binary that shall be generated.

### Step 2: Bring the renderer into play

In fact we can already render that, so let's include the actual renderer!

```cpp
#include <memory>

#include <CE3D2/models/Model.h>
#include <CE3D2/render/TextRenderer.h>
#include <CE3D2/render/TextSurface.h>
#include <CE3D2/Vector.h>

// ...

int main()
{
    // ...
    vectors.push_back(create_2d_vector(0.0f, 5.0f));

    Render::TextRenderer renderer;
    renderer.set_target(std::make_shared<Render::TextSurface>(40, 10));

    return 0;
}
```

Now we instantiated a `TextRenderer`, this class is responsible for bringing our
vectors into a textual representation. The rendered output is stored inside a
`TextSurface` that is efficiently a 2-dimensional char-array. In this case the
surface is 40 pixels wide and 20 pixels high. This is the screen for our
renderer where it paints on.

Why the model is not added already? As you see the renderer works on
*shared resources*. That's why we utilize `std::make_shared()` that creates an
`std::shared_ptr` for us that allows to manage the surface from different code
locations. The same needs to be done for the model, so we modify the code a bit:

```cpp
// ...

int main()
{
    // Make a shared_ptr...
    auto rectangle = std::make_shared<Models::Model>();
    // and now use operator `->` (instead of `.`) to dereference it:
    auto& vectors = rectangle->vectors();

    vectors.push_back(create_2d_vector(0.0f, 0.0f));
    vectors.push_back(create_2d_vector(20.0f, 0.0f));
    vectors.push_back(create_2d_vector(20.0f, 5.0f));
    vectors.push_back(create_2d_vector(0.0f, 5.0f));

    Render::TextRenderer renderer;
    renderer.set_target(std::make_shared<Render::TextSurface>(40, 10));
    // Now set the model for the renderer!
    renderer.models().push_back(rectangle);

    return 0;
}
```

### Step 3: Printing to console

Well done! Let's bring it into our console!

```cpp
#include <iostream>
#include <memory>

// ...

// TextSurface does not contain a function that prints out the contents to
// console. Already addressed in https://github.com/Makman2/CE3D2/issues/51.
void print_textsurface(Render::TextSurface const& surf)
{
    for (unsigned int y = 0; y < surf.height(); y++)
    {
        for (unsigned int x = 0; x < surf.width(); x++)
        {
            std::cout << surf(x, y);
        }
        std::cout << std::endl;
    }
}

int main()
{
    // ...

    Render::TextRenderer renderer;
    renderer.set_target(std::make_shared<Render::TextSurface>(40, 10));
    // Now set the model for the renderer!
    renderer.models().push_back(rectangle);

    renderer.render();
    print_textsurface(*renderer.get_target());

    return 0;
}
```

Nice! Now you should see something like this (4 little dots) on your console
when compiling and running your program.

```
.                   .




.                   .
```

So we have already brought something from a model to a renderer and printed
that onto the console.
