#include "CE3D2/transformation/Transformation.h"


namespace CE3D2
{
namespace Transformation
{
    template<typename T>
    void
    Transformation::transform(T& vectors) const
    {
        for (auto& vector : vectors)
        {
            transform_vector(vector);
        }
    }
}
}
