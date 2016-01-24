#define BOOST_TEST_MODULE TransformationChainTest
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <algorithm>

#include "CE3D2/tests/TestUtilities.h"
#include "CE3D2/transformation/TransformationChain.h"


class MultiplyTransformation : public CE3D2::Transformation::Transformation
{
public:
    MultiplyTransformation()
    : MultiplyTransformation(1.0f)
    {}

    MultiplyTransformation(float multiplication_factor)
    : factor(multiplication_factor)
    {}

    void
    transform_vector(CE3D2::Vector& vector) const override
    {
        vector *= factor;
    }

    float factor;
};


class SquareTransformation : public CE3D2::Transformation::Transformation
{
    void
    transform_vector(CE3D2::Vector& vector) const override
    {
        for (CE3D2::Vector::size_type i = 0; i < vector.size(); i++)
        {
            vector[i] *= vector[i];
        }
    }
};


BOOST_AUTO_TEST_SUITE(TransformationChainTestSuite)

BOOST_AUTO_TEST_CASE(test_constructor)
{
    CE3D2::Transformation::TransformationChain uut;

    BOOST_CHECK(uut.transformations().empty());
}

BOOST_AUTO_TEST_CASE(test_empty_transform)
{
    CE3D2::Transformation::TransformationChain uut;

    auto vector = CE3D2::create_vector(4.0f, 22.0f, 71.98f);
    auto vector2 = CE3D2::Vector(vector);

    uut.transform_vector(vector2);
    CE3D2_CHECK_VECTORS_EQUAL(vector, vector2);
}

BOOST_AUTO_TEST_CASE(test_single_transform)
{
    CE3D2::Transformation::TransformationChain uut;
    auto vector = CE3D2::create_vector(1.0f, 2.0f, 3.0f);
    auto mul_transform = std::make_shared<MultiplyTransformation>();
    uut.transformations().push_back(mul_transform);

    uut.transform_vector(vector);
    CE3D2_CHECK_VECTORS_EQUAL(vector, CE3D2::create_vector(1.0f, 2.0f, 3.0f));

    mul_transform->factor = 2.0f;

    uut.transform_vector(vector);
    CE3D2_CHECK_VECTORS_EQUAL(vector, CE3D2::create_vector(2.0f, 4.0f, 6.0f));
}

BOOST_AUTO_TEST_CASE(test_double_transform)
{
    CE3D2::Transformation::TransformationChain uut;
    auto vector = CE3D2::create_vector(1.0f, 2.0f, 3.0f, 4.5f);

    auto& transformations = uut.transformations();
    transformations.push_back(
        std::shared_ptr<MultiplyTransformation>(
            new MultiplyTransformation(2.0f)));
    transformations.push_back(
        std::shared_ptr<SquareTransformation>(new SquareTransformation()));

    uut.transform_vector(vector);
    CE3D2_CHECK_VECTORS_EQUAL(vector,
                              CE3D2::create_vector(4.0f, 16.0f, 36.0f, 81.0f));

    // Swap order.
    std::reverse(transformations.begin(), transformations.end());

    vector = CE3D2::create_vector(1.0f, 2.0f, 3.0f, 4.5f);

    uut.transform_vector(vector);
    CE3D2_CHECK_VECTORS_EQUAL(vector,
                              CE3D2::create_vector(2.0f, 8.0f, 18.0f, 40.5f));
}

BOOST_AUTO_TEST_SUITE_END()
