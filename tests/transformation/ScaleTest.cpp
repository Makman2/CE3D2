#define BOOST_TEST_MODULE ScaleTest
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "CE3D2/transformation/Scale.h"
#include "TestUtilities.h"


BOOST_AUTO_TEST_SUITE(ScaleTestSuite)

BOOST_AUTO_TEST_CASE(test_scaling_vector)
{
    CE3D2::Vector scale = CE3D2::create_vector(2.0f, 3.0f);
    auto uut = CE3D2::Transformation::Scale(scale);

    CE3D2_CHECK_VECTORS_EQUAL(uut.get_scale(), scale);

    scale = CE3D2::create_vector(1.0f, 2.0f, 3.0f);
    uut.set_scale(scale);

    CE3D2_CHECK_VECTORS_EQUAL(uut.get_scale(), scale);

    scale[0] = -1.0f;
    uut.set_scale(0, -1.0f);

    CE3D2_CHECK_VECTORS_EQUAL(uut.get_scale(), scale);

    scale[2] = 444.4f;
    uut.set_scale(2, 444.4f);

    CE3D2_CHECK_VECTORS_EQUAL(uut.get_scale(), scale);
}

BOOST_AUTO_TEST_CASE(test_matrix)
{
    auto uut = CE3D2::Transformation::Scale(CE3D2::create_vector(2.0f, 3.0f));

    CE3D2::Matrix compare_matrix = CE3D2::Matrix(2, 2);
    compare_matrix(0, 0) = 2.0f;
    compare_matrix(0, 1) = 0.0f;
    compare_matrix(1, 0) = 0.0f;
    compare_matrix(1, 1) = 3.0f;

    CE3D2_CHECK_MATRICES_EQUAL(uut.get_matrix(), compare_matrix);

    CE3D2::Vector testvector = CE3D2::create_vector(2.2f, 7.0f);
    uut.transform_vector(testvector);
    CE3D2_CHECK_VECTORS_EQUAL(testvector, CE3D2::create_vector(4.4f, 21.0f));

    testvector = CE3D2::create_vector(1.0f, 1.5f);
    uut.transform_vector(testvector);
    CE3D2_CHECK_VECTORS_EQUAL(testvector, CE3D2::create_vector(2.0f, 4.5f));


    uut.set_scale(1, 4.0f);

    compare_matrix(1, 1) = 4.0f;

    CE3D2_CHECK_MATRICES_EQUAL(uut.get_matrix(), compare_matrix);

    testvector = CE3D2::create_vector(1.0f, 1.0f);
    uut.transform_vector(testvector);
    CE3D2_CHECK_VECTORS_EQUAL(testvector, CE3D2::create_vector(2.0f, 4.0f));

    testvector = CE3D2::create_vector(8.0f, -2.0f);
    uut.transform_vector(testvector);
    CE3D2_CHECK_VECTORS_EQUAL(testvector, CE3D2::create_vector(16.0f, -8.0f));


    uut.set_scale(CE3D2::create_vector(4.7f, 1.2f, 0.5f));

    compare_matrix = CE3D2::Matrix(3, 3);
    compare_matrix(0, 0) = 4.7f;
    compare_matrix(0, 1) = 0.0f;
    compare_matrix(0, 2) = 0.0f;
    compare_matrix(1, 0) = 0.0f;
    compare_matrix(1, 1) = 1.2f;
    compare_matrix(1, 2) = 0.0f;
    compare_matrix(2, 0) = 0.0f;
    compare_matrix(2, 1) = 0.0f;
    compare_matrix(2, 2) = 0.5f;

    testvector = CE3D2::create_vector(2.0f, 2.0f, 2.0f);
    uut.transform_vector(testvector);
    CE3D2_CHECK_VECTORS_EQUAL(testvector,
                              CE3D2::create_vector(9.4f, 2.4f, 1.0f));

    testvector = CE3D2::create_vector(1.0f, 0.5f, 3.0f);
    uut.transform_vector(testvector);
    CE3D2_CHECK_VECTORS_EQUAL(testvector,
                              CE3D2::create_vector(4.7f, 0.6f, 1.5f));
}

BOOST_AUTO_TEST_SUITE_END()
