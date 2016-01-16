# Getting Started - Part 1 - Example code

This is the full code file from the first tutorial that renders 2D points.

## Build

You can build it via `g++` with

```
g++ -std=c++11 -lCE3D2 example2d.cpp -o example2d
```

and execute it with `./example2d`.

## example2d.cpp

```cpp
#include <iostream>
#include <memory>

#include <CE3D2/models/Model.h>
#include <CE3D2/render/TextRenderer.h>
#include <CE3D2/render/TextSurface.h>
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
    auto rectangle = std::make_shared<Models::Model>();
    auto& vectors = rectangle->vectors();

    vectors.push_back(create_2d_vector(0.0f, 0.0f));
    vectors.push_back(create_2d_vector(20.0f, 0.0f));
    vectors.push_back(create_2d_vector(20.0f, 5.0f));
    vectors.push_back(create_2d_vector(0.0f, 5.0f));

    Render::TextRenderer renderer;
    renderer.set_target(std::make_shared<Render::TextSurface>(40, 10));
    renderer.models().push_back(rectangle);

    renderer.render();
    print_textsurface(*renderer.get_target());

    return 0;
}
```
