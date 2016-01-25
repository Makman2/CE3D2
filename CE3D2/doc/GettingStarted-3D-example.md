# Getting Started - Part 2 - Example code

This is the full code file from the second tutorial that renders the 3D cube.

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
#include <vector>

#include <CE3D2/models/Model.h>
#include <CE3D2/transformation/OrthogonalProjection.h>
#include <CE3D2/render/TextRenderer.h>
#include <CE3D2/render/TextSurface.h>
#include <CE3D2/Vector.h>

using namespace CE3D2;

// Creates a cube of given size and specific equidistant number of vectors on
// the edges.
std::vector<Vector> make_cube(float size = 1.0f, unsigned int edge_density = 0)
{
    std::vector<Vector> vectors;

    float step = size / (1 + edge_density);
    for (float x = 0.0f; x <= size; x += step)
    {
        vectors.push_back(create_vector(x, 0.0f, 0.0f));
        vectors.push_back(create_vector(x, size, 0.0f));
        vectors.push_back(create_vector(x, size, size));
        vectors.push_back(create_vector(x, 0.0f, size));
    }
    for (float y = step; y <= size - step; y += step)
    {
        vectors.push_back(create_vector(0.0f, y, 0.0f));
        vectors.push_back(create_vector(size, y, 0.0f));
        vectors.push_back(create_vector(size, y, size));
        vectors.push_back(create_vector(0.0f, y, size));
    }
    for (float z = step; z <= size - step; z += step)
    {
        vectors.push_back(create_vector(0.0f, 0.0f, z));
        vectors.push_back(create_vector(size, 0.0f, z));
        vectors.push_back(create_vector(size, size, z));
        vectors.push_back(create_vector(0.0f, size, z));
    }

    return vectors;
}

int main()
{
    auto cube_vectors = make_cube(10, 10);
    auto cube = std::make_shared<Models::Model>();
    cube->vectors().assign(cube_vectors.begin(), cube_vectors.end());

    Render::TextRenderer renderer;
    renderer.set_target(std::make_shared<Render::TextSurface>(40, 20));
    renderer.models().push_back(cube);

    Transformation::OrthogonalProjection ortho_projection;
    std::vector<Vector> projection_vecs;
    projection_vecs.push_back(create_vector(0.7f, 0.3f, 0.0f));
    projection_vecs.push_back(create_vector(0.0f, 0.3f, 0.7f));
    ortho_projection.set_projection_vectors(projection_vecs);

    ortho_projection.transform(cube->vectors());

    renderer.render();
    std::cout << *renderer.get_target();

    return 0;
}
```
