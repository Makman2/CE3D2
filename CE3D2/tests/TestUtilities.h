#ifndef CE3D2_TESTS_TESTUTILITIES_H
#define CE3D2_TESTS_TESTUTILITIES_H

#include <boost/test/unit_test.hpp>

#include "CE3D2/Vector.h"


/// Warns for vector equality.
///
/// @param a First vector to compare.
/// @param b Second vector to compare.
#define BOOST_WARN_VECTORS_EQUAL(a, b) BOOST_ASSERT_VECTORS_EQUAL(a, b, WARN)


/// Checks for vector equality.
///
/// @param a First vector to compare.
/// @param b Second vector to compare.
#define BOOST_CHECK_VECTORS_EQUAL(a, b) BOOST_ASSERT_VECTORS_EQUAL(a, b, CHECK)


/// Requires vector equality.
///
/// @param a First vector to compare.
/// @param b Second vector to compare.
#define BOOST_REQUIRE_VECTORS_EQUAL(a, b) \
    BOOST_ASSERT_VECTORS_EQUAL(a, b, REQUIRE)


/// Assert two vectors equal.
///
/// You should consider using the specializations BOOST_WARN_VECTORS_EQUAL,
/// BOOST_CHECK_VECTORS_EQUAL and BOOST_REQUIRE_VECTORS_EQUAL instead.
///
/// @param a     First vector to compare.
/// @param b     Second vector to compare.
/// @param LEVEL The assertion level. Valid values are "WARN", "CHECK" or
///              "REQUIRE".
#define BOOST_ASSERT_VECTORS_EQUAL(a, b, LEVEL)       \
{                                                     \
    BOOST_##LEVEL##_MESSAGE(                          \
        a.size() == b.size(),                         \
        "Sizes of vectors differ, " << a.size()       \
            << " != " << b.size() << ".");            \
    for (unsigned int i = 0; i < a.size(); i++)       \
    {                                                 \
        BOOST_##LEVEL##_MESSAGE(                      \
            a[i] == b[i],                             \
            "Vectors differ in element " << i << " (" \
                << a[i] << " != " << b[i] << ").");   \
    }                                                 \
}


/// Creates a vector from a list.
///
/// @param numbers The list of numbers to fill the vector with.
/// @returns       The vector filled with numbers.
CE3D2::Vector
_ce3d2_create_vector_from_list(
    std::vector<CE3D2::PrecisionType> const& numbers)
{
    CE3D2::Vector vector = CE3D2::Vector(numbers.size());
    for (CE3D2::Vector::size_type i = 0; i < vector.size(); i++)
    {
        vector[i] = numbers[i];
    }

    return vector;
}


/// Creates a CE3D2::Vector.
///
/// Creates a vector easily by filling the given parameter numbers into the
/// vector. The size of the vector is the same as the length of the parameter
/// numbers given.
///
/// For example:
/// CE3D2_CREATE_VECTOR(1.0f, 2.0f, 3.0f, 4.0f)
/// This creates a 4-dimensional vector with the numbers 1, 2, 3 and 4.
///
/// @param ...      The parameter numbers to fill the vector with.
/// @returns        The newly created vector.
#define CE3D2_CREATE_VECTOR(...)    \
    _ce3d2_create_vector_from_list( \
        std::vector<CE3D2::PrecisionType>({__VA_ARGS__}))

#endif
