#define BOOST_TEST_MODULE ITransformableTest
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <string>

#include "CE3D2/transformation/ITransformable.h"


class TestITransformable : public CE3D2::Transformation::ITransformable
{
public:
    TestITransformable()
    : call_string()
    {}

    virtual void
    transform(CE3D2::Transformation::Transformation const& transform) override
    {
        call_string += "c";
    }

    std::string call_string;
};


class TestTransformation : public CE3D2::Transformation::Transformation
{
public:
    TestTransformation()
    {}

    virtual void
    transform_vector(CE3D2::Vector& vector) const override
    {}
};


BOOST_AUTO_TEST_SUITE(ITransformableTestSuite)

BOOST_AUTO_TEST_CASE(test_interface)
{
    TestITransformable uut;
    BOOST_CHECK_EQUAL(uut.call_string, "");

    TestTransformation test_transform;
    uut.transform(test_transform);
    BOOST_CHECK_EQUAL(uut.call_string, "c");
    uut.transform(test_transform);
    BOOST_CHECK_EQUAL(uut.call_string, "cc");
    uut.call_string = "ab";
    uut.transform(test_transform);
    BOOST_CHECK_EQUAL(uut.call_string, "abc");
    uut.transform(test_transform);
    uut.transform(test_transform);
    BOOST_CHECK_EQUAL(uut.call_string, "abccc");
}

BOOST_AUTO_TEST_SUITE_END()
