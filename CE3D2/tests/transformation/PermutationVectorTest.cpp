#define BOOST_TEST_MODULE PermutationVectorTest
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "CE3D2/transformation/PermutationVector.h"


BOOST_AUTO_TEST_SUITE(PermutationVectorTestSuite)

BOOST_AUTO_TEST_CASE(test_vector)
{
    CE3D2::Transformation::PermutationVector uut(2);
    BOOST_CHECK_EQUAL(uut.size(), 2);
    uut[0] = 0;
    uut[1] = 0;
    BOOST_CHECK_EQUAL(uut[0], 0);
    BOOST_CHECK_EQUAL(uut[1], 0);

    uut = CE3D2::Transformation::PermutationVector(4);
    BOOST_CHECK_EQUAL(uut.size(), 4);
    uut[0] = 1;
    uut[1] = 0;
    uut[2] = 37;
    uut[3] = 10;
    BOOST_CHECK_EQUAL(uut[0], 1);
    BOOST_CHECK_EQUAL(uut[1], 0);
    BOOST_CHECK_EQUAL(uut[2], 37);
    BOOST_CHECK_EQUAL(uut[3], 10);
}

BOOST_AUTO_TEST_CASE(test_create_vector_1D)
{
    auto vec = CE3D2::Transformation::create_permutation_vector(5);
    BOOST_CHECK_EQUAL(vec.size(), 1);
    BOOST_CHECK_EQUAL(vec[0], 5);
}

BOOST_AUTO_TEST_CASE(test_create_vector_2D)
{
    auto vec = CE3D2::Transformation::create_permutation_vector(1, 2);
    BOOST_CHECK_EQUAL(vec.size(), 2);
    BOOST_CHECK_EQUAL(vec[0], 1);
    BOOST_CHECK_EQUAL(vec[1], 2);
}

BOOST_AUTO_TEST_CASE(test_create_vector_3D)
{
    auto vec = CE3D2::Transformation::create_permutation_vector(111, 3, 88);
    BOOST_CHECK_EQUAL(vec.size(), 3);
    BOOST_CHECK_EQUAL(vec[0], 111);
    BOOST_CHECK_EQUAL(vec[1], 3);
    BOOST_CHECK_EQUAL(vec[2], 88);
}

BOOST_AUTO_TEST_CASE(test_create_vector_4D)
{
    auto vec = CE3D2::Transformation::create_permutation_vector(1, 2, 4, 9);
    BOOST_CHECK_EQUAL(vec.size(), 4);
    BOOST_CHECK_EQUAL(vec[0], 1);
    BOOST_CHECK_EQUAL(vec[1], 2);
    BOOST_CHECK_EQUAL(vec[2], 4);
    BOOST_CHECK_EQUAL(vec[3], 9);
}

BOOST_AUTO_TEST_CASE(test_create_vector_5D)
{
    auto vec = CE3D2::Transformation::create_permutation_vector(
        2, 9, 1, 4, 18);
    BOOST_CHECK_EQUAL(vec.size(), 5);
    BOOST_CHECK_EQUAL(vec[0], 2);
    BOOST_CHECK_EQUAL(vec[1], 9);
    BOOST_CHECK_EQUAL(vec[2], 1);
    BOOST_CHECK_EQUAL(vec[3], 4);
    BOOST_CHECK_EQUAL(vec[4], 18);
}

BOOST_AUTO_TEST_SUITE_END()
