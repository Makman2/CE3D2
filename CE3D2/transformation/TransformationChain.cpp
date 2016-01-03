#include "CE3D2/transformation/TransformationChain.h"


namespace CE3D2
{
namespace Transformation
{
    TransformationChain::TransformationChain()
    : m_Transformations()
    {}

    void
    TransformationChain::transform_vector(CE3D2::Vector& vector) const
    {
        for (auto const& transformation: m_Transformations)
        {
            transformation->transform_vector(vector);
        }
    }

    std::vector<std::shared_ptr<Transformation>>&
    TransformationChain::get_transformations()
    {
        return m_Transformations;
    }
}
}
