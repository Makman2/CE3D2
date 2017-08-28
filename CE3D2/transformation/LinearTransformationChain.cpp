#include "CE3D2/transformation/LinearTransformationChain.h"

#include <boost/numeric/ublas/operation.hpp>


namespace CE3D2
{
namespace Transformation
{
    LinearTransformationChain::TransformationChain()
    : m_Transformations()
    {}

    void
    LinearTransformationChain::transform_vector(CE3D2::Vector& vector) const
    {


        for (auto const& transformation: m_Transformations)
        {
            transformation->transform_vector(vector);
        }
    }

    std::vector<std::shared_ptr<LinearTransformation>>&
    LinearTransformationChain::transformations()
    {
        return m_Transformations;
    }

    CE3D2::Matrix
    LinearTransformationChain::on_update() const
    {
        if (m_Transformations.empty()) {
            throw std::logic_error(
                "No transformations placed into transformation chain.");
        }

        if (std::any_of(m_Transformations.cbegin(),
                        m_Transformations.cend(),
                        [](LinearTransformation const& transform)
                        {
                            return !transform.is_updated();
                        }))
        {
            // Again multiply matrices, as at least one has changed.

            auto iterator = m_Transformations.cbegin();
            auto multiplied_matrix = iterator->get()->get_matrix();
            iterator++;

            while (iterator != m_Transformations.cend())
            {
                multiplied_matrix = boost::numeric::ublas::prod(
                    iterator->get()->get_matrix(), multiplied_matrix);
                iterator++;
            }
        }
    }
}
}
