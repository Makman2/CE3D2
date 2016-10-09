#define BOOST_TEST_MODULE OrthogonalProjectionTest
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <vector>

#include "CE3D2/tests/TestUtilities.h"
#include "CE3D2/transformation/OrthogonalProjection.h"
#include "CE3D2/Vector.h"


BOOST_AUTO_TEST_SUITE(OrthogonalProjectionTestSuite)

BOOST_AUTO_TEST_CASE(test_projection_vectors)
{
    auto uut = CE3D2::Transformation::OrthogonalProjection();
    std::vector<CE3D2::Vector> projection_vectors;

    BOOST_CHECK_EQUAL(uut.get_projection_vectors().size(), 0);

    projection_vectors.push_back(CE3D2::create_vector(1.0f, 2.0f, 3.0f));
    uut.set_projection_vectors(projection_vectors);
    BOOST_CHECK_EQUAL(uut.get_projection_vectors().size(), 1);
    CE3D2_CHECK_VECTORS_EQUAL(uut.get_projection_vectors()[0],
                              CE3D2::create_vector(1.0f, 2.0f, 3.0f));

    projection_vectors.push_back(CE3D2::ZeroVector(3));
    projection_vectors.push_back(CE3D2::create_vector(-1.0f, 0.0f, 0.0f));
    uut.set_projection_vectors(projection_vectors);
    BOOST_CHECK_EQUAL(uut.get_projection_vectors().size(), 3);
    CE3D2_CHECK_VECTORS_EQUAL(uut.get_projection_vectors()[0],
                              CE3D2::create_vector(1.0f, 2.0f, 3.0f));
    CE3D2_CHECK_VECTORS_EQUAL(uut.get_projection_vectors()[1],
                              CE3D2::ZeroVector(3));
    CE3D2_CHECK_VECTORS_EQUAL(uut.get_projection_vectors()[2],
                              CE3D2::create_vector(-1.0f, 0.0f, 0.0f));

    projection_vectors.push_back(CE3D2::UnitVector(2, 1));
    uut.set_projection_vectors(projection_vectors);
    BOOST_CHECK_EQUAL(uut.get_projection_vectors().size(), 4);
    CE3D2_CHECK_VECTORS_EQUAL(uut.get_projection_vectors()[3],
                              CE3D2::UnitVector(2, 1));

    projection_vectors.clear();
    projection_vectors.push_back(CE3D2::create_vector(-5.0f, 2.3f));
    projection_vectors.push_back(CE3D2::create_vector(7.0f, 0.2f));

    // Test setting vectors from constructor.
    uut = CE3D2::Transformation::OrthogonalProjection(projection_vectors);

    BOOST_CHECK_EQUAL(uut.get_projection_vectors().size(), 2);
    CE3D2_CHECK_VECTORS_EQUAL(uut.get_projection_vectors()[0],
                              CE3D2::create_vector(-5.0f, 2.3f));
    CE3D2_CHECK_VECTORS_EQUAL(uut.get_projection_vectors()[1],
                              CE3D2::create_vector(7.0f, 0.2f));
}

