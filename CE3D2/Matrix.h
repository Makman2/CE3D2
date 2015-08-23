#ifndef CE3D2_MATRIX_H
#define CE3D2_MATRIX_H

#include <boost/numeric/ublas/matrix.hpp>

#include "CE3D2/Precision.h"


namespace CE3D2
{
    /// The basic matrix type of CE3D2.
    using Matrix = boost::numeric::ublas::matrix<PrecisionType>;
    /// Identity matrix type of CE3D2.
    using IdentityMatrix =
        boost::numeric::ublas::identity_matrix<PrecisionType>;
    /// Zero matrix type of CE3D2.
    using ZeroMatrix = boost::numeric::ublas::zero_matrix<PrecisionType>;
}

#endif
