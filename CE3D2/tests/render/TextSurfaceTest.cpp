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
    BOOST_CHECK_EQUAL(uut(1, 0), ' ');
    BOOST_CHECK_EQUAL(uut(1, 1), ' ');
    BOOST_CHECK_EQUAL(uut(2, 0), ' ');
    BOOST_CHECK_EQUAL(uut(2, 1), ' ');
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

    // Check a single element to see whether something was set.
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
    BOOST_CHECK_EQUAL(uut(0, 2), 'z');
    BOOST_CHECK_EQUAL(uut(1, 0), 'z');
    BOOST_CHECK_EQUAL(uut(1, 1), 'z');
    BOOST_CHECK_EQUAL(uut(1, 2), 'z');
}

BOOST_AUTO_TEST_CASE(test_is_boundary_valid_point)
{
    CE3D2::Render::TextSurface uut(20, 24);

    // Check corners.
    BOOST_CHECK(uut.is_boundary_valid(0, 0));
    BOOST_CHECK(uut.is_boundary_valid(0, 19));
    BOOST_CHECK(uut.is_boundary_valid(23, 19));
    BOOST_CHECK(uut.is_boundary_valid(23, 0));

    // Check some points from inside of the surface.
    BOOST_CHECK(uut.is_boundary_valid(11, 2));
    BOOST_CHECK(uut.is_boundary_valid(2, 11));
    BOOST_CHECK(uut.is_boundary_valid(7, 13));
    BOOST_CHECK(uut.is_boundary_valid(22, 5));

    // Check beyond corners.
    BOOST_CHECK(!uut.is_boundary_valid(0, 20));
    BOOST_CHECK(!uut.is_boundary_valid(23, 20));
    BOOST_CHECK(!uut.is_boundary_valid(24, 20));
    BOOST_CHECK(!uut.is_boundary_valid(24, 19));
    BOOST_CHECK(!uut.is_boundary_valid(24, 0));

    // Check somewhere far far away.
    BOOST_CHECK(!uut.is_boundary_valid(100, 100));
    BOOST_CHECK(!uut.is_boundary_valid(8, 77));
    BOOST_CHECK(!uut.is_boundary_valid(77, 8));
    BOOST_CHECK(!uut.is_boundary_valid(99999, 12312));
}

BOOST_AUTO_TEST_CASE(test_is_boundary_valid_block)
{
    CE3D2::Render::TextSurface uut(10, 10);

    // Check inside.
    BOOST_CHECK(uut.is_boundary_valid(0, 0, 10, 10));
    BOOST_CHECK(uut.is_boundary_valid(9, 9, 1, 1));
    BOOST_CHECK(uut.is_boundary_valid(4, 2, 4, 5));

    // Check partially outside.
    BOOST_CHECK(!uut.is_boundary_valid(0, 0, 4, 11));
    BOOST_CHECK(!uut.is_boundary_valid(0, 0, 11, 7));
    BOOST_CHECK(!uut.is_boundary_valid(7, 8, 20, 12));

    // Check completely outside.
    BOOST_CHECK(!uut.is_boundary_valid(10, 10, 1, 1));
    BOOST_CHECK(!uut.is_boundary_valid(10, 10, 10, 10));
    BOOST_CHECK(!uut.is_boundary_valid(2, 10, 5, 5));
    BOOST_CHECK(!uut.is_boundary_valid(10, 2, 7, 7));
    BOOST_CHECK(!uut.is_boundary_valid(72, 15, 20, 88));
}

BOOST_AUTO_TEST_SUITE_END()
