#ifndef CE3D2_VECTOR_H
#define CE3D2_VECTOR_H

#include <boost/numeric/ublas/vector.hpp>

#include "CE3D2/Precision.h"


namespace CE3D2
{
    /// Vector type used from CE3D2.
    using Vector = boost::numeric::ublas::vector<PrecisionType>;
    /// Unit-vector type used from CE3D2.
    using UnitVector = boost::numeric::ublas::unit_vector<PrecisionType>;
    /// Zero-vector type used from CE3D2.
    using ZeroVector = boost::numeric::ublas::zero_vector<PrecisionType>;
}

#endif
