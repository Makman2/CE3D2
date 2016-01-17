#define BOOST_TEST_MODULE TextSurfaceTest
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "CE3D2/render/TextSurface.h"
#include "CE3D2/tests/TestUtilities.h"


BOOST_AUTO_TEST_SUITE(TextSurfaceTestSuite)

BOOST_AUTO_TEST_CASE(test_initialization)
{
    CE3D2::Render::TextSurface uut(2, 3);

    auto expected = CE3D2_CREATE_TEXTSURFACE("  ", "  ", "  ");
    CE3D2_CHECK_TEXTSURFACES_EQUAL(uut, *expected);
}

BOOST_AUTO_TEST_CASE(test_width_and_height)
{
    CE3D2::Render::TextSurface uut(1, 1);
    BOOST_CHECK_EQUAL(uut.width(), 1);
    BOOST_CHECK_EQUAL(uut.height(), 1);

    uut = CE3D2::Render::TextSurface(100, 50);
    BOOST_CHECK_EQUAL(uut.width(), 100);
    BOOST_CHECK_EQUAL(uut.height(), 50);
}

BOOST_AUTO_TEST_CASE(test_element_access)
{
    CE3D2::Render::TextSurface uut(10, 10);

    uut(0, 0) = 'c';
    uut(9, 9) = 'b';
    uut(5, 5) = '1';
    uut(3, 7) = 'm';

    BOOST_CHECK_EQUAL(uut(0, 0), 'c');
    BOOST_CHECK_EQUAL(uut(9, 9), 'b');
    BOOST_CHECK_EQUAL(uut(5, 5), '1');
    BOOST_CHECK_EQUAL(uut(3, 7), 'm');
}

BOOST_AUTO_TEST_CASE(test_clear)
{
    CE3D2::Render::TextSurface uut(2, 2);
    uut.fill('y');

    auto expected = CE3D2_CREATE_TEXTSURFACE("yy", "yy");
    CE3D2_CHECK_TEXTSURFACES_EQUAL(uut, *expected);

    uut.clear();

    expected = CE3D2_CREATE_TEXTSURFACE("  ", "  ");
    CE3D2_CHECK_TEXTSURFACES_EQUAL(uut, *expected);
}

BOOST_AUTO_TEST_CASE(test_partial_fill)
{
    CE3D2::Render::TextSurface uut(10, 10);

    auto expected = CE3D2_CREATE_TEXTSURFACE("          ",
                                             "          ",
                                             "          ",
                                             "          ",
                                             "          ",
                                             "          ",
                                             "          ",
                                             "          ",
                                             "          ",
                                             "          ");
    CE3D2_CHECK_TEXTSURFACES_EQUAL(uut, *expected);

    uut.fill('x', 6, 4, 2, 2);

    expected = CE3D2_CREATE_TEXTSURFACE("          ",
                                        "          ",
                                        "          ",
                                        "          ",
                                        "      xx  ",
                                        "      xx  ",
                                        "          ",
                                        "          ",
                                        "          ",
                                        "          ");
    CE3D2_CHECK_TEXTSURFACES_EQUAL(uut, *expected);
}

BOOST_AUTO_TEST_CASE(test_complete_fill)
{
    CE3D2::Render::TextSurface uut(3, 2);
    uut.fill('z');

    auto expected = CE3D2_CREATE_TEXTSURFACE("zzz", "zzz");
    CE3D2_CHECK_TEXTSURFACES_EQUAL(uut, *expected);
}

BOOST_AUTO_TEST_CASE(test_copy_from_source)
{
    CE3D2::Render::TextSurface source(3, 3);
    source.fill('x');
    source(0, 0) = 'A';
    source(1, 1) = 'B';
    source(2, 2) = 'C';
    source(2, 0) = 'D';

    CE3D2::Render::TextSurface target(9, 9);
    target.copy_from(source, 1, 1, 7, 7, 1, 1);

    auto expected = CE3D2_CREATE_TEXTSURFACE("         ",
                                             "         ",
                                             "         ",
                                             "         ",
                                             "         ",
                                             "         ",
                                             "         ",
                                             "       B ",
                                             "         ");
    CE3D2_CHECK_TEXTSURFACES_EQUAL(target, *expected);

    target.copy_from(source, 0, 0, 2, 4, 3, 2);

    expected = CE3D2_CREATE_TEXTSURFACE("         ",
                                        "         ",
                                        "         ",
                                        "         ",
                                        "  AxD    ",
                                        "  xBx    ",
                                        "         ",
                                        "       B ",
                                        "         ");
    CE3D2_CHECK_TEXTSURFACES_EQUAL(target, *expected);
}

