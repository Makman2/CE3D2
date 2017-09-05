#define BOOST_TEST_MODULE MatrixTransformationTest
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "CE3D2/transformation/MatrixTransformation.h"
#include "TestUtilities.h"


BOOST_AUTO_TEST_SUITE(MatrixTransformationTestSuite)

BOOST_AUTO_TEST_CASE(test_constructor)
{
    CE3D2::Matrix matrix(2, 2);
    matrix(0, 0) = 0.0f;
    matrix(0, 1) = 5.0f;
    matrix(1, 0) = 1.0f;
    matrix(1, 1) = 2.0f;

    CE3D2::Transformation::MatrixTransformation uut(matrix);
    CE3D2_CHECK_MATRICES_EQUAL(uut.get_matrix(), matrix);
}

BOOST_AUTO_TEST_CASE(test_matrix_setter)
{
    CE3D2::Matrix matrix(2, 3);
    CE3D2::Transformation::MatrixTransformation uut(matrix);

    matrix(0, 0) = 1.5f;
    matrix(0, 1) = 4.0f;
    matrix(0, 2) = 2.2f;
    matrix(1, 0) = 1.0f;
    matrix(1, 1) = 7.7f;
    matrix(1, 2) = -54.4;

    uut.set_matrix(matrix);
    CE3D2_CHECK_MATRICES_EQUAL(uut.get_matrix(), matrix);
}

BOOST_AUTO_TEST_SUITE_END()
