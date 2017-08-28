#include "CE3D2/transformation/LinearTransformation.h"

#include <boost/numeric/ublas/operation.hpp>


namespace CE3D2
{
namespace Transformation
{
    LinearTransformation::LinearTransformation()
    : m_Matrix()
    , m_UpdateScheduled(true)
    {}

    LinearTransformation::~LinearTransformation()
    {}

    void
    LinearTransformation::transform_vector(CE3D2::Vector& vector) const
    {
        vector = boost::numeric::ublas::prod(get_matrix(), vector);
    }

    CE3D2::Matrix const&
    LinearTransformation::get_matrix() const
    {
        if (m_UpdateScheduled)
        {
            m_Matrix = on_update();
            m_UpdateScheduled = false;
        }

        return m_Matrix;
    }

    /// Specifies whether the underlying matrix is up-to-date or not.
    ///
    /// @returns `true` if up-to-date, `false` if not.
    bool
    LinearTransformation::is_updated() const {
        return !m_UpdateScheduled;
    }

    void
    LinearTransformation::update()
    {
        m_UpdateScheduled = true;
    }
}
}
