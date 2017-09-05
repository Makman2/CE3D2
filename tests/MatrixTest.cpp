#define BOOST_TEST_MODULE MatrixTest
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "CE3D2/Matrix.h"


BOOST_AUTO_TEST_SUITE(MatrixTestSuite)

BOOST_AUTO_TEST_CASE(test_standard_matrix)
{
    CE3D2::Matrix uut(2, 1);
    BOOST_CHECK_EQUAL(uut.size1(), 2);
    BOOST_CHECK_EQUAL(uut.size2(), 1);
    uut(0, 0) = 0.0f;
    uut(1, 0) = 0.0f;
    BOOST_CHECK_EQUAL(uut(0, 0), 0.0f);
    BOOST_CHECK_EQUAL(uut(1, 0), 0.0f);

    uut = CE3D2::Matrix(2, 2);
    BOOST_CHECK_EQUAL(uut.size1(), 2);
    BOOST_CHECK_EQUAL(uut.size2(), 2);
    uut(0, 0) = 0.0f;
    uut(0, 1) = 22.8f;
    uut(1, 0) = 1.0f;
    uut(1, 1) = -1.1f;
    BOOST_CHECK_EQUAL(uut(0, 0), 0.0f);
    BOOST_CHECK_EQUAL(uut(1, 0), 1.0f);
    BOOST_CHECK_EQUAL(uut(0, 1), 22.8f);
    BOOST_CHECK_EQUAL(uut(1, 1), -1.1f);
}

BOOST_AUTO_TEST_CASE(test_identity_matrix)
{
    CE3D2::IdentityMatrix uut(2, 2);
    BOOST_CHECK_EQUAL(uut.size1(), 2);
    BOOST_CHECK_EQUAL(uut.size2(), 2);
    BOOST_CHECK_EQUAL(uut(0, 0), 1.0f);
    BOOST_CHECK_EQUAL(uut(0, 1), 0.0f);
    BOOST_CHECK_EQUAL(uut(1, 0), 0.0f);
    BOOST_CHECK_EQUAL(uut(1, 1), 1.0f);

    uut = CE3D2::IdentityMatrix(2, 3);
    BOOST_CHECK_EQUAL(uut.size1(), 2);
    BOOST_CHECK_EQUAL(uut.size2(), 3);
    BOOST_CHECK_EQUAL(uut(0, 0), 1.0f);
    BOOST_CHECK_EQUAL(uut(0, 1), 0.0f);
    BOOST_CHECK_EQUAL(uut(0, 2), 0.0f);
    BOOST_CHECK_EQUAL(uut(1, 0), 0.0f);
    BOOST_CHECK_EQUAL(uut(1, 1), 1.0f);
    BOOST_CHECK_EQUAL(uut(1, 2), 0.0f);
}

BOOST_AUTO_TEST_CASE(test_zero_matrix)
{
    CE3D2::ZeroMatrix uut(4, 3);
    BOOST_CHECK_EQUAL(uut.size1(), 4);
    BOOST_CHECK_EQUAL(uut.size2(), 3);
    BOOST_CHECK_EQUAL(uut(0, 0), 0.0f);
    BOOST_CHECK_EQUAL(uut(0, 1), 0.0f);
    BOOST_CHECK_EQUAL(uut(0, 2), 0.0f);
    BOOST_CHECK_EQUAL(uut(1, 0), 0.0f);
    BOOST_CHECK_EQUAL(uut(1, 1), 0.0f);
    BOOST_CHECK_EQUAL(uut(1, 2), 0.0f);
    BOOST_CHECK_EQUAL(uut(2, 0), 0.0f);
    BOOST_CHECK_EQUAL(uut(2, 1), 0.0f);
    BOOST_CHECK_EQUAL(uut(2, 2), 0.0f);
    BOOST_CHECK_EQUAL(uut(3, 0), 0.0f);
    BOOST_CHECK_EQUAL(uut(3, 1), 0.0f);
    BOOST_CHECK_EQUAL(uut(3, 2), 0.0f);
}

BOOST_AUTO_TEST_SUITE_END()
