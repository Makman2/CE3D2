#include "CE3D2/transformation/OrthogonalProjection.h"


namespace CE3D2
{
namespace Transformation
{
    template<typename T>
    OrthogonalProjection::OrthogonalProjection(T const& vectors)
    : m_ProjectionVectors(vectors)
    {}

    template<typename T>
    void
    OrthogonalProjection::set_projection_vectors(T const& vectors)
    {
        m_ProjectionVectors.assign(vectors.cbegin(), vectors.cend());
        update();
    }
}
}
