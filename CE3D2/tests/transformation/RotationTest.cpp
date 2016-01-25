#define BOOST_TEST_MODULE RotationTest
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "CE3D2/tests/TestUtilities.h"
#include "CE3D2/transformation/Rotation.h"


BOOST_AUTO_TEST_SUITE(RotationTestSuite)

BOOST_AUTO_TEST_CASE(test_constructors)
{
    CE3D2::Transformation::Rotation uut;

    CE3D2_CHECK_VECTORS_EQUAL(uut.get_plane_vector1(), CE3D2::Vector());
    CE3D2_CHECK_VECTORS_EQUAL(uut.get_plane_vector2(), CE3D2::Vector());
    BOOST_CHECK_EQUAL(uut.get_angle(), 0.0f);

    auto v1 = CE3D2::create_vector(1.0f, 2.0f, 3.0f);
    auto v2 = CE3D2::create_vector(2.0f, 4.0f, 0.0f);
    uut = CE3D2::Transformation::Rotation(v1, v2);

    CE3D2_CHECK_VECTORS_EQUAL(uut.get_plane_vector1(), v1);
    CE3D2_CHECK_VECTORS_EQUAL(uut.get_plane_vector2(), v2);
    BOOST_CHECK_EQUAL(uut.get_angle(), 0.0f);

    uut = CE3D2::Transformation::Rotation(v1, v2, 90.0f);
    CE3D2_CHECK_VECTORS_EQUAL(uut.get_plane_vector1(), v1);
    CE3D2_CHECK_VECTORS_EQUAL(uut.get_plane_vector2(), v2);
    BOOST_CHECK_EQUAL(uut.get_angle(), 90.0f);
}

BOOST_AUTO_TEST_CASE(test_plane_vectors)
{
    auto v1 = CE3D2::create_vector(1.0f, 0.0f, 0.0f);
    auto v2 = CE3D2::create_vector(0.0f, 1.0f, 0.0f);
    CE3D2::Transformation::Rotation uut(v1, v2);

    CE3D2_CHECK_VECTORS_EQUAL(uut.get_plane_vector1(), v1);
    CE3D2_CHECK_VECTORS_EQUAL(uut.get_plane_vector2(), v2);

    v1 = CE3D2::create_vector(5.5f, 8.8f);
    v2 = CE3D2::create_vector(0.0f, 0.0f);
    uut.set_plane_vector1(v1);
    uut.set_plane_vector2(v2);

    CE3D2_CHECK_VECTORS_EQUAL(uut.get_plane_vector1(), v1);
    CE3D2_CHECK_VECTORS_EQUAL(uut.get_plane_vector2(), v2);
}

BOOST_AUTO_TEST_CASE(test_angle)
{
    CE3D2::Transformation::Rotation uut(CE3D2::Vector(),
                                        CE3D2::Vector(),
                                        180.0f);

    BOOST_CHECK_EQUAL(uut.get_angle(), 180.0f);

    uut.set_angle(77.7f);

    BOOST_CHECK_EQUAL(uut.get_angle(), 77.7f);
}

BOOST_AUTO_TEST_CASE(test_angle_in_degrees)
{
    CE3D2::Transformation::Rotation uut(CE3D2::Vector(),
                                        CE3D2::Vector(),
                                        CE3D2::PI);

    BOOST_CHECK_EQUAL(uut.get_angle_in_degrees(), 180.0f);

    uut.set_angle(CE3D2::PI / 2);

    BOOST_CHECK_EQUAL(uut.get_angle_in_degrees(), 90.0f);

    uut.set_angle_in_degrees(270.0f);

    BOOST_CHECK_EQUAL(uut.get_angle_in_degrees(), 270.0f);
    BOOST_CHECK_EQUAL(uut.get_angle(), CE3D2::PI * 3 / 2);

    uut.set_angle_in_degrees(45.0f);

    BOOST_CHECK_EQUAL(uut.get_angle_in_degrees(), 45.0f);
    BOOST_CHECK_EQUAL(uut.get_angle(), CE3D2::PI / 4);
}

