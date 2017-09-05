#ifndef CE3D2_TESTS_TESTUTILITIES_H
#define CE3D2_TESTS_TESTUTILITIES_H

#include <algorithm>
#include <iomanip>
#include <boost/test/unit_test.hpp>

#include "CE3D2/Matrix.h"
#include "CE3D2/Vector.h"
#include "CE3D2/render/TextSurface.h"


/// Warns that an exception has been thrown with the given message.
///
/// @param code           The code that shall throw an exception.
/// @param exception_type The exception-type that is thrown.
/// @param message        The exception message.
#define CE3D2_WARN_EXCEPTION(code, exception_type, message) \
    CE3D2_ASSERT_EXCEPTION(code, exception_type, message, WARN)


/// Checks that an exception has been thrown with the given message.
///
/// @param code           The code that shall throw an exception.
/// @param exception_type The exception-type that is thrown.
/// @param message        The exception message.
#define CE3D2_CHECK_EXCEPTION(code, exception_type, message) \
    CE3D2_ASSERT_EXCEPTION(code, exception_type, message, CHECK)


/// Requires that an exception has been thrown with the given message.
///
/// @param code           The code that shall throw an exception.
/// @param exception_type The exception-type that is thrown.
/// @param message        The exception message.
#define CE3D2_REQUIRE_EXCEPTION(code, exception_type, message) \
    CE3D2_ASSERT_EXCEPTION(code, exception_type, message, REQUIRE)


/// Asserts that an exception has been thrown with the given message.
///
/// @param code           The code that shall throw an exception.
/// @param exception_type The exception-type that is thrown.
/// @param message        The exception message.
/// @param LEVEL          The assertion level. Valid values are "WARN", "CHECK"
///                       or "REQUIRE".
#define CE3D2_ASSERT_EXCEPTION(code, exception_type, message, LEVEL) \
    BOOST_##LEVEL##_EXCEPTION(                                       \
        code,                                                        \
        exception_type,                                              \
        [](exception_type const& ex)                                 \
            {return std::string(ex.what()) == (message);})


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


/// Warns for `IndexPair` equality.
///
/// @param A First `IndexPair` to compare.
/// @param B Second `IndexPair` to compare.
#define CE3D2_WARN_INDEX_PAIRS_EQUAL(A, B) \
    CE3D2_ASSERT_INDEX_PAIRS_EQUAL(A, B, WARN)


/// Checks for `IndexPair` equality.
///
/// @param A First `IndexPair` to compare.
/// @param B Second `IndexPair` to compare.
#define CE3D2_CHECK_INDEX_PAIRS_EQUAL(A, B) \
    CE3D2_ASSERT_INDEX_PAIRS_EQUAL(A, B, CHECK)


/// Requires `IndexPair` equality.
///
/// @param A First `IndexPair` to compare.
/// @param B Second `IndexPair` to compare.
#define CE3D2_REQUIRE_INDEX_PAIRS_EQUAL(A, B) \
    CE3D2_ASSERT_INDEX_PAIRS_EQUAL(A, B, REQUIRE)


/// Assert two `IndexPair`s equal.
///
/// You should consider using the specializations CE3D2_WARN_INDEX_PAIRS_EQUAL,
/// CE3D2_CHECK_INDEX_PAIRS_EQUAL and CE3D2_REQUIRE_INDEX_PAIRS_EQUAL instead.
///
/// @param A     First `IndexPair` to compare.
/// @param B     Second `IndexPair` to compare.
/// @param LEVEL The assertion level. Valid values are "WARN", "CHECK" or
///              "REQUIRE".
#define CE3D2_ASSERT_INDEX_PAIRS_EQUAL(A, B, LEVEL)                     \
{                                                                       \
    BOOST_##LEVEL##_MESSAGE(                                            \
        (A).first == (B).first,                                         \
        "First element of IndexPair differs, " << (A).first << " != "   \
            << (B).first << ".");                                       \
    BOOST_##LEVEL##_MESSAGE(                                            \
        (A).second == (B).second,                                       \
        "Second element of IndexPair differs, " << (A).second << " != " \
            << (B).second << ".");                                      \
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


/// Asserts that two models are equal.
///
/// @param a     First Model to compare.
/// @param b     Second Model to compare.
/// @param LEVEL The assertion level. Valid values are "WARN", "CHECK" or
///              "REQUIRE".
#define CE3D2_ASSERT_MODELS_EQUAL(a, b, LEVEL)                           \
{                                                                        \
    BOOST_##LEVEL##_EQUAL((a).get_name(), (b).get_name());               \
    BOOST_##LEVEL##_EQUAL((a).is_visible(), (b).is_visible());           \
                                                                         \
    auto const& vectors_a = (a).vectors();                               \
    auto const& vectors_b = (b).vectors();                               \
    BOOST_##LEVEL##_EQUAL(vectors_a.size(), vectors_b.size());           \
    for (CE3D2::Models::StorageType<CE3D2::Vector>::size_type k = 0;     \
         k < vectors_a.size();                                           \
         k++)                                                            \
    {                                                                    \
        CE3D2_ASSERT_VECTORS_EQUAL(vectors_a[k], vectors_b[k], LEVEL);   \
    }                                                                    \
                                                                         \
    auto const& connections_a = (a).connections();                       \
    auto const& connections_b = (b).connections();                       \
                                                                         \
    BOOST_##LEVEL##_EQUAL(connections_a.size(), connections_b.size());   \
    for (CE3D2::Models::StorageType<CE3D2::Models::IndexPair>::size_type \
             k = 0;                                                      \
         k < connections_a.size();                                       \
         k++)                                                            \
    {                                                                    \
        auto const& connection_a = connections_a[k];                     \
        auto const& connection_b = connections_b[k];                     \
                                                                         \
        bool connection_is_equal =                                       \
            connection_a.first == connection_b.first &&                  \
            connection_a.second == connection_b.second;                  \
                                                                         \
        BOOST_##LEVEL##_MESSAGE(connection_is_equal,                     \
            "Connection differs in element " << k << " ("                \
            << connection_a.first << ", " << connection_a.second         \
            << " != " <<                                                 \
            connection_b.first << ", " << connection_b.second << ").");  \
    }                                                                    \
}


/// Warns if two models are not equal.
///
/// @param a First Model to compare.
/// @param b Second Model to compare.
#define CE3D2_WARN_MODELS_EQUAL(A, B) \
    CE3D2_ASSERT_MODELS_EQUAL(A, B, WARN)


/// Checks two models being equal.
///
/// @param a First Model to compare.
/// @param b Second Model to compare.
#define CE3D2_CHECK_MODELS_EQUAL(A, B) \
    CE3D2_ASSERT_MODELS_EQUAL(A, B, CHECK)


/// Requires two models being equal.
///
/// @param a First Model to compare.
/// @param b Second Model to compare.
#define CE3D2_REQUIRE_MODELS_EQUAL(A, B) \
    CE3D2_ASSERT_MODELS_EQUAL(A, B, REQUIRE)

#endif
