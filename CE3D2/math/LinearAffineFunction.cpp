#include "CE3D2/math/LinearAffineFunction.h"


namespace CE3D2
{
namespace Math
{
    LinearAffineFunction::LinearAffineFunction()
    : LinearAffineFunction(1.0f, 0.0f)
    {}

    LinearAffineFunction::LinearAffineFunction(PrecisionType gradient)
    : LinearAffineFunction(gradient, 0.0f)
    {}

    LinearAffineFunction::LinearAffineFunction(PrecisionType x1,
                                               PrecisionType y1,
                                               PrecisionType x2,
                                               PrecisionType y2)
    : LinearAffineFunction((y1 - y2) / (x1 - x2),
                           (x1 * y2 - x2 * y1) / (x1 - x2))
    {}

    LinearAffineFunction::LinearAffineFunction(PrecisionType gradient,
                                               PrecisionType yintercept)
    : m_Gradient(gradient)
    , m_YIntercept(yintercept)
    {}

    PrecisionType
    LinearAffineFunction::get_gradient() const
    {
        return m_Gradient;
    }

    void
    LinearAffineFunction::set_gradient(PrecisionType value)
    {
        m_Gradient = value;
    }

    PrecisionType
    LinearAffineFunction::get_yintercept() const
    {
        return m_YIntercept;
    }

    void
    LinearAffineFunction::set_yintercept(PrecisionType value)
    {
        m_YIntercept = value;
    }

    PrecisionType
    LinearAffineFunction::operator ()(PrecisionType x) const
    {
        return m_Gradient * x + m_YIntercept;
    }
}
}
