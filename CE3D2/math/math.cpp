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

        // Calculate intersections with the continued border-lines of the box
        // and pick the points that are on the box's border.

        // Left border
        bool left;
        std::pair<PrecisionType, PrecisionType> p;
        p.second = line(box.x);
        if (p.second >= box.y && p.second <= box.y + box.height)
        {
            p.first = box.x;
            intersections.push_back(p);
            left = true;
        }
        else
        {
            left = false;
        }

        // Right border
        bool right;
        p.first = box.x + box.width;
        p.second = line(p.first);
        if (p.second >= box.y && p.second <= box.y + box.height)
        {
            intersections.push_back(p);
            right = true;
        }
        else
        {
            right = false;
        }

        // Bottom border.
        bool bottom;
        p.first = line.inverse(box.y);
        if (p.first >= box.x && p.first <= box.x + box.width)
        {
            p.second = box.y;
            intersections.push_back(p);
            bottom = true;
        }
        else
        {
            bottom = false;
        }

        // Top border
        bool top;
        p.second = box.y + box.height;
        p.first = line.inverse(p.second);
        if (p.first >= box.x && p.first <= box.x + box.width)
        {
            intersections.push_back(p);
            top = true;
        }
        else
        {
            top = false;
        }

        // Sort out duplicate points which occur when hitting corners.
        if (intersections.size() == 4) {
            intersections.erase(intersections.end() - 2, intersections.end());
        }
        else if (left && right && (bottom || top)) {
            intersections.pop_back();
        }
        else if ((left || right) && bottom && top) {
            intersections.erase(intersections.begin());
        }

        return intersections;
    }
}
}
