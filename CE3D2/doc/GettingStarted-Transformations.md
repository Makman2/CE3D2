# Getting Started - Part 3

## Transformations

In the last part of the tutorial we applied an orthogonal projection
transformation onto a cube geometry. This chapter deals with the transformation
system of CE3D2.

### A quantum of theory

Transformations are something quite general, mathematically defined a
transformation maps a vector onto another vector in CE3D2.

In fact any function that operates on vectors and returns one is a suitable
transformation and can be implemented as such. More interesting is now which
ones are useful for us, since there are plenty of mathematical functions one
could think of.

CE3D2 implements common transformations like
`CE3D2::Transformation::OrthogonalProjection` (that we used before) or
`CE3D2::Transformation::Rotation`. Important to know is that transformations
apply their changes *in-place*. This allows to chain them easily with just
applying them sequentially:

```cpp
CE3D2::Models::Model geometry;

// ...

scale_transform.transform(geometry.vectors());
orthogonal_projection.transform(geometry.vectors());
```

An important derivative of the `CE3D2::Transformation::Transformation` class
is the `CE3D2::Transformation::LinearTransformation` which allows to implement
linear mappings.

A linear transformation can be described in the most general matter as a matrix
(I believe). Means for linear transformations you only need to provide a matrix
that defines the linear behaviour of the transformation. Imagine you apply many
transformations in a row and assume they are all linear, means they consist of
matrices. Let's write this down mathematically:

`output = f(g(input))`
`=> output = A * (B * input)`

Where `f` and `g` are our linear transformations of the form `M * input`, where
`M` describes an arbitrary matrix.

That's what happens when we apply transformations in a row like above. Matrices
have a very nice property: Associativity!

`output = A * (B * input)`
`=> output = A * B * input`
`=> output = (A * B) * input`

Nice! This means we can premultiply all matrices before applying them onto a
vector!

This behaviour yields significant performance boosts if you have many
transformations and many vectors. Since now you don't need to multiply every
single matrix with a vector again and again until every transformation is
worked through, we multiply the matrices together a single time, and then we
need to multiply with a vector also a single time!

So that's about the concept of transformations, let's do something meaningful
with our example.

### Squarify our cube

The last time our example served us this:

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

We defined a cube, but this doesn't look like a cube, more like a cuboid. This
happens due to the size of a single character: It's more height than width.

Let's compensate this using a scale transformation. We assume that a char needs
twice as much height than width.

```cpp
#include <CE3D2/transformation/Scale.h>

// ...

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

    // Instantiate a scale transformation.
    Vector scaling_vector(2);
    scaling_vector[0] = 2.0f; // Only the x-component of the screen needs a bit
                              // stretching.
    scaling_vector[1] = 1.0f;
    Transformation::Scale scale(scaling_vector);

    ortho_projection.transform(cube->vectors());
    // Apply scale.
    scale.transform(cube->vectors());

    renderer.render();
    print_textsurface(*renderer.get_target());

    return 0;
}
```

Running the modified example prints out this:

```
... . . .  .            .  ....
. ..                   .       ..
.   ..                 .     . ...
      ..       . .  . . . .      .
        .  . .        .         .
        .             .         .
        .
       .             .          .
       .             .         .
                     .         .
       .      . . . ..         .
  .  ... . .          ..      .
.     .                 ..    .
.     .                   ..  .
..   .                      ..
 ..  .          . . .  . . .
   ... . . .  .
```

Yeah! That's actually a cube!
