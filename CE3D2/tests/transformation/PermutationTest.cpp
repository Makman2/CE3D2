#define BOOST_TEST_MODULE PermutationTest
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "CE3D2/tests/TestUtilities.h"
#include "CE3D2/transformation/Permutation.h"


BOOST_AUTO_TEST_SUITE(PermutationTestSuite)

BOOST_AUTO_TEST_CASE(test_permutation_vector)
{
    CE3D2::Vector permutation =
        CE3D2::Transformation::create_permutation_vector(0, 1, 2);
    CE3D2::Transformation::Permutation uut(permutation);

    CE3D2_CHECK_VECTORS_EQUAL(uut.get_permutation_vector(), permutation);

    uut = CE3D2::Transformation::Permutation(4);
    CE3D2_CHECK_VECTORS_EQUAL(
        uut.get_permutation_vector(),
        CE3D2::Transformation::create_permutation_vector(3, 2, 1, 0));

    permutation = CE3D2::Transformation::create_permutation_vector(1, 0);
    uut.set_permutation_vector(permutation);

    CE3D2_CHECK_VECTORS_EQUAL(uut.get_permutation_vector(), permutation);
}

BOOST_AUTO_TEST_CASE(test_matrix)
{
    CE3D2::Transformation::Permutation uut(
        CE3D2::Transformation::create_permutation_vector(0, 1, 2));

    CE3D2::Matrix compare_matrix = CE3D2::ZeroMatrix(3, 3);
    compare_matrix(0, 0) = 1.0f;
    compare_matrix(1, 1) = 1.0f;
    compare_matrix(2, 2) = 1.0f;

    CE3D2_CHECK_MATRICES_EQUAL(uut.get_matrix(), compare_matrix);

    uut.set_permutation_vector(
        CE3D2::Transformation::create_permutation_vector(3, 1, 2, 0));

    compare_matrix = CE3D2::ZeroMatrix(4, 4);
    compare_matrix(0, 3) = 1.0f;
    compare_matrix(1, 1) = 1.0f;
    compare_matrix(2, 2) = 1.0f;
    compare_matrix(3, 0) = 1.0f;

    CE3D2_CHECK_MATRICES_EQUAL(uut.get_matrix(), compare_matrix);

    auto test_vector = CE3D2::create_vector(1.0f, 2.0f, 3.0f, 4.0f);
    uut.transform_vector(test_vector);
    CE3D2_CHECK_VECTORS_EQUAL(test_vector,
                              CE3D2::create_vector(4.0f, 2.0f, 3.0f, 1.0f));
}

BOOST_AUTO_TEST_SUITE_END()
