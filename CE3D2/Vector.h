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
    /// Scalar-vector type used from CE3D2.
    using ScalarVector = boost::numeric::ublas::scalar_vector<PrecisionType>;

    /// Creates a 1-dimensional vector.
    ///
    /// @param v0 The 1st value.
    /// @returns  A 1-dimensional vector.
    Vector
    create_vector(PrecisionType v0);
    /// Creates a 2-dimensional vector.
    ///
    /// @param v0 The 1st value.
    /// @param v1 The 2nd value.
    /// @returns  A 2-dimensional vector.
    Vector
    create_vector(PrecisionType v0, PrecisionType v1);
    /// Creates a 3-dimensional vector.
    ///
    /// @param v0 The 1st value.
    /// @param v1 The 2nd value.
    /// @param v2 The 3rd value.
    /// @returns  A 3-dimensional vector.
    Vector
    create_vector(PrecisionType v0, PrecisionType v1, PrecisionType v2);
    /// Creates a 4-dimensional vector.
    ///
    /// @param v0 The 1st value.
    /// @param v1 The 2nd value.
    /// @param v2 The 3rd value.
    /// @param v3 The 4th value.
    /// @returns  A 4-dimensional vector.
    Vector
    create_vector(PrecisionType v0,
                  PrecisionType v1,
                  PrecisionType v2,
                  PrecisionType v3);
    /// Creates a 5-dimensional vector.
    ///
    /// @param v0 The 1st value.
    /// @param v1 The 2nd value.
    /// @param v2 The 3rd value.
    /// @param v3 The 4th value.
    /// @param v4 The 5th value.
    /// @returns  A 5-dimensional vector.
    Vector
    create_vector(PrecisionType v0,
                  PrecisionType v1,
                  PrecisionType v2,
                  PrecisionType v3,
                  PrecisionType v4);
}

#endif
