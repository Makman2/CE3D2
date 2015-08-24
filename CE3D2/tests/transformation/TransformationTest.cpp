#define BOOST_TEST_MODULE TransformationTest
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "CE3D2/tests/TestUtilities.h"
#include "CE3D2/transformation/Transformation.h"


class TestTransformation : public CE3D2::Transformation::Transformation
{
public:
    TestTransformation()
    {}

    virtual void
    transform_vector(CE3D2::Vector& vector) const override
    {
        vector *= 3;
    }
};


BOOST_AUTO_TEST_SUITE(TransformationTestSuite)

BOOST_AUTO_TEST_CASE(test_transform)
{
    TestTransformation uut;

    CE3D2::Vector test_vector = CE3D2::UnitVector(3, 1);
    CE3D2::Vector compare_vector = CE3D2::Vector(3);
    compare_vector[0] = 0.0f;
    compare_vector[1] = 3.0f;
    compare_vector[2] = 0.0f;
    uut.transform_vector(test_vector);
    BOOST_CHECK_VECTORS_EQUAL(test_vector, compare_vector);

    std::vector<CE3D2::Vector> test_vector_list = std::vector<CE3D2::Vector>();
    test_vector_list.emplace_back(3);
    test_vector_list[0][0] = 1.2f;
    test_vector_list[0][1] = -2.0f;
    test_vector_list[0][2] = 12.3f;
    test_vector_list.emplace_back(2);
    test_vector_list[1][0] = 0.0f;
    test_vector_list[1][1] = 1.0f;
    test_vector_list.emplace_back(1);
    test_vector_list[2][0] = -10.2f;
    std::vector<CE3D2::Vector> compare_vector_list =
        std::vector<CE3D2::Vector>();
    compare_vector_list.emplace_back(3);
    // The following value needs to be 3 * 1.2f because using 3.6f directly
    // introduces rounding errors, the compiler translates 3.6f better than
    // calculation.
    compare_vector_list[0][0] = 3 * 1.2f;
    compare_vector_list[0][1] = -6.0f;
    compare_vector_list[0][2] = 36.9f;
    compare_vector_list.emplace_back(2);
    compare_vector_list[1][0] = 0.0f;
    compare_vector_list[1][1] = 3.0f;
    compare_vector_list.emplace_back(1);
    compare_vector_list[2][0] = -30.6f;
    uut.transform(test_vector_list);
    BOOST_CHECK_EQUAL(test_vector_list.size(), compare_vector_list.size());
    for (unsigned int i = 0; i < compare_vector_list.size(); i++)
    {
        BOOST_CHECK_VECTORS_EQUAL(test_vector_list[i], compare_vector_list[i]);
    }
}

BOOST_AUTO_TEST_SUITE_END()
