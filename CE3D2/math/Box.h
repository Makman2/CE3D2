#ifndef CE3D2_MATH_BOX_H
#define CE3D2_MATH_BOX_H

#include "CE3D2/Precision.h"


namespace CE3D2
{
namespace Math
{
    /// A rectangular box in 2D-space.
    class Box
    {
    public:
        /// Creates a new `Box` with a lower-left-corner at `(0, 0)`.
        ///
        /// @param width  The width of the box.
        /// @param height The height of the box.
        Box(PrecisionType width, PrecisionType height);

        /// Creates a new `Box`.
        ///
        /// @param x      The x-coordinate of the lower-left-corner of the box.
        /// @param y      The y-coordinate of the lower-left-corner of the box.
        /// @param width  The width of the box.
        /// @param height The height of the box.
        Box(PrecisionType x,
            PrecisionType y,
            PrecisionType width,
            PrecisionType height);

        PrecisionType x;
        PrecisionType y;
        PrecisionType width;
        PrecisionType height;
    };
}
}

#endif
