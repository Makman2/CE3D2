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

BOOST_AUTO_TEST_CASE(test_create_vector_1D)
{
    auto vec = CE3D2::create_vector(5.0f);
    BOOST_CHECK_EQUAL(vec.size(), 1);
    BOOST_CHECK_EQUAL(vec[0], 5.0f);

    vec = CE3D2::create_vector(22.478f);
    BOOST_CHECK_EQUAL(vec.size(), 1);
    BOOST_CHECK_EQUAL(vec[0], 22.478f);
}

BOOST_AUTO_TEST_CASE(test_create_vector_2D)
{
    auto vec = CE3D2::create_vector(1.0f, 2.0f);
    BOOST_CHECK_EQUAL(vec.size(), 2);
    BOOST_CHECK_EQUAL(vec[0], 1.0f);
    BOOST_CHECK_EQUAL(vec[1], 2.0f);

    vec = CE3D2::create_vector(23.479f, -2.4f);
    BOOST_CHECK_EQUAL(vec.size(), 2);
    BOOST_CHECK_EQUAL(vec[0], 23.479f);
    BOOST_CHECK_EQUAL(vec[1], -2.4f);
}

BOOST_AUTO_TEST_CASE(test_create_vector_3D)
{
    auto vec = CE3D2::create_vector(1.0f, 2.0f, 4.0f);
    BOOST_CHECK_EQUAL(vec.size(), 3);
    BOOST_CHECK_EQUAL(vec[0], 1.0f);
    BOOST_CHECK_EQUAL(vec[1], 2.0f);
    BOOST_CHECK_EQUAL(vec[2], 4.0f);

    vec = CE3D2::create_vector(111.1f, -0.5f, 88.0f);
    BOOST_CHECK_EQUAL(vec.size(), 3);
    BOOST_CHECK_EQUAL(vec[0], 111.1f);
    BOOST_CHECK_EQUAL(vec[1], -0.5f);
    BOOST_CHECK_EQUAL(vec[2], 88.0f);
}

BOOST_AUTO_TEST_CASE(test_create_vector_4D)
{
    auto vec = CE3D2::create_vector(1.0f, 2.0f, 4.0f, 9.0f);
    BOOST_CHECK_EQUAL(vec.size(), 4);
    BOOST_CHECK_EQUAL(vec[0], 1.0f);
    BOOST_CHECK_EQUAL(vec[1], 2.0f);
    BOOST_CHECK_EQUAL(vec[2], 4.0f);
    BOOST_CHECK_EQUAL(vec[3], 9.0f);

    vec = CE3D2::create_vector(111.1f, -0.5f, 88.0f, 7.0f);
    BOOST_CHECK_EQUAL(vec.size(), 4);
    BOOST_CHECK_EQUAL(vec[0], 111.1f);
    BOOST_CHECK_EQUAL(vec[1], -0.5f);
    BOOST_CHECK_EQUAL(vec[2], 88.0f);
    BOOST_CHECK_EQUAL(vec[3], 7.0f);
}

BOOST_AUTO_TEST_CASE(test_create_vector_5D)
{
    auto vec = CE3D2::create_vector(1.0f, 2.0f, 4.0f, 9.0f, 18.0f);
    BOOST_CHECK_EQUAL(vec.size(), 5);
    BOOST_CHECK_EQUAL(vec[0], 1.0f);
    BOOST_CHECK_EQUAL(vec[1], 2.0f);
    BOOST_CHECK_EQUAL(vec[2], 4.0f);
    BOOST_CHECK_EQUAL(vec[3], 9.0f);
    BOOST_CHECK_EQUAL(vec[4], 18.0f);

    vec = CE3D2::create_vector(111.1f, -0.5f, 88.0f, 7.0f, -3.0f);
    BOOST_CHECK_EQUAL(vec.size(), 5);
    BOOST_CHECK_EQUAL(vec[0], 111.1f);
    BOOST_CHECK_EQUAL(vec[1], -0.5f);
    BOOST_CHECK_EQUAL(vec[2], 88.0f);
    BOOST_CHECK_EQUAL(vec[3], 7.0f);
    BOOST_CHECK_EQUAL(vec[4], -3.0f);
}

BOOST_AUTO_TEST_SUITE_END()
