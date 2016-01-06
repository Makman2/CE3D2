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

BOOST_AUTO_TEST_SUITE_END()
