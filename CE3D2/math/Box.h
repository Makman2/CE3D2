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

        /// Tests whether another box is completely inside this box.
        ///
        /// @param box The other box.
        bool
        contains(Box const& box) const;

        /// Tests whether a given 2D-coordinate resides inside this box.
        ///
        /// @param x The x-coordinate of the point.
        /// @param y The y-coordinate of the point.
        bool
        contains(PrecisionType x, PrecisionType y) const;

        /// Tests whether this box is completely inside another box.
        ///
        /// @param box The other box.
        bool
        inside(Box const& box) const;

        PrecisionType x;
        PrecisionType y;
        PrecisionType width;
        PrecisionType height;
    };
}
}

#endif
