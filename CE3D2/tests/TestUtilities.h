#ifndef CE3D2_TESTS_TESTUTILITIES_H
#define CE3D2_TESTS_TESTUTILITIES_H

#include <iomanip>
#include <boost/test/unit_test.hpp>

#include "CE3D2/Matrix.h"
#include "CE3D2/Vector.h"
#include "CE3D2/render/TextSurface.h"


/// Warns for vector equality.
///
/// @param a First vector to compare.
/// @param b Second vector to compare.
#define CE3D2_WARN_VECTORS_EQUAL(a, b) CE3D2_ASSERT_VECTORS_EQUAL(a, b, WARN)


/// Checks for vector equality.
///
/// @param a First vector to compare.
/// @param b Second vector to compare.
#define CE3D2_CHECK_VECTORS_EQUAL(a, b) CE3D2_ASSERT_VECTORS_EQUAL(a, b, CHECK)


/// Requires vector equality.
///
/// @param a First vector to compare.
/// @param b Second vector to compare.
#define CE3D2_REQUIRE_VECTORS_EQUAL(a, b) \
    CE3D2_ASSERT_VECTORS_EQUAL(a, b, REQUIRE)


/// Assert two vectors equal.
///
/// You should consider using the specializations CE3D2_WARN_VECTORS_EQUAL,
/// CE3D2_CHECK_VECTORS_EQUAL and CE3D2_REQUIRE_VECTORS_EQUAL instead.
///
/// @param a     First vector to compare.
/// @param b     Second vector to compare.
/// @param LEVEL The assertion level. Valid values are "WARN", "CHECK" or
///              "REQUIRE".
#define CE3D2_ASSERT_VECTORS_EQUAL(a, b, LEVEL)               \
{                                                             \
    BOOST_##LEVEL##_MESSAGE(                                  \
        (a).size() == (b).size(),                             \
        "Sizes of vectors differ, " << (a).size()             \
            << " != " << (b).size() << ".");                  \
    for (CE3D2::Vector::size_type i = 0; i < (a).size(); i++) \
    {                                                         \
        BOOST_##LEVEL##_MESSAGE(                              \
            (a)[i] == (b)[i],                                 \
            "Vectors differ in element " << i << " ("         \
                << std::setprecision(8) << (a)[i]             \
                << " != " << std::setprecision(8)             \
                << (b)[i] << ").");                           \
    }                                                         \
}


/// Warns for matrix equality.
///
/// @param A First matrix to compare.
/// @param B Second matrix to compare.
#define CE3D2_WARN_MATRICES_EQUAL(A, B) CE3D2_ASSERT_MATRICES_EQUAL(A, B, WARN)


/// Checks for matrix equality.
///
/// @param A First matrix to compare.
/// @param B Second matrix to compare.
#define CE3D2_CHECK_MATRICES_EQUAL(A, B) \
    CE3D2_ASSERT_MATRICES_EQUAL(A, B, CHECK)


/// Requires matrix equality.
///
/// @param A First matrix to compare.
/// @param B Second matrix to compare.
#define CE3D2_REQUIRE_MATRICES_EQUAL(A, B) \
    CE3D2_ASSERT_MATRICES_EQUAL(A, B, REQUIRE)


/// Assert two matrices equal.
///
/// You should consider using the specializations CE3D2_WARN_MATRICES_EQUAL,
/// CE3D2_CHECK_MATRICES_EQUAL and CE3D2_REQUIRE_MATRICES_EQUAL instead.
///
/// @param A     First matrix to compare.
/// @param B     Second matrix to compare.
/// @param LEVEL The assertion level. Valid values are "WARN", "CHECK" or
///              "REQUIRE".
#define CE3D2_ASSERT_MATRICES_EQUAL(A, B, LEVEL)                       \
{                                                                      \
    BOOST_##LEVEL##_MESSAGE(                                           \
        (A).size1() == (B).size1(),                                    \
        "Row size of matrices differ, " << (A).size1() << " != "       \
            << (B).size1() << ".");                                    \
    BOOST_##LEVEL##_MESSAGE(                                           \
        (A).size2() == (B).size2(),                                    \
        "Column size of matrices differ, " << (A).size2() << " != "    \
            << (B).size2() << ".");                                    \
    for (CE3D2::Matrix::size_type r = 0; r < (A).size1(); r++)         \
    {                                                                  \
        for (CE3D2::Matrix::size_type c = 0; c < (A).size2(); c++)     \
        {                                                              \
            BOOST_##LEVEL##_MESSAGE(                                   \
                (A)(r, c) == (B)(r, c),                                \
                "Matrices differ in element " << r << "," << c << " (" \
                    << std::setprecision(8) << (A)(r, c) << " != "     \
                    << std::setprecision(8) << (B)(r, c) << ").");     \
        }                                                              \
    }                                                                  \
}


/// Warns for TextSurface equality.
///
/// @param A First TextSurface to compare.
/// @param B Second TextSurface to compare.
#define CE3D2_WARN_TEXTSURFACES_EQUAL(A, B) \
    CE3D2_ASSERT_TEXTSURFACES_EQUAL(A, B, WARN)


/// Checks for TextSurface equality.
///
/// @param A First TextSurface to compare.
/// @param B Second TextSurface to compare.
#define CE3D2_CHECK_TEXTSURFACES_EQUAL(A, B) \
    CE3D2_ASSERT_TEXTSURFACES_EQUAL(A, B, CHECK)


/// Requires TextSurface equality.
///
/// @param A First TextSurface to compare.
/// @param B Second TextSurface to compare.
#define CE3D2_REQUIRE_TEXTSURFACES_EQUAL(A, B) \
    CE3D2_ASSERT_TEXTSURFACES_EQUAL(A, B, REQUIRE)


/// Assert two TextSurface's equal.
///
/// You should consider using the specializations CE3D2_WARN_TEXTSURFACES_EQUAL,
/// CE3D2_CHECK_TEXTSURFACES_EQUAL and CE3D2_REQUIRE_TEXTSURFACES_EQUAL instead.
///
/// @param A     First TextSurface to compare.
/// @param B     Second TextSurface to compare.
/// @param LEVEL The assertion level. Valid values are "WARN", "CHECK" or
///              "REQUIRE".
#define CE3D2_ASSERT_TEXTSURFACES_EQUAL(A, B, LEVEL)                          \
{                                                                             \
    BOOST_##LEVEL##_MESSAGE(                                                  \
        (A).width() == (B).width(),                                           \
        "Widths of TextSurface's differ, " << (A).width() << " != "           \
            << (B).width() << ".");                                           \
    BOOST_##LEVEL##_MESSAGE(                                                  \
        (A).height() == (B).height(),                                         \
        "Heights of TextSurface's differ, " << (A).height() << " != "         \
            << (B).height() << ".");                                          \
    for (CE3D2::Render::TextSurface::size_type x = 0; x < (A).width(); x++)   \
    {                                                                         \
        for (CE3D2::Render::TextSurface::size_type y = 0;                     \
             y < (A).height();                                                \
             y++)                                                             \
        {                                                                     \
            BOOST_##LEVEL##_MESSAGE(                                          \
                (A)(x, y) == (B)(x, y),                                       \
                "TextSurface's differ in coordinates " << x << "," << y       \
                    << " ('" << (A)(x, y) << "' != '" << (B)(x, y) << "')."); \
        }                                                                     \
    }                                                                         \
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
