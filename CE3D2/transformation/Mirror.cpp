#include "CE3D2/transformation/Mirror.h"


namespace CE3D2
{
namespace Transformation
{
    Mirror::Mirror(CE3D2::Vector const& reflection_plane_normal)
    : m_ReflectionPlaneNormal(reflection_plane_normal)
    , m_MatrixPartCache(calculate_matrix_part_cache(reflection_plane_normal))
    {}

    Mirror::~Mirror()
    {}

    CE3D2::Vector const&
    Mirror::get_reflection_plane_normal() const
    {
        return m_ReflectionPlaneNormal;
    }

    void
    Mirror::set_reflection_plane_normal(CE3D2::Vector const& value)
    {
        m_ReflectionPlaneNormal = value;
        m_MatrixPartCache = calculate_matrix_part_cache(value);

        update();
    }

    void
    Mirror::transform_vector(CE3D2::Vector& vector) const
    {
        vector -= m_MatrixPartCache *
            boost::numeric::ublas::inner_prod(m_ReflectionPlaneNormal, vector);
    }

    CE3D2::Matrix
    Mirror::on_update() const
    {
        return CE3D2::IdentityMatrix(m_ReflectionPlaneNormal.size()) -
            boost::numeric::ublas::outer_prod(
                m_MatrixPartCache, m_ReflectionPlaneNormal);
    }

    CE3D2::Vector
    Mirror::calculate_matrix_part_cache(
        CE3D2::Vector const& reflection_plane_normal)
    {
        return 2 * reflection_plane_normal /
            boost::numeric::ublas::inner_prod(reflection_plane_normal,
                                              reflection_plane_normal);
    }
}
}
