#include "CE3D2/transformation/OrthogonalProjection.h"

#include "CE3D2/math/matrices.h"


namespace CE3D2
{
namespace Transformation
{
    OrthogonalProjection::OrthogonalProjection()
    : m_ProjectionVectors()
    {}

    OrthogonalProjection::~OrthogonalProjection()
    {}

    std::vector<CE3D2::Vector> const&
    OrthogonalProjection::get_projection_vectors() const
    {
        return m_ProjectionVectors;
    }

    CE3D2::Matrix
    OrthogonalProjection::on_update() const
    {
        // Check if we have any projection vectors.
        if (m_ProjectionVectors.empty())
        {
            throw std::invalid_argument("No projection vectors to project on.");
        }

        // Check size equality of vectors.
        for (std::vector<CE3D2::Vector>::size_type i = 1;
             i < m_ProjectionVectors.size();
             i++)
        {
            if (m_ProjectionVectors[i - 1].size() !=
                m_ProjectionVectors[i].size())
            {
                throw std::invalid_argument(
                    "The size of the projection vectors varies.");
            }
        }

        // Check if we have more projection vectors than dimensions (so we have
        // ambigious projection vectors). The inverse would fail.
        if (m_ProjectionVectors[0].size() < m_ProjectionVectors.size())
        {
            throw std::invalid_argument("More projection vectors than "
                                        "dimensions. They must be linearly "
                                        "dependent.");
        }

        // Actually calculate the projection matrix.
        CE3D2::Matrix matrix = CE3D2::Matrix(m_ProjectionVectors[0].size(),
                                             m_ProjectionVectors.size());

        // Concatenate vectors together.
        for (std::vector<CE3D2::Vector>::size_type i = 0;
             i < m_ProjectionVectors.size();
             i++)
        {
            auto const& current_vector = m_ProjectionVectors[i];
            boost::numeric::ublas::column(matrix, i) = current_vector;
        }

        CE3D2::Matrix transposed(boost::numeric::ublas::trans(matrix));
        CE3D2::Matrix inverted(matrix.size1(), matrix.size2());

        CE3D2::Matrix inner_prod(prod(transposed, matrix));

        if (CE3D2::Math::Matrices::invert(inner_prod, inverted) == false)
        {
            throw std::invalid_argument(
                "The projection vectors are linearly dependent.");
        }

        return prod(inverted, transposed);
    }
}
}
