# Getting Started - Part 2

## 3D rendering

Now we come to the part where we do fancy 3D stuff.

### Step 1: Create a 3D geometry

So let's define an actual geometry! We take a cube for this purpose with points
also on the edges so it looks more like a cube when rendering:

```cpp
Vector create_3d_vector(float x, float y, float z)
{
    Vector v(3);
    v[0] = x;
    v[1] = y;
    v[2] = z;
    return v;
}

// Creates a cube of given size and specific equidistant number of vectors on
// the edges.
std::vector<Vector> make_cube(float size = 1.0f, unsigned int edge_density = 0)
{
    std::vector<Vector> vectors;

    float step = size / (1 + edge_density);
    for (float x = 0.0f; x <= size; x += step)
    {
        vectors.push_back(create_3d_vector(x, 0.0f, 0.0f));
        vectors.push_back(create_3d_vector(x, size, 0.0f));
        vectors.push_back(create_3d_vector(x, size, size));
        vectors.push_back(create_3d_vector(x, 0.0f, size));
    }
    for (float y = step; y <= size - step; y += step)
    {
        vectors.push_back(create_3d_vector(0.0f, y, 0.0f));
        vectors.push_back(create_3d_vector(size, y, 0.0f));
        vectors.push_back(create_3d_vector(size, y, size));
        vectors.push_back(create_3d_vector(0.0f, y, size));
    }
    for (float z = step; z <= size - step; z += step)
    {
        vectors.push_back(create_3d_vector(0.0f, 0.0f, z));
        vectors.push_back(create_3d_vector(size, 0.0f, z));
        vectors.push_back(create_3d_vector(size, size, z));
        vectors.push_back(create_3d_vector(0.0f, size, z));
    }

    return vectors;
}
```

### Step 2: Use a renderer

We apply the same workflow like in the 2D-case on our 3D vectors:

```cpp
#include <iostream>
#include <memory>
#include <vector>

#include <CE3D2/models/Model.h>
#include <CE3D2/render/TextRenderer.h>
#include <CE3D2/render/TextSurface.h>
#include <CE3D2/Vector.h>

using namespace CE3D2;

Vector create_3d_vector(float x, float y, float z)
{
    // ...
}

// Creates a cube of given size and specific equidistant number of vectors on
// the edges.
std::vector<Vector> make_cube(float size = 1.0f, unsigned int edge_density = 0)
{
    // ...
}

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
    // Let's create the cube!
    auto cube_vectors = make_cube(10, 10);
    auto cube = std::make_shared<Models::Model>();
    cube->vectors().assign(cube_vectors.begin(), cube_vectors.end());

    Render::TextRenderer renderer;
    renderer.set_target(std::make_shared<Render::TextSurface>(40, 20));
    renderer.models().push_back(cube);

    renderer.render();
    print_textsurface(*renderer.get_target());

    return 0;
}
```

We can already render that program, but this looks disappointing, just like
before but with some more points.

```
...........
.         .
.         .
.         .
.         .
.         .
.         .
.         .
.         .
.         .
...........
```

So what's happening here? We provided a cube, why the hell it isn't rendered?

That's because we are missing the transformation step! We defined a cube, but
we don't work with our vectors and project them onto the screen so it gets an
(orthogonal) perspective!

### Step 3: Apply a transformation

The `TextRenderer` takes the first two coordinates of a vector and renders them
with the same coordinates onto the given `TextSurface`. The z-coordinate is
therefore ignored in this case. To render our cube-points, we project the
vectors onto a surface that shall function as our virtual screen.

CE3D2 provides a little transformation system with some transformations for this
purpose. The class we need is `CE3D2::Transformation::OrthogonalProjection`.

```cpp
#include <CE3D2/transformation/OrthogonalProjection.h>

// ...

int main()
{
    // ...
    renderer.models().push_back(cube);

    Transformation::OrthogonalProjection ortho_projection;
    std::vector<Vector> projection_vecs;
    projection_vecs.push_back(create_3d_vector(0.7f, 0.3f, 0.0f));
    projection_vecs.push_back(create_3d_vector(0.0f, 0.3f, 0.7f));
    ortho_projection.set_projection_vectors(projection_vecs);

    ortho_projection.transform(cube->vectors());

    renderer.render();
    // ...
}
```

This looks by far better!

```
......      ....
..         .   ..
. .        .  ...
.  .   .. ....  .
.   ...    .    .
.   .      .    .
    .
   .      .     .
   .      .    .
          .    .
   .   ....    .
 .....     .   .
.  .        .  .
.  .         . .
. .           .
...     ......
 ..... .
```