BOOST_AUTO_TEST_CASE(test_copy_from_source_to_coords)
{
    CE3D2::Render::TextSurface source(2, 2);
    source.fill('0');
    source(1, 1) = 'h';

    CE3D2::Render::TextSurface target(4, 4);
    target.copy_from(source, 1, 1);

    auto expected = CE3D2_CREATE_TEXTSURFACE("    ", " 00 ", " 0h ", "    ");
    CE3D2_CHECK_TEXTSURFACES_EQUAL(target, *expected);
}

BOOST_AUTO_TEST_CASE(test_copy_from_source_completely)
{
    CE3D2::Render::TextSurface source(10, 10);
    source.fill('7');

    CE3D2::Render::TextSurface target(10, 15);
    target.copy_from(source);

    for (CE3D2::Render::TextSurface::size_type x = 0; x < 10; x++)
    {
        for (CE3D2::Render::TextSurface::size_type y = 0; y < 10; y++)
        {
            BOOST_CHECK_EQUAL(target(x, y), '7');
        }
    }
    for (CE3D2::Render::TextSurface::size_type x = 0; x < 10; x++)
    {
        for (CE3D2::Render::TextSurface::size_type y = 10; y < 15; y++)
        {
            BOOST_CHECK_EQUAL(target(x, y), ' ');
        }
    }
}

BOOST_AUTO_TEST_CASE(test_is_boundary_valid_point)
{
    CE3D2::Render::TextSurface uut(20, 24);

    // Check corners.
    BOOST_CHECK(uut.is_boundary_valid(0, 0));
    BOOST_CHECK(uut.is_boundary_valid(19, 0));
    BOOST_CHECK(uut.is_boundary_valid(19, 23));
    BOOST_CHECK(uut.is_boundary_valid(0, 23));

    // Check some points from inside of the surface.
    BOOST_CHECK(uut.is_boundary_valid(2, 11));
    BOOST_CHECK(uut.is_boundary_valid(11, 2));
    BOOST_CHECK(uut.is_boundary_valid(13, 7));
    BOOST_CHECK(uut.is_boundary_valid(5, 22));

    // Check beyond corners.
    BOOST_CHECK(!uut.is_boundary_valid(20, 0));
    BOOST_CHECK(!uut.is_boundary_valid(20, 23));
    BOOST_CHECK(!uut.is_boundary_valid(20, 24));
    BOOST_CHECK(!uut.is_boundary_valid(19, 24));
    BOOST_CHECK(!uut.is_boundary_valid(0, 24));

    // Check somewhere far far away.
    BOOST_CHECK(!uut.is_boundary_valid(100, 100));
    BOOST_CHECK(!uut.is_boundary_valid(77, 8));
    BOOST_CHECK(!uut.is_boundary_valid(8, 77));
    BOOST_CHECK(!uut.is_boundary_valid(12312, 99999));
}

BOOST_AUTO_TEST_CASE(test_is_boundary_valid_block)
{
    CE3D2::Render::TextSurface uut(10, 10);

    // Check inside.
    BOOST_CHECK(uut.is_boundary_valid(0, 0, 10, 10));
    BOOST_CHECK(uut.is_boundary_valid(9, 9, 1, 1));
    BOOST_CHECK(uut.is_boundary_valid(2, 4, 4, 5));

    // Check partially outside.
    BOOST_CHECK(!uut.is_boundary_valid(0, 0, 4, 11));
    BOOST_CHECK(!uut.is_boundary_valid(0, 0, 11, 7));
    BOOST_CHECK(!uut.is_boundary_valid(8, 7, 20, 12));

    // Check completely outside.
    BOOST_CHECK(!uut.is_boundary_valid(10, 10, 1, 1));
    BOOST_CHECK(!uut.is_boundary_valid(10, 10, 10, 10));
    BOOST_CHECK(!uut.is_boundary_valid(10, 2, 5, 5));
    BOOST_CHECK(!uut.is_boundary_valid(2, 10, 7, 7));
    BOOST_CHECK(!uut.is_boundary_valid(15, 72, 20, 88));
}

BOOST_AUTO_TEST_SUITE_END()
