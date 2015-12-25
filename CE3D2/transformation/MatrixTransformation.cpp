#include "CE3D2/transformation/MatrixTransformation.h"


namespace CE3D2
{
namespace Transformation
{
    MatrixTransformation::MatrixTransformation(CE3D2::Matrix const& matrix)
    : m_Matrix(matrix)
    {}

    MatrixTransformation::~MatrixTransformation()
    {}

    void
    MatrixTransformation::set_matrix(CE3D2::Matrix const& matrix)
    {
        m_Matrix = matrix;
        update();
    }

    CE3D2::Matrix
    MatrixTransformation::on_update() const
    {
        return m_Matrix;
    }
}
}
