#ifndef CE3D2_TESTS_TESTUTILITIES_H
#define CE3D2_TESTS_TESTUTILITIES_H

#include <algorithm>
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


/// Compares the length of two strings.
///
/// @param a The first string to compare.
/// @param b The second string to compare.
/// @returns If the size of `a` is smaller than the size of `b`.
bool
_compare_string_sizes(std::string const& a, std::string const& b)
{
    return a.length() < b.length();
}


/// Creates a TextSurface.
///
/// @param data A vector of strings where each string represents a single row of
///             the TextSurface to create. Width of the surface is determined
///             from the longest string in `data`, height from the number of
///             elements in it.
/// @returns    The TextSurface.
std::shared_ptr<CE3D2::Render::TextSurface>
_create_textsurface(std::vector<std::string> const& data)
{
    auto width = static_cast<CE3D2::Render::TextSurface::size_type>(
        std::max_element(data.cbegin(),
                         data.cend(),
                         _compare_string_sizes)->length());
    auto height = static_cast<CE3D2::Render::TextSurface::size_type>(
        data.size());

    auto surface = std::make_shared<CE3D2::Render::TextSurface>(width, height);

    for (std::vector<std::string>::size_type s = 0; s < data.size(); s++)
    {
        auto const& current_string = data[s];

        auto y = static_cast<CE3D2::Render::TextSurface::size_type>(s);

        for (std::string::size_type l = 0; l < current_string.length(); l++)
        {
            auto x = static_cast<CE3D2::Render::TextSurface::size_type>(l);

            (*surface)(x, y) = current_string[l];
        }
    }

    return surface;
}


/// Creates a TextSurface.
///
/// @param ... Parameters of strings where each string represents a single row
///            of the TextSurface to create. Width of the surface is determined
///            from the longest string in `data`, height from the number of
///            elements in it.
///
///            For example:
///            CE3D2_CREATE_TEXTSURFACE(" + ", "+++", " + ")
///            This would create a 3x3 TextSurface with following content:
///
///             +
///            +++
///             +
///
/// @returns   The TextSurface.
#define CE3D2_CREATE_TEXTSURFACE(...) \
    _create_textsurface(std::vector<std::string>({__VA_ARGS__}))

#endif