BOOST_AUTO_TEST_CASE(test_matrix)
{
    auto uut = CE3D2::Transformation::OrthogonalProjection();
    std::vector<CE3D2::Vector> projection_vectors;

    // Identity projection into the same space.
    projection_vectors.push_back(CE3D2::UnitVector(3, 0));
    projection_vectors.push_back(CE3D2::UnitVector(3, 1));
    projection_vectors.push_back(CE3D2::UnitVector(3, 2));

    uut.set_projection_vectors(projection_vectors);

    CE3D2_CHECK_MATRICES_EQUAL(uut.get_matrix(), CE3D2::IdentityMatrix(3));

    // Same dimension, but other base vectors to project on.
    projection_vectors.clear();
    projection_vectors.push_back(CE3D2::create_vector(1.0f, 1.0f, 0.0f));
    projection_vectors.push_back(CE3D2::create_vector(1.0f, -1.0f, 0.0f));
    projection_vectors.push_back(CE3D2::UnitVector(3, 2));

    uut.set_projection_vectors(projection_vectors);

    CE3D2::Matrix compare_matrix(3, 3);
    compare_matrix(0, 0) = 0.5f;
    compare_matrix(0, 1) = 0.5f;
    compare_matrix(0, 2) = 0.0f;
    compare_matrix(1, 0) = 0.5f;
    compare_matrix(1, 1) = -0.5f;
    compare_matrix(1, 2) = 0.0f;
    compare_matrix(2, 0) = 0.0f;
    compare_matrix(2, 1) = 0.0f;
    compare_matrix(2, 2) = 1.0f;

    CE3D2_CHECK_MATRICES_EQUAL(uut.get_matrix(), compare_matrix);

    // Complicated bases in 4D space.
    projection_vectors.clear();
    projection_vectors.push_back(CE3D2::create_vector(1.0f, 0.0f, 0.0f, 1.0f));
    projection_vectors.push_back(CE3D2::create_vector(1.0f, 1.0f, 0.0f, 0.0f));
    projection_vectors.push_back(CE3D2::create_vector(0.0f, 1.0f, 1.0f, 1.0f));
    projection_vectors.push_back(CE3D2::create_vector(0.0f, 0.0f, 1.0f, 0.0f));

    uut.set_projection_vectors(projection_vectors);

    compare_matrix = CE3D2::Matrix(4, 4);
    compare_matrix(0, 0) = 0.5f;
    compare_matrix(0, 1) = -0.5f;
    compare_matrix(0, 2) = 0.0f;
    compare_matrix(0, 3) = 0.5f;
    compare_matrix(1, 0) = 0.5f;
    compare_matrix(1, 1) = 0.5f;
    compare_matrix(1, 2) = 0.000000029802322f;
    compare_matrix(1, 3) = -0.5f;
    compare_matrix(2, 0) = -0.5f;
    compare_matrix(2, 1) = 0.49999997f;
    compare_matrix(2, 2) = -0.000000059604645f;
    compare_matrix(2, 3) = 0.5f;
    compare_matrix(3, 0) = 0.5f;
    compare_matrix(3, 1) = -0.5f;
    compare_matrix(3, 2) = 1.0f;
    compare_matrix(3, 3) = -0.50000006f;

    CE3D2_CHECK_MATRICES_EQUAL(uut.get_matrix(), compare_matrix);

    // Project from 3D onto 2D.
    projection_vectors.clear();
    projection_vectors.push_back(CE3D2::create_vector(1.0f, 0.0f, 0.0f));
    projection_vectors.push_back(CE3D2::create_vector(0.0f, 2.0f, 2.0f));

    uut.set_projection_vectors(projection_vectors);

    compare_matrix = CE3D2::Matrix(2, 3);
    compare_matrix(0, 0) = 1.0f;
    compare_matrix(0, 1) = 0.0f;
    compare_matrix(0, 2) = 0.0f;
    compare_matrix(1, 0) = 0.0f;
    compare_matrix(1, 1) = 0.25f;
    compare_matrix(1, 2) = 0.25f;

    CE3D2_CHECK_MATRICES_EQUAL(uut.get_matrix(), compare_matrix);

    // Project from 3D onto 1D.
    projection_vectors.clear();
    projection_vectors.push_back(CE3D2::create_vector(1.0f, 2.0f, 0.0f));

    uut.set_projection_vectors(projection_vectors);

    compare_matrix = CE3D2::Matrix(1, 3);
    compare_matrix(0, 0) = 0.2f;
    compare_matrix(0, 1) = 0.4f;
    compare_matrix(0, 2) = 0.0f;

    CE3D2_CHECK_MATRICES_EQUAL(uut.get_matrix(), compare_matrix);

    // Project from 2D onto 1D.
    projection_vectors.clear();
    projection_vectors.push_back(CE3D2::create_vector(1.0f, -3.0f));

    uut.set_projection_vectors(projection_vectors);

    compare_matrix = CE3D2::Matrix(1, 2);
    compare_matrix(0, 0) = 0.1f;
    compare_matrix(0, 1) = -0.3f;

    CE3D2_CHECK_MATRICES_EQUAL(uut.get_matrix(), compare_matrix);
}

BOOST_AUTO_TEST_CASE(test_matrix_exceptions)
{
    CE3D2::Transformation::OrthogonalProjection uut;
    std::vector<CE3D2::Vector> projection_vectors;

    // No projection vectors to project on.
    projection_vectors.clear();

    uut.set_projection_vectors(projection_vectors);

    BOOST_CHECK_THROW(uut.get_matrix(), std::invalid_argument);

    // Size of vectors varies.
    projection_vectors.push_back(CE3D2::UnitVector(3, 0));
    projection_vectors.push_back(CE3D2::UnitVector(2, 1));
    projection_vectors.push_back(CE3D2::UnitVector(3, 2));

    uut.set_projection_vectors(projection_vectors);

    BOOST_CHECK_THROW(uut.get_matrix(), std::invalid_argument);

    // More vectors than dimensions.
    projection_vectors.clear();
    projection_vectors.push_back(CE3D2::UnitVector(3, 0));
    projection_vectors.push_back(CE3D2::UnitVector(3, 1));
    projection_vectors.push_back(CE3D2::UnitVector(3, 2));
    projection_vectors.push_back(CE3D2::create_vector(1.0f, 1.0f, 1.0f));

    uut.set_projection_vectors(projection_vectors);

    BOOST_CHECK_THROW(uut.get_matrix(), std::invalid_argument);

    // Linear dependent projection vectors.
    projection_vectors.clear();
    projection_vectors.push_back(CE3D2::UnitVector(3, 0));
    projection_vectors.push_back(CE3D2::UnitVector(3, 0) * 4);

    uut.set_projection_vectors(projection_vectors);

    BOOST_CHECK_THROW(uut.get_matrix(), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()
