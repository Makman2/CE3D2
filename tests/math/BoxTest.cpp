#define BOOST_TEST_MODULE BoxTest
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "CE3D2/math/Box.h"


BOOST_AUTO_TEST_SUITE(BoxTestSuite)

BOOST_AUTO_TEST_CASE(test_construction)
{
    CE3D2::Math::Box uut(7.0f, 3.0f, 10.0f, 12.0f);
    BOOST_CHECK_EQUAL(uut.x, 7.0f);
    BOOST_CHECK_EQUAL(uut.y, 3.0f);
    BOOST_CHECK_EQUAL(uut.width, 10.0f);
    BOOST_CHECK_EQUAL(uut.height, 12.0f);

    uut = CE3D2::Math::Box(100.0f, 200.0f);
    BOOST_CHECK_EQUAL(uut.x, 0.0f);
    BOOST_CHECK_EQUAL(uut.y, 0.0f);
    BOOST_CHECK_EQUAL(uut.width, 100.0f);
    BOOST_CHECK_EQUAL(uut.height, 200.0f);
}

BOOST_AUTO_TEST_CASE(test_contains_box)
{
    CE3D2::Math::Box uut(1.0f, 2.0f, 3.0f, 4.0f);
    BOOST_CHECK(uut.contains(uut));

    // Completely inside.
    CE3D2::Math::Box other_box(2.0f, 3.0f, 1.0f, 2.0f);
    BOOST_CHECK(uut.contains(other_box));

    // Partially inside.
    other_box = CE3D2::Math::Box(-1.0f, 2.0f, 3.0f, 4.0f);
    BOOST_CHECK(!uut.contains(other_box));

    // Absolutely not inside.
    other_box = CE3D2::Math::Box(0.0f, 0.0f, 2.0f, 2.0f);
    BOOST_CHECK(!uut.contains(other_box));
}

BOOST_AUTO_TEST_CASE(test_contains_point)
{
    CE3D2::Math::Box uut(1.0f, 2.0f, 3.0f, 4.0f);
    // Point is inside.
    BOOST_CHECK(uut.contains(2.0f, 3.0f));
    BOOST_CHECK(uut.contains(1.5f, 5.5f));
    // Point resides on edge.
    BOOST_CHECK(uut.contains(1.0f, 4.0f));
    BOOST_CHECK(uut.contains(2.0f, 6.0f));
    BOOST_CHECK(uut.contains(4.0f, 3.0f));
    BOOST_CHECK(uut.contains(3.0f, 2.0f));
    // Point resides in corner.
    BOOST_CHECK(uut.contains(1.0f, 2.0f));
    BOOST_CHECK(uut.contains(1.0f, 6.0f));
    BOOST_CHECK(uut.contains(4.0f, 2.0f));
    BOOST_CHECK(uut.contains(4.0f, 6.0f));
    // Point is not inside.
    BOOST_CHECK(!uut.contains(0.0f, 0.0f));
    BOOST_CHECK(!uut.contains(-1.0f, 3.0f));
    BOOST_CHECK(!uut.contains(0.5f, 10.0f));
    BOOST_CHECK(!uut.contains(3.0f, 7.0f));
    BOOST_CHECK(!uut.contains(11.0f, 22.0f));
    BOOST_CHECK(!uut.contains(5.0f, 4.0f));
    BOOST_CHECK(!uut.contains(6.0f, 0.0f));
    BOOST_CHECK(!uut.contains(2.0f, -1.0f));
}

BOOST_AUTO_TEST_CASE(test_inside)
{
    CE3D2::Math::Box uut(1.0f, 2.0f, 3.0f, 4.0f);
    BOOST_CHECK(uut.inside(uut));

    // Completely inside.
    CE3D2::Math::Box other_box(2.0f, 3.0f, 1.0f, 2.0f);
    BOOST_CHECK(other_box.inside(uut));

    // Partially inside.
    other_box = CE3D2::Math::Box(-1.0f, 2.0f, 3.0f, 4.0f);
    BOOST_CHECK(!other_box.inside(uut));

    // Absolutely not inside.
    other_box = CE3D2::Math::Box(0.0f, 0.0f, 2.0f, 2.0f);
    BOOST_CHECK(!other_box.inside(uut));
}

BOOST_AUTO_TEST_SUITE_END()
