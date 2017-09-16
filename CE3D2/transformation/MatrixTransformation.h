#ifndef CE3D2_TRANSFORMATION_MATRIX_TRANSFORMATION_H
#define CE3D2_TRANSFORMATION_MATRIX_TRANSFORMATION_H

#include "CE3D2/transformation/LinearTransformation.h"


namespace CE3D2
{
namespace Transformation
{
    /// A custom linear transformation.
    class MatrixTransformation : public LinearTransformation
    {
    public:
        /// Instantiates a new matrix transformation.
        ///
        /// @param matrix
        ///     The initial matrix.
        MatrixTransformation(CE3D2::Matrix const& matrix);

        virtual ~MatrixTransformation();

        /// Sets the transformation matrix.
        ///
        /// @param matrix
        ///     The new transformation matrix.
        void
        set_matrix(CE3D2::Matrix const& matrix);

    protected:
        // Inherited documentation.
        virtual CE3D2::Matrix
        on_update() const override;

    private:
        CE3D2::Matrix m_Matrix;
    };
}
}

#endif
