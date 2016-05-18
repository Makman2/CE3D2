#include "CE3D2/math/math.h"


namespace CE3D2
{
namespace Math
{
    std::vector<std::pair<PrecisionType, PrecisionType>>
    line_intersection_with_box(LinearAffineFunction const& line,
                               Box const& box)
    {
        std::vector<std::pair<PrecisionType, PrecisionType>> intersections;

        // Calculate intersections with the border-lines of the box and pick the
        // points that are inside the box.

        // FIXME
        // There may be precision problems when the line hits corners, so this
        // function returns one point more.

        // Left border
        std::pair<PrecisionType, PrecisionType> p;
        p.second = line(box.x);
        if (p.second >= box.y && p.second <= box.y + box.height)
        {
            p.first = box.x;
            intersections.push_back(p);
        }

        // Right border
        p.first = box.x + box.width;
        p.second = line(p.first);
        if (p.second >= box.y && p.second <= box.y + box.height)
        {
            intersections.push_back(p);
        }

        // Bottom border.
        p.first = line.inverse(box.y);
        if (p.first >= box.x && p.first <= box.x + box.width)
        {
            p.second = box.y;
            intersections.push_back(p);
        }

        // Top border
        p.second = box.y + box.height;
        p.first = line.inverse(p.second);
        if (p.first >= box.x && p.first <= box.x + box.width)
        {
            intersections.push_back(p);
        }

        return intersections;
    }
}
}
