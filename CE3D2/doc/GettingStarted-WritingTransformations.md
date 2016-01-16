# Getting Started - Part 4

## Writing your own transformations

### Non-linear transformations

Like described in the chapter before a transformation in CE3D2 maps a vector
onto another vector. Exactly this behaviour is manifested inside a function
of `CE3D2::Transformation::Transformation`:

```cpp
virtual void
transform_vector(CE3D2::Vector &vector) const;
```

So all you need to do is override this member and modify the vector as you wish.

For example let's take a translation in x-direction of the length 1.

```cpp
#include <CE3D2/transformation/Transformation.h>

class XTranslation : public CE3D2::Transformation::Transformation
{
public:
    void
    transform_vector(CE3D2::Vector& vector) const override
    {
        vector[0] += 1;
    }
};
```

That's all! This transformation can now be used like any other transformation.

### Linear transformations

If your transformation you want to implement fits into a matrix, you should use
the `CE3D2::Transformation::LinearTransformation` instead.

Let us directly take another example: We want a matrix that shall apply
something like a weighting algorithm, so each element of the given vector is
weighted with a factor and added together with the others. We imagine some kind
of shopping list with 3 items: Pizza, energy drinks and ice cream. The
weightings represent prices, a pizza costs 10$, a single energy drink 3$ and a
bucket of ice cream 5$ (yeah we buy the good ice cream, not the cheapest one
:D). We could implement this inside a transformation like this:

```cpp
#include <CE3D2/Matrix.h>
#include <CE3D2/transformation/LinearTransformation.h>

class ShoppingListTransformation :
    public CE3D2::Transformation::LinearTransformation
{
protected:
    virtual CE3D2::Matrix
    on_update() const override
    {
        CE3D2::Matrix cashbox(1, 3);
        cashbox(0, 0) = 10.0f; // Pizza,
        cashbox(0, 1) = 3.0f; // energy-drinks
        cashbox(0, 2) = 5.0f; // and the good ice cream.
        return cashbox;
    }
};
```

Applying this transformation on a 3D-vector would serve us now a one-dimensional
vector where the entry holds the all round price.

Now we need to override another member, called `on_update()`. Linear
transformations use a lazy update system, this means if someone wants to
retrieve the matrix via `get_matrix()`, it's only calculated once (if no
changes were performed until the next call, more on that instantly). So
calling `get_matrix()` repeatedly does not impact that much on performance,
since the last calculated matrix is stored and retrieved directly on demand.

But what if changes occur? Maybe you provide a value inside your transformation
your matrix depends on? That's what the `update()` method is for. You **must**
call it if you detected changes that affect your matrix so it can be updated
again from your values inside `on_update()`.

So you know now also how linear transformations work in CE3D2, you should have
no problems to advance even further!
