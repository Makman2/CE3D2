# Getting Started - Part 3 - Example code

This is the full code file from the third tutorial dealing with transformations.

## Build

You can build it via `g++` with

```
g++ -std=c++11 -lCE3D2 example_transform.cpp -o example_transform
```

and execute it with `./example_transform`.

## example_transform.cpp

```cpp
#include <iostream>
#include <memory>
#include <vector>

#include <CE3D2/models/Model.h>
#include <CE3D2/transformation/Scale.h>
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

    Vector scaling_vector(2);
    scaling_vector[0] = 2.0f;
    scaling_vector[1] = 1.0f;
    Transformation::Scale scale(scaling_vector);

    ortho_projection.transform(cube->vectors());
    scale.transform(cube->vectors());

    renderer.render();
    print_textsurface(*renderer.get_target());

    return 0;
}
```
