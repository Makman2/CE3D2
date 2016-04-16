#include "CE3D2/math/Box.h"


namespace CE3D2
{
namespace Math
{
    Box::Box(PrecisionType width, PrecisionType height)
    : Box(0.0f, 0.0f, width, height)
    {}

    Box::Box(PrecisionType x,
             PrecisionType y,
             PrecisionType width,
             PrecisionType height)
    : x(x)
    , y(y)
    , width(width)
    , height(height)
    {}

    bool
    Box::contains(Box const& box) const
    {
        return box.x >= x &&
               box.y >= y &&
               box.x + box.width <= x + width &&
               box.y + box.height <= y + height;
    }

    bool
    Box::contains(PrecisionType x, PrecisionType y) const
    {
        return x >= this->x &&
               x <= this->x + this->width &&
               y >= this->y &&
               y <= this->y + this->height;
    }

    bool
    Box::inside(Box const& box) const
    {
        return box.contains(*this);
    }
}
}
