#ifndef CE3D2_MATH_MATRICES_H
#define CE3D2_MATH_MATRICES_H

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/lu.hpp>


namespace CE3D2
{
namespace Math
{
namespace Matrices
{
    /// Inverts a matrix.
    ///
    /// @param input   The matrix to invert. Invertable matrices have quadratic
    ///                size (means they have the same count of rows like
    ///                columns). Passing non-quadratic matrices results in
    ///                undefined behaviour.
    /// @param inverse A reference to the matrix where to store the inverse.
    /// @returns       true if invertable, false if not (because row/column
    ///                vectors are lineary dependent).
    template<typename T>
    bool
    invert(boost::numeric::ublas::matrix<T> const& input,
           boost::numeric::ublas::matrix<T>& inverse);
}
}
}

#include "CE3D2/math/matrices.hpp"

#endif
