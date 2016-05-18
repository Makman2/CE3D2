#ifndef CE3D2_MATH_MATH_H
#define CE3D2_MATH_MATH_H

#include <utility>
#include <vector>

#include "CE3D2/math/LinearAffineFunction.h"
#include "CE3D2/math/Box.h"


namespace CE3D2
{
namespace Math
{
    /// Calculates the intersection points when a line intersects a box.
    ///
    /// @param line The line.
    /// @param box  The box.
    /// @returns    A vector of intersection points.
    std::vector<std::pair<PrecisionType, PrecisionType>>
    line_intersection_with_box(LinearAffineFunction const& line,
                               Box const& box);
}
}

#endif
