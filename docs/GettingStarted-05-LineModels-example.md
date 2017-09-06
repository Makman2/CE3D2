# Getting Started - Part 5 - Example code

This is the full code file from the 5th tutorial that renders a 3D cube with
lines.

## Build

You can build it via `g++` with

```
g++ -std=c++11 -lCE3D2 example3d.cpp -o example3d
```

and execute it with `./example3d`.

## example3d.cpp

```cpp
#include <iostream>
#include <memory>

#include <CE3D2/models/LineModel.h>
#include <CE3D2/render/TextRenderer.h>
#include <CE3D2/render/TextSurface.h>
#include <CE3D2/transformation/OrthogonalProjection.h>
#include <CE3D2/transformation/Scale.h>
#include <CE3D2/transformation/Translation.h>
#include <CE3D2/Vector.h>

using namespace CE3D2;

int main()
{
    auto model = std::make_shared<Models::LineModel>(Models::LineModel::cube());

    model->transform(Transformation::Scale(create_vector(10.0f, 10.0f, 10.0f)));

    Transformation::OrthogonalProjection ortho_projection;
    std::vector<Vector> projection_vecs;
    projection_vecs.push_back(create_vector(0.7f, 0.3f, 0.0f));
    projection_vecs.push_back(create_vector(0.0f, 0.3f, 0.7f));
    ortho_projection.set_projection_vectors(projection_vecs);

    model->transform(ortho_projection);

    model->transform(Transformation::Translation(create_vector(10.0f, 10.0f)));

    Render::TextRenderer renderer;
    renderer.set_target(std::make_shared<Render::TextSurface>(24, 21));
    renderer.line_models().push_back(model);
    renderer.render();
    std::cout << *renderer.get_target();

    return 0;
}
```
