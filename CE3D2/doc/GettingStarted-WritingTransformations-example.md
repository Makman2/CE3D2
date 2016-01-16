# Getting Started - Part 4 - Example code

Contains all snippets from the fourth tutorial you can directly include. For
simplicity reasons no cpp-files were used.

## XTranslation.h

```cpp
#ifndef _XTRANSLATION_H
#define _XTRANSLATION_H

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

#endif
```

## ShoppingListTransformation.h

```cpp
#ifndef _SHOPPING_LIST_TRANSFORMATION_H
#define _SHOPPING_LIST_TRANSFORMATION_H

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

#endif
```
