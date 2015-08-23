#ifndef CE3D2_TESTS_TESTUTILITIES_H
#define CE3D2_TESTS_TESTUTILITIES_H

#include <boost/test/unit_test.hpp>


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

#endif
