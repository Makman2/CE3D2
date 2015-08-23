#define BOOST_TEST_MODULE VectorTest
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "CE3D2/Vector.h"


BOOST_AUTO_TEST_SUITE(VectorTestSuite)

BOOST_AUTO_TEST_CASE(test_standard_vector)
{
    CE3D2::Vector uut(2);
    BOOST_CHECK_EQUAL(uut.size(), 2);
    uut[0] = 0.0f;
    uut[1] = 0.0f;
    BOOST_CHECK_EQUAL(uut[0], 0.0f);
    BOOST_CHECK_EQUAL(uut[1], 0.0f);

    uut = CE3D2::Vector(4);
    BOOST_CHECK_EQUAL(uut.size(), 4);
    uut[0] = 1.0f;
    uut[1] = 0.0f;
    uut[2] = 37.4f;
    uut[3] = -10.0f;
    BOOST_CHECK_EQUAL(uut[0], 1.0f);
    BOOST_CHECK_EQUAL(uut[1], 0.0f);
    BOOST_CHECK_EQUAL(uut[2], 37.4f);
    BOOST_CHECK_EQUAL(uut[3], -10.0f);
}

BOOST_AUTO_TEST_CASE(test_unit_vector)
{
    CE3D2::UnitVector uut(3, 0);
    BOOST_CHECK_EQUAL(uut.size(), 3);
    BOOST_CHECK_EQUAL(uut[0], 1.0f);
    BOOST_CHECK_EQUAL(uut[1], 0.0f);
    BOOST_CHECK_EQUAL(uut[2], 0.0f);

    uut = CE3D2::UnitVector(3, 2);
    BOOST_CHECK_EQUAL(uut.size(), 3);
    BOOST_CHECK_EQUAL(uut[0], 0.0f);
    BOOST_CHECK_EQUAL(uut[1], 0.0f);
    BOOST_CHECK_EQUAL(uut[2], 1.0f);

    uut = CE3D2::UnitVector(5, 3);
    BOOST_CHECK_EQUAL(uut.size(), 5);
    BOOST_CHECK_EQUAL(uut[0], 0.0f);
    BOOST_CHECK_EQUAL(uut[1], 0.0f);
    BOOST_CHECK_EQUAL(uut[2], 0.0f);
    BOOST_CHECK_EQUAL(uut[3], 1.0f);
    BOOST_CHECK_EQUAL(uut[4], 0.0f);
}

BOOST_AUTO_TEST_CASE(test_zero_vector)
{
    CE3D2::ZeroVector uut(1);
    BOOST_CHECK_EQUAL(uut.size(), 1);
    BOOST_CHECK_EQUAL(uut[0], 0.0f);

    uut = CE3D2::ZeroVector(2);
    BOOST_CHECK_EQUAL(uut.size(), 2);
    BOOST_CHECK_EQUAL(uut[0], 0.0f);
    BOOST_CHECK_EQUAL(uut[1], 0.0f);

    uut = CE3D2::ZeroVector(3);
    BOOST_CHECK_EQUAL(uut.size(), 3);
    BOOST_CHECK_EQUAL(uut[0], 0.0f);
    BOOST_CHECK_EQUAL(uut[1], 0.0f);
    BOOST_CHECK_EQUAL(uut[2], 0.0f);
}

BOOST_AUTO_TEST_SUITE_END()
