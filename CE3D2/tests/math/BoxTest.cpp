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

BOOST_AUTO_TEST_SUITE_END()
