# Getting Started - Part 5

## Line rendering

CE3D2 is capable of not only rendering dots, but also ASCII-art lines.

### Step 1: Set up a model

Again the starting point of rendering something is creating our geometry. But
in this case we use a `LineModel` instead of the plain `Model` we have used
before.

```cpp
#include <memory>

#include <CE3D2/models/LineModel.h>

using namespace CE3D2;

int main()
{
    auto model = std::make_shared<Model::LineModel>(Model::LineModel::cube());

    return 0;
}
```

The line model contains additional information what vectors are connected
together with a line. This information is stored inside
`LineModel::edges()` using index pairs of the vectors in
`LineModel::vectors()`. The indices in the pairs refer to the (zero-based)
position inside `LineModel::vectors()`.

### Step 2: Transforming

Creating a model was quite easy and quick, let's add the functionality for
preparing the vertices for the renderer on top (scaling it appropriately, making
a flat projection and move it into the view):

```cpp
#include <memory>

#include <CE3D2/models/LineModel.h>
#include <CE3D2/transformation/OrthogonalProjection.h>
#include <CE3D2/transformation/Scale.h>
#include <CE3D2/transformation/Translation.h>
#include <CE3D2/Vector.h>

using namespace CE3D2;

int main()
{
    auto model = std::make_shared<Model::LineModel>(Model::LineModel::cube());

    model.transform(Transformation::Scale(create_vector(10.0f, 10.0f, 10.0f)));

    Transformation::OrthogonalProjection ortho_projection;
    std::vector<Vector> projection_vecs;
    projection_vecs.push_back(create_vector(0.7f, 0.3f, 0.0f));
    projection_vecs.push_back(create_vector(0.0f, 0.3f, 0.7f));
    ortho_projection.set_projection_vectors(projection_vecs);

    model.transform(ortho_projection);

    model->transform(Transformation::Translation(create_vector(10.0f, 10.0f)));

    return 0;
}
```

### Step 3: Rendering

Now we need to render the stuff. There's only a minor change involved inside the
renderer we used before to draw our stuff: Instead of adding the model to
`TextRenderer::models()`, we add it to `TextRenderer::line_models()`.

```cpp
#include <iostream>

// ...
#include <CE3D2/render/TextRenderer.h>
#include <CE3D2/render/TextSurface.h>

using namespace CE3D2;

int main()
{
    // ...

    model.transform(ortho_projection);

    Render::TextRenderer renderer;
    renderer.set_target(std::make_shared<Render::TextSurface>(24, 21));
    renderer.line_models().push_back(cube);
    renderer.render();
    std::cout << *renderer.get_target();

    return 0;
}
```

And that's it! The same procedure as before, but `line_models()` instead of
`models()` is used. This is our nice-looking output:

```

           ____|
    ______/    |\
   /           | \
  | \          /  \
  |  \        |   _\
  |   \     __|__/ |
  |    \___/  |    |
  |    |      |    |
  |    |      |    |
  /    |      /    |
 |     /     |     /
 |    |      |    |
 |    |    __\    |
 |   _|___/   \   |
 \__/ |        \  |
  \   |         \ |
   \  /          \|
    \|      ______
     |_____/


```
