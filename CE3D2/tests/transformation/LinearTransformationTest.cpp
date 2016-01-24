#define BOOST_TEST_MODULE LinearTransformationTest
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "CE3D2/tests/TestUtilities.h"
#include "CE3D2/transformation/LinearTransformation.h"


class TestLinearTransformation
: public CE3D2::Transformation::LinearTransformation
{
public:
    TestLinearTransformation()
    : m_Scale(1.0f)
    {}

    virtual CE3D2::Matrix
    on_update() const override
    {
        CE3D2::Matrix matrix = CE3D2::Matrix(2, 2);
        matrix(0, 0) = m_Scale;
        matrix(0, 1) = m_Scale;
        matrix(1, 0) = m_Scale;
        matrix(1, 1) = m_Scale;
        return matrix;
    }

    void
    set_scale(float scale)
    {
        m_Scale = scale;
        update();
    }

private:
    float m_Scale;
};


BOOST_AUTO_TEST_SUITE(LinearTransformationTestSuite)

BOOST_AUTO_TEST_CASE(test_matrix)
{
    auto uut = TestLinearTransformation();

    CE3D2::Vector testvector = CE3D2::create_vector(2.0f, 2.0f);
    CE3D2::Vector compare_vector = CE3D2::create_vector(4.0f, 4.0f);
    uut.transform_vector(testvector);

    CE3D2_CHECK_VECTORS_EQUAL(testvector, compare_vector);

    uut.set_scale(0.0f);
    testvector = CE3D2::create_vector(2.0f, 2.0f);
    compare_vector = CE3D2::create_vector(0.0f, 0.0f);
    uut.transform_vector(testvector);

    CE3D2_CHECK_VECTORS_EQUAL(testvector, compare_vector);

    uut.set_scale(2.5f);
    testvector = CE3D2::create_vector(4.0f, 2.0f);
    compare_vector = CE3D2::create_vector(15.0f, 15.0f);
    uut.transform_vector(testvector);

    CE3D2_CHECK_VECTORS_EQUAL(testvector, compare_vector);

    testvector = CE3D2::create_vector(3.0f, 1.0f);
    compare_vector = CE3D2::create_vector(10.0f, 10.0f);
    uut.transform_vector(testvector);

    CE3D2_CHECK_VECTORS_EQUAL(testvector, compare_vector);
}

BOOST_AUTO_TEST_SUITE_END()
