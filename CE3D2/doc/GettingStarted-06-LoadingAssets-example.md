# Getting Started - Part 6 - Example code

This is an example for the 6th tutorial that imports and renders an asset.

## Build

You can build it via `g++` with

```
g++ -std=c++11 -lCE3D2 example-asset.cpp -o example-asset
```

and execute it with `./example-asset`.

## example-asset.cpp

```cpp
#include <iostream>
#include <memory>

#include <CE3D2/models/loaders/WavefrontObj.h>
#include <CE3D2/render/TextRenderer.h>
#include <CE3D2/render/TextSurface.h>
#include <CE3D2/transformation/OrthogonalProjection.h>
#include <CE3D2/transformation/Scale.h>
#include <CE3D2/transformation/Translation.h>
#include <CE3D2/Vector.h>

using namespace CE3D2;


int main(int argc, char* argv[])
{
    // OBJ-files can contain multiple models. However, the example only
    // contains a single model.
    auto model = Models::Loaders::load_wavefront_obj("octagon.obj")[0];

    // Do the already known part: Set up the necessary projection matrices to
    // bring the model onto the screen nicely.

    // Set up view and projections.
    Transformation::OrthogonalProjection ortho_projection;
    std::vector<Vector> projection_vecs;
    projection_vecs.push_back(create_vector(0.7f, 0.3f, 0.0f));
    projection_vecs.push_back(create_vector(0.0f, 0.3f, 0.7f));
    ortho_projection.set_projection_vectors(projection_vecs);

    auto translation = Transformation::Translation(create_vector(20.0f, 20.0f));

    // Used to compensate the fact that chars in terminals are twice as high
    // than broad.
    auto screenscale = Transformation::Scale(create_vector(2.0f, 1.0f));

    // Transform model.
    model->transform(Transformation::Scale(ScalarVector(3, 3.0f)));
    model->transform(ortho_projection);
    model->transform(translation);
    model->transform(screenscale);

    // Render.
    Render::TextRenderer renderer;
    renderer.set_target(std::make_shared<Render::TextSurface>(80, 40));
    renderer.line_models().push_back(model);
    renderer.render();
    std::cout << *renderer.get_target();

    return 0;
}
```

## octagon.obj

```
o Octagon
v 0.000000 -1.000000 -3.415228
v 0.000000 1.000000 -3.415228
v 2.414931 -1.000000 -2.414931
v 2.414931 1.000000 -2.414931
v 3.415228 -1.000000 0.000000
v 3.415228 1.000000 0.000000
v 2.414931 -1.000000 2.414931
v 2.414931 1.000000 2.414931
v -0.000000 -1.000000 3.415228
v -0.000000 1.000000 3.415228
v -2.414932 -1.000000 2.414931
v -2.414932 1.000000 2.414931
v -3.415228 -1.000000 -0.000000
v -3.415228 1.000000 -0.000000
v -2.414932 -1.000000 -2.414931
v -2.414932 1.000000 -2.414931
f 1 2 4 3
f 3 4 6 5
f 5 6 8 7
f 7 8 10 9
f 9 10 12 11
f 11 12 14 13
f 4 2 16 14 12 10 8 6
f 13 14 16 15
f 15 16 2 1
f 1 3 5 7 9 11 13 15
```

## Output

```
                                        ____
                                    ___/  \_\_______
                                ___/        \_      \_____
                             __/            __\_____      |_
                         ___/           ___/        \_____\ \_
                      __/            __/                   \___
                     /\_         ___/                       |  \
                    /   \_   ___/                           \   |
                   /      \_/                                |  \
                  /       /                                  \   \
                 /       /                                    |   |
                /       /                                     /_  \
               /       /                                     /  \_ |
              /       /                                     /     \\
             /       /                                     /       /
            /       /                                     /       /
            \\_    /                                     /       /
             | \_ /                                     /       /
             \   /                                     /       /
              |   |                                   /       /
              \   \                                  /       /
               \   |                            ___//       /
                |  \                        ___/           /
                \___|                    __/            __/
                 \_ \______          ___/           ___/
                   \_\     \________/            __/
                     \_____      \_          ___/
                           \_______\_    ___/
                                   \____/
```
