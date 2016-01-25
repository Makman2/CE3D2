#include "CE3D2/transformation/Rotation.h"


namespace CE3D2
{
namespace Transformation
{
    Rotation::Rotation()
    : Rotation(CE3D2::Vector(), CE3D2::Vector())
    {}

    Rotation::Rotation(CE3D2::Vector const& v1, CE3D2::Vector const& v2)
    : Rotation(v1, v2, 0.0f)
    {}

    Rotation::Rotation(CE3D2::Vector const& v1,
                       CE3D2::Vector const& v2,
                       PrecisionType angle)
    : m_PlaneVector1(v1)
    , m_PlaneVector2(v2)
    , m_Angle(angle)
    , m_MatricesCached(false)
    , m_CachedMatrixV()
    , m_CachedMatrixW()
    , m_CachedIdentity()
    {}

    Rotation::~Rotation()
    {}

    CE3D2::Vector const&
    Rotation::get_plane_vector1() const
    {
        return m_PlaneVector1;
    }

    void
    Rotation::set_plane_vector1(CE3D2::Vector const& value)
    {
        m_PlaneVector1 = value;
        m_MatricesCached = false;
        update();
    }

    CE3D2::Vector const&
    Rotation::get_plane_vector2() const
    {
        return m_PlaneVector2;
    }

    void
    Rotation::set_plane_vector2(CE3D2::Vector const& value)
    {
        m_PlaneVector2 = value;
        m_MatricesCached = false;
        update();
    }

    PrecisionType
    Rotation::get_angle() const
    {
        return m_Angle;
    }

    void
    Rotation::set_angle(PrecisionType value)
    {
        m_Angle = value;
        update();
    }

    PrecisionType
    Rotation::get_angle_in_degrees() const
    {
        return get_angle() * 180.0f / CE3D2::PI;
    }

    void
    Rotation::set_angle_in_degrees(PrecisionType value)
    {
        set_angle(value * CE3D2::PI / 180.0f);
    }

    CE3D2::Matrix
    Rotation::on_update() const
    {
        if (!m_MatricesCached)
        {
            if (m_PlaneVector1.size() != m_PlaneVector2.size())
            {
                throw std::invalid_argument(
                    "Plane vectors have unequal size.");
            }

            // Orthonormalize first plane vector.
            Vector plane_vector1_orthonormalized =
                m_PlaneVector1 / boost::numeric::ublas::norm_2(m_PlaneVector1);

            // Orthonormalize the second plane vector with the first one.
            Vector plane_vector2_orthonormalized =
                m_PlaneVector2 -
                boost::numeric::ublas::inner_prod(
                    m_PlaneVector2,
                    plane_vector1_orthonormalized) *
                plane_vector1_orthonormalized;

            PrecisionType plane_vector2_norm =
                boost::numeric::ublas::norm_2(plane_vector2_orthonormalized);

            if (plane_vector2_norm == 0.0f)
            {
                throw std::invalid_argument(
                    "Plane vectors are linearly dependent.");
            }

            plane_vector2_orthonormalized /= plane_vector2_norm;

            // Create main matrices for constructing the rotation matrix.
            m_CachedMatrixV =
                boost::numeric::ublas::outer_prod(
                    plane_vector1_orthonormalized,
                    plane_vector1_orthonormalized) +
                boost::numeric::ublas::outer_prod(
                    plane_vector2_orthonormalized,
                    plane_vector2_orthonormalized);

            m_CachedMatrixW =
                boost::numeric::ublas::outer_prod(
                    plane_vector1_orthonormalized,
                    plane_vector2_orthonormalized) -
                boost::numeric::ublas::outer_prod(
                    plane_vector2_orthonormalized,
                    plane_vector1_orthonormalized);

            m_CachedIdentity = CE3D2::IdentityMatrix(m_PlaneVector1.size());

            m_MatricesCached = true;
        }

        // Construct and return final rotation matrix.
        return (cos(m_Angle) - 1.0f) * m_CachedMatrixV + sin(m_Angle) *
               m_CachedMatrixW + m_CachedIdentity;
    }
}
}
