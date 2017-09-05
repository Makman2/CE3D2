#define BOOST_TEST_MODULE MirrorTest
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "CE3D2/transformation/Mirror.h"
#include "TestUtilities.h"


BOOST_AUTO_TEST_SUITE(MirrorTestSuite)

BOOST_AUTO_TEST_CASE(test_properties)
{
    CE3D2::Transformation::Mirror uut(CE3D2::create_vector(1.0f, 2.0f));
    CE3D2_CHECK_VECTORS_EQUAL(uut.get_reflection_plane_normal(),
                              CE3D2::create_vector(1.0f, 2.0f));

    uut.set_reflection_plane_normal(CE3D2::create_vector(5.0f));
    CE3D2_CHECK_VECTORS_EQUAL(uut.get_reflection_plane_normal(),
                              CE3D2::create_vector(5.0f));
}

BOOST_AUTO_TEST_CASE(test_transform_vector)
{
    CE3D2::Transformation::Mirror uut(CE3D2::create_vector(2.0f, 0.0f, 0.0f));

    CE3D2::Vector vec(CE3D2::create_vector(5.0f, 2.0f, -1.0f));

    uut.transform_vector(vec);
    CE3D2_CHECK_VECTORS_EQUAL(vec, CE3D2::create_vector(-5.0f, 2.0f, -1.0f));

    vec = CE3D2::create_vector(-1.0f, 3.0f, 3.0f);
    uut.transform_vector(vec);
    CE3D2_CHECK_VECTORS_EQUAL(vec, CE3D2::create_vector(1.0f, 3.0f, 3.0f));

    uut.set_reflection_plane_normal(CE3D2::create_vector(1.0f, 1.0f, 2.0f));

    vec = CE3D2::create_vector(2.0f, 2.0f, 4.0f);
    uut.transform_vector(vec);
    CE3D2_CHECK_VECTORS_EQUAL(vec, CE3D2::create_vector(-2.0f, -2.0f, -4.0f));

    vec = CE3D2::create_vector(6.0f, -12.0f, 15.0f);
    uut.transform_vector(vec);
    CE3D2_CHECK_VECTORS_EQUAL(vec, CE3D2::create_vector(-2.0f, -20.0f, -1.0f));
}

BOOST_AUTO_TEST_CASE(test_matrix)
{
    CE3D2::Transformation::Mirror uut(CE3D2::create_vector(6.0f, 0.0f));

    CE3D2::Matrix compare_matrix(2, 2);
    compare_matrix(0, 0) = -1.0f;
    compare_matrix(0, 1) = 0.0f;
    compare_matrix(1, 0) = 0.0f;
    compare_matrix(1, 1) = 1.0f;

    CE3D2_CHECK_MATRICES_EQUAL(uut.get_matrix(), compare_matrix);

    uut.set_reflection_plane_normal(CE3D2::create_vector(-1.0f, 2.0f, -1.0f));

    compare_matrix = CE3D2::Matrix(3, 3);
    compare_matrix(0, 0) = 0.66666663f;
    compare_matrix(0, 1) = 2.0f / 3.0f;
    compare_matrix(0, 2) = -1.0f / 3.0f;
    compare_matrix(1, 0) = 2.0f / 3.0f;
    compare_matrix(1, 1) = -0.33333337f;
    compare_matrix(1, 2) = 2.0f / 3.0f;
    compare_matrix(2, 0) = -1.0f / 3.0f;
    compare_matrix(2, 1) = 2.0f / 3.0f;
    compare_matrix(2, 2) = 0.66666663f;

    CE3D2_CHECK_MATRICES_EQUAL(uut.get_matrix(), compare_matrix);
}

BOOST_AUTO_TEST_SUITE_END()
