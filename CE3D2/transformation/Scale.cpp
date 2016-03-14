#include "CE3D2/transformation/Scale.h"


namespace CE3D2
{
namespace Transformation
{
    Scale::Scale(CE3D2::Vector const& scale)
    : m_Scale(scale)
    {}

    Scale::~Scale()
    {}

    CE3D2::Vector const&
    Scale::get_scale() const
    {
        return m_Scale;
    }

    void
    Scale::set_scale(CE3D2::Vector const& scale)
    {
        m_Scale = scale;
        update();
    }

    void
    Scale::set_scale(CE3D2::Vector::size_type index, CE3D2::PrecisionType scale)
    {
        m_Scale[index] = scale;
        update();
    }

    void
    Scale::transform_vector(CE3D2::Vector& vector) const
    {
        vector = boost::numeric::ublas::element_prod(vector, m_Scale);
    }

    CE3D2::Matrix
    Scale::on_update() const
    {
        CE3D2::Matrix matrix = CE3D2::ZeroMatrix(m_Scale.size(),
                                                 m_Scale.size());

        for (CE3D2::Vector::size_type i = 0; i < m_Scale.size(); i++)
        {
            matrix(i, i) = m_Scale[i];
        }

        return matrix;
    }
}
}
