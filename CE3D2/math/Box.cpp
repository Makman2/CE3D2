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
}
}