BOOST_AUTO_TEST_CASE(test_matrix_2D)
{
    CE3D2::Transformation::Rotation uut(CE3D2::create_vector(1.0f, 0.0f),
                                        CE3D2::create_vector(0.0f, 1.0f),
                                        0.0f);
    CE3D2_CHECK_MATRICES_EQUAL(uut.get_matrix(), CE3D2::IdentityMatrix(2));

    uut.set_angle(CE3D2::PI / 4);
    CE3D2::Matrix expected(2, 2);
    expected(0, 0) = 0.70710677f;
    expected(0, 1) = 0.70710677f;
    expected(1, 0) = -0.70710677f;
    expected(1, 1) = 0.70710677f;
    CE3D2_CHECK_MATRICES_EQUAL(uut.get_matrix(), expected);

    uut.set_angle(CE3D2::PI / 2);
    expected(0, 0) = -0.000000043711388f;
    expected(0, 1) = 1.0f;
    expected(1, 0) = -1.0f;
    expected(1, 1) = -0.000000043711388f;
    CE3D2_CHECK_MATRICES_EQUAL(uut.get_matrix(), expected);

    uut.set_angle(CE3D2::PI);
    expected(0, 0) = -1.0f;
    expected(0, 1) = -0.000000087422777f;
    expected(1, 0) = 0.000000087422777f;
    expected(1, 1) = -1.0f;
    CE3D2_CHECK_MATRICES_EQUAL(uut.get_matrix(), expected);

    uut.set_angle(CE3D2::PI * 3 / 2);
    expected(0, 0) = 0.000000011924881f;
    expected(0, 1) = -1.0f;
    expected(1, 0) = 1.0f;
    expected(1, 1) = 0.000000011924881f;
    CE3D2_CHECK_MATRICES_EQUAL(uut.get_matrix(), expected);

    uut.set_angle(CE3D2::PI * 2);
    expected(0, 0) = 1.0f;
    expected(0, 1) = 0.00000017484555f;
    expected(1, 0) = -0.00000017484555f;
    expected(1, 1) = 1.0f;
    CE3D2_CHECK_MATRICES_EQUAL(uut.get_matrix(), expected);
}

BOOST_AUTO_TEST_CASE(test_matrix_3D)
{
    CE3D2::Transformation::Rotation uut(CE3D2::create_vector(0.0f, 0.0f, 1.0f),
                                        CE3D2::create_vector(0.0f, 1.0f, 0.0f),
                                        0.0f);
    CE3D2_CHECK_MATRICES_EQUAL(uut.get_matrix(), CE3D2::IdentityMatrix(3));

    uut.set_angle(CE3D2::PI / 2);
    CE3D2::Matrix expected(3, 3);
    expected(0, 0) = 1.0f;
    expected(0, 1) = 0.0f;
    expected(0, 2) = 0.0f;
    expected(1, 0) = 0.0f;
    expected(1, 1) = -0.000000043711388f;
    expected(1, 2) = -1.0f;
    expected(2, 0) = 0.0f;
    expected(2, 1) = 1.0f;
    expected(2, 2) = -0.000000043711388f;
    CE3D2_CHECK_MATRICES_EQUAL(uut.get_matrix(), expected);

    uut.set_plane_vector1(CE3D2::create_vector(4.0f, 0.0f, 0.0f));
    expected(0, 0) = -0.000000043711388f;
    expected(0, 1) = 1.0f;
    expected(0, 2) = 0.0f;
    expected(1, 0) = -1.0f;
    expected(1, 1) = -0.000000043711388f;
    expected(1, 2) = 0.0f;
    expected(2, 0) = 0.0f;
    expected(2, 1) = 0.0f;
    expected(2, 2) = 1.0f;
    CE3D2_CHECK_MATRICES_EQUAL(uut.get_matrix(), expected);

    uut.set_plane_vector2(CE3D2::create_vector(1.0f, 1.0f, 1.0f));
    expected(0, 0) = -0.000000043711388f;
    expected(0, 1) = 0.70710677f;
    expected(0, 2) = 0.70710677f;
    expected(1, 0) = -0.70710677f;
    expected(1, 1) = 0.5f;
    expected(1, 2) = -0.5f;
    expected(2, 0) = -0.70710677f;
    expected(2, 1) = -0.5f;
    expected(2, 2) = 0.5f;
    CE3D2_CHECK_MATRICES_EQUAL(uut.get_matrix(), expected);
}

BOOST_AUTO_TEST_CASE(test_matrix_exceptions)
{
    // Plane vectors do not have the same size.
    CE3D2::Transformation::Rotation uut(
        CE3D2::create_vector(1.0f, 0.0f),
        CE3D2::create_vector(0.0f, 1.0f, 44.0f));
    BOOST_CHECK_THROW(uut.get_matrix(), std::invalid_argument);

    // Linearly dependent plane vectors.
    uut = CE3D2::Transformation::Rotation(CE3D2::create_vector(33.0f, 0.0f),
                                          CE3D2::create_vector(55.0f, 0.0f));
    BOOST_CHECK_THROW(uut.get_matrix(), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()
