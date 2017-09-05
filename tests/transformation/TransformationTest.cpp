#define BOOST_TEST_MODULE TransformationTest
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "CE3D2/transformation/Transformation.h"
#include "TestUtilities.h"


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
    CE3D2::Vector compare_vector = CE3D2::create_vector(0.0f, 3.0f, 0.0f);
    uut.transform_vector(test_vector);
    CE3D2_CHECK_VECTORS_EQUAL(test_vector, compare_vector);

    std::vector<CE3D2::Vector> test_vector_list = std::vector<CE3D2::Vector>();
    test_vector_list.push_back(CE3D2::create_vector(1.2f, -2.0f, 12.3f));
    test_vector_list.push_back(CE3D2::create_vector(0.0f, 1.0f));
    test_vector_list.push_back(CE3D2::create_vector(-10.2f));

    std::vector<CE3D2::Vector> compare_vector_list =
        std::vector<CE3D2::Vector>();

    // The following value needs to be 3 * 1.2f because using 3.6f directly
    // introduces rounding errors, the compiler translates 3.6f better than
    // calculation.
    compare_vector_list.push_back(CE3D2::create_vector(3 * 1.2f, -6.0f, 36.9f));
    compare_vector_list.push_back(CE3D2::create_vector(0.0f, 3.0f));
    compare_vector_list.push_back(CE3D2::create_vector(-30.6f));

    uut.transform(test_vector_list);
    BOOST_CHECK_EQUAL(test_vector_list.size(), compare_vector_list.size());
    for (unsigned int i = 0; i < compare_vector_list.size(); i++)
    {
        CE3D2_CHECK_VECTORS_EQUAL(test_vector_list[i], compare_vector_list[i]);
    }
}

BOOST_AUTO_TEST_SUITE_END()
