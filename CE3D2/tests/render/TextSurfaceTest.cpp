#define BOOST_TEST_MODULE TextSurfaceTest
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "CE3D2/render/TextSurface.h"


BOOST_AUTO_TEST_SUITE(TextSurfaceTestSuite)

BOOST_AUTO_TEST_CASE(test_initialization)
{
    CE3D2::Render::TextSurface uut(2, 3);

    BOOST_CHECK_EQUAL(uut(0, 0), ' ');
    BOOST_CHECK_EQUAL(uut(0, 1), ' ');
    BOOST_CHECK_EQUAL(uut(0, 2), ' ');
    BOOST_CHECK_EQUAL(uut(1, 0), ' ');
    BOOST_CHECK_EQUAL(uut(1, 1), ' ');
    BOOST_CHECK_EQUAL(uut(1, 2), ' ');
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

    BOOST_CHECK_EQUAL(uut(0, 0), 'y');
    BOOST_CHECK_EQUAL(uut(0, 1), 'y');
    BOOST_CHECK_EQUAL(uut(1, 0), 'y');
    BOOST_CHECK_EQUAL(uut(1, 1), 'y');

    uut.clear();

    BOOST_CHECK_EQUAL(uut(0, 0), ' ');
    BOOST_CHECK_EQUAL(uut(0, 1), ' ');
    BOOST_CHECK_EQUAL(uut(1, 0), ' ');
    BOOST_CHECK_EQUAL(uut(1, 1), ' ');
}

BOOST_AUTO_TEST_CASE(test_partial_fill)
{
    CE3D2::Render::TextSurface uut(10, 10);

    BOOST_CHECK_EQUAL(uut(6, 4), ' ');
    BOOST_CHECK_EQUAL(uut(7, 5), ' ');
    BOOST_CHECK_EQUAL(uut(6, 4), ' ');
    BOOST_CHECK_EQUAL(uut(7, 5), ' ');

    uut.fill('x', 6, 4, 2, 2);

    BOOST_CHECK_EQUAL(uut(6, 4), 'x');
    BOOST_CHECK_EQUAL(uut(6, 5), 'x');
    BOOST_CHECK_EQUAL(uut(7, 4), 'x');
    BOOST_CHECK_EQUAL(uut(7, 5), 'x');
    // Check all around the filled area.
    BOOST_CHECK_EQUAL(uut(5, 3), ' ');
    BOOST_CHECK_EQUAL(uut(5, 4), ' ');
    BOOST_CHECK_EQUAL(uut(5, 5), ' ');
    BOOST_CHECK_EQUAL(uut(5, 6), ' ');
    BOOST_CHECK_EQUAL(uut(6, 6), ' ');
    BOOST_CHECK_EQUAL(uut(7, 6), ' ');
    BOOST_CHECK_EQUAL(uut(8, 6), ' ');
    BOOST_CHECK_EQUAL(uut(8, 5), ' ');
    BOOST_CHECK_EQUAL(uut(8, 4), ' ');
    BOOST_CHECK_EQUAL(uut(8, 3), ' ');
    BOOST_CHECK_EQUAL(uut(7, 3), ' ');
    BOOST_CHECK_EQUAL(uut(6, 3), ' ');
}

BOOST_AUTO_TEST_CASE(test_complete_fill)
{
    CE3D2::Render::TextSurface uut(3, 2);
    uut.fill('z');

    BOOST_CHECK_EQUAL(uut(0, 0), 'z');
    BOOST_CHECK_EQUAL(uut(0, 1), 'z');
    BOOST_CHECK_EQUAL(uut(1, 0), 'z');
    BOOST_CHECK_EQUAL(uut(1, 1), 'z');
    BOOST_CHECK_EQUAL(uut(2, 0), 'z');
    BOOST_CHECK_EQUAL(uut(2, 1), 'z');
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

    BOOST_CHECK_EQUAL(target(7, 7), 'B');

    target.copy_from(source, 0, 0, 2, 4, 3, 2);

    BOOST_CHECK_EQUAL(target(2, 4), 'A');
    BOOST_CHECK_EQUAL(target(3, 4), 'x');
    BOOST_CHECK_EQUAL(target(4, 4), 'D');
    BOOST_CHECK_EQUAL(target(2, 5), 'x');
    BOOST_CHECK_EQUAL(target(3, 5), 'B');
    BOOST_CHECK_EQUAL(target(4, 5), 'x');
}

BOOST_AUTO_TEST_CASE(test_copy_from_source_to_coords)
{
    CE3D2::Render::TextSurface source(2, 2);
    source.fill('0');
    source(1, 1) = 'h';

    CE3D2::Render::TextSurface target(4, 4);
    target.copy_from(source, 1, 1);

    BOOST_CHECK_EQUAL(target(0, 0), ' ');
    BOOST_CHECK_EQUAL(target(0, 1), ' ');
    BOOST_CHECK_EQUAL(target(0, 2), ' ');
    BOOST_CHECK_EQUAL(target(0, 3), ' ');
    BOOST_CHECK_EQUAL(target(1, 0), ' ');
    BOOST_CHECK_EQUAL(target(1, 1), '0');
    BOOST_CHECK_EQUAL(target(1, 2), '0');
    BOOST_CHECK_EQUAL(target(1, 3), ' ');
    BOOST_CHECK_EQUAL(target(2, 0), ' ');
    BOOST_CHECK_EQUAL(target(2, 1), '0');
    BOOST_CHECK_EQUAL(target(2, 2), 'h');
    BOOST_CHECK_EQUAL(target(2, 3), ' ');
    BOOST_CHECK_EQUAL(target(3, 0), ' ');
    BOOST_CHECK_EQUAL(target(3, 1), ' ');
    BOOST_CHECK_EQUAL(target(3, 2), ' ');
    BOOST_CHECK_EQUAL(target(3, 3), ' ');
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
