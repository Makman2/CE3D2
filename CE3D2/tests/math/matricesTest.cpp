#define BOOST_TEST_MODULE matricesTest
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "CE3D2/math/matrices.h"
#include "CE3D2/Matrix.h"
#include "CE3D2/tests/TestUtilities.h"


BOOST_AUTO_TEST_SUITE(matricesTestSuite)

BOOST_AUTO_TEST_CASE(test_invert)
{
    CE3D2::Matrix output;

    // Test identity matrix.
    CE3D2::Matrix testmatrix = CE3D2::IdentityMatrix(2);
    BOOST_CHECK(CE3D2::Math::Matrices::invert(testmatrix, output));
    BOOST_CHECK_MATRICES_EQUAL(output, testmatrix);

    // Test orthonormal matrix.
    testmatrix = CE3D2::Matrix(4, 4);
    testmatrix(0, 0) = 0.5f;
    testmatrix(0, 1) = 0.5f;
    testmatrix(0, 2) = 0.5f;
    testmatrix(0, 3) = 0.5f;
    testmatrix(1, 0) = -0.5f;
    testmatrix(1, 1) = -0.5f;
    testmatrix(1, 2) = 0.5f;
    testmatrix(1, 3) = 0.5f;
    testmatrix(2, 0) = -0.5f;
    testmatrix(2, 1) = 0.5f;
    testmatrix(2, 2) = -0.5f;
    testmatrix(2, 3) = 0.5f;
    testmatrix(3, 0) = 0.5f;
    testmatrix(3, 1) = -0.5f;
    testmatrix(3, 2) = -0.5f;
    testmatrix(3, 3) = 0.5f;

    BOOST_CHECK(CE3D2::Math::Matrices::invert(testmatrix, output));
    BOOST_CHECK_MATRICES_EQUAL(output,
                               boost::numeric::ublas::trans(testmatrix));

    // Test arbitrary matrix.
    testmatrix = CE3D2::Matrix(3, 3);
    testmatrix(0, 0) = 1.0f;
    testmatrix(0, 1) = 1.0f;
    testmatrix(0, 2) = 0.0f;
    testmatrix(1, 0) = 0.0f;
    testmatrix(1, 1) = 0.0f;
    testmatrix(1, 2) = 1.0f;
    testmatrix(2, 0) = 1.0f;
    testmatrix(2, 1) = -1.0f;
    testmatrix(2, 2) = 2.0f;

    CE3D2::Matrix compare_matrix = CE3D2::Matrix(3, 3);
    compare_matrix(0, 0) = 0.5f;
    compare_matrix(0, 1) = -1.0f;
    compare_matrix(0, 2) = 0.5f;
    compare_matrix(1, 0) = 0.5f;
    compare_matrix(1, 1) = 1.0f;
    compare_matrix(1, 2) = -0.5f;
    compare_matrix(2, 0) = 0.0f;
    compare_matrix(2, 1) = 1.0f;
    compare_matrix(2, 2) = 0.0f;

    BOOST_CHECK(CE3D2::Math::Matrices::invert(testmatrix, output));
    BOOST_CHECK_MATRICES_EQUAL(output, compare_matrix);

    // Test non-invertable matrices.
    testmatrix = CE3D2::ZeroMatrix(3, 3);
    BOOST_CHECK(!CE3D2::Math::Matrices::invert(testmatrix, output));

    testmatrix = CE3D2::Matrix(2, 2);
    testmatrix(0, 0) = 3.0f;
    testmatrix(0, 1) = 3.0f;
    testmatrix(1, 0) = 3.0f;
    testmatrix(1, 1) = 3.0f;
    BOOST_CHECK(!CE3D2::Math::Matrices::invert(testmatrix, output));

    testmatrix = CE3D2::Matrix(3, 3);
    testmatrix(0, 0) = 1.0f;
    testmatrix(0, 1) = 1.0f;
    testmatrix(0, 2) = 0.0f;
    testmatrix(1, 0) = 2.0f;
    testmatrix(1, 1) = 2.0f;
    testmatrix(1, 2) = 0.0f;
    testmatrix(2, 0) = 1.0f;
    testmatrix(2, 1) = -1.0f;
    testmatrix(2, 2) = 2.0f;
    BOOST_CHECK(!CE3D2::Math::Matrices::invert(testmatrix, output));
}

BOOST_AUTO_TEST_SUITE_END()
