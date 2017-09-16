#ifndef CE3D2_TRANSFORMATION_PERMUTATIONVECTOR_H
#define CE3D2_TRANSFORMATION_PERMUTATIONVECTOR_H

#include <boost/numeric/ublas/vector.hpp>


namespace CE3D2
{
namespace Transformation
{
    /// Permutation vector type.
    using PermutationVector = boost::numeric::ublas::vector<size_t>;

    /// Creates a 1-dimensional permutation vector.
    ///
    /// @param v0
    ///     The 1st value.
    /// @returns
    ///     A 1-dimensional permutation vector.
    PermutationVector
    create_permutation_vector(size_t v0);
    /// Creates a 2-dimensional permutation vector.
    ///
    /// @param v0
    ///     The 1st value.
    /// @param v1
    ///     The 2nd value.
    /// @returns
    ///     A 2-dimensional permutation vector.
    PermutationVector
    create_permutation_vector(size_t v0, size_t v1);
    /// Creates a 3-dimensional permutation vector.
    ///
    /// @param v0
    ///     The 1st value.
    /// @param v1
    ///     The 2nd value.
    /// @param v2
    ///     The 3rd value.
    /// @returns
    ///     A 3-dimensional permutation vector.
    PermutationVector
    create_permutation_vector(size_t v0, size_t v1, size_t v2);
    /// Creates a 4-dimensional permutation vector.
    ///
    /// @param v0
    ///     The 1st value.
    /// @param v1
    ///     The 2nd value.
    /// @param v2
    ///     The 3rd value.
    /// @param v3
    ///     The 4th value.
    /// @returns
    ///     A 4-dimensional permutation vector.
    PermutationVector
    create_permutation_vector(size_t v0, size_t v1, size_t v2, size_t v3);
    /// Creates a 5-dimensional permutation vector.
    ///
    /// @param v0
    ///     The 1st value.
    /// @param v1
    ///     The 2nd value.
    /// @param v2
    ///     The 3rd value.
    /// @param v3
    ///     The 4th value.
    /// @param v4
    ///     The 5th value.
    /// @returns
    ///     A 5-dimensional permutation vector.
    PermutationVector
    create_permutation_vector(size_t v0,
                              size_t v1,
                              size_t v2,
                              size_t v3,
                              size_t v4);
}
}

#endif
