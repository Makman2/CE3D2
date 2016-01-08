#define BOOST_TEST_MODULE ModelTest
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "CE3D2/models/Model.h"
#include "CE3D2/tests/TestUtilities.h"
#include "CE3D2/transformation/Scale.h"


BOOST_AUTO_TEST_SUITE(ModelTestSuite)

BOOST_AUTO_TEST_CASE(test_name)
{
    CE3D2::Models::Model uut;
    BOOST_CHECK_EQUAL(uut.get_name(), "");
    uut.set_name("Hello world");
    BOOST_CHECK_EQUAL(uut.get_name(), "Hello world");
    uut.set_name("123456-+#!?");
    BOOST_CHECK_EQUAL(uut.get_name(), "123456-+#!?");

    uut = CE3D2::Models::Model("initial-name");
    BOOST_CHECK_EQUAL(uut.get_name(), "initial-name");
    uut.set_name("set_after_init");
    BOOST_CHECK_EQUAL(uut.get_name(), "set_after_init");
}

BOOST_AUTO_TEST_CASE(test_visibility)
{
    CE3D2::Models::Model uut;
    BOOST_CHECK_EQUAL(uut.is_visible(), true);

    uut.set_visibility(true);
    BOOST_CHECK_EQUAL(uut.is_visible(), true);
    uut.set_visibility(false);
    BOOST_CHECK_EQUAL(uut.is_visible(), false);
    uut.set_visibility(true);
    BOOST_CHECK_EQUAL(uut.is_visible(), true);
}

BOOST_AUTO_TEST_CASE(test_vectors)
{
    CE3D2::Models::Model uut;
    auto& vecs = uut.vectors();

    BOOST_CHECK_EQUAL(uut.vectors().size(), 0);
    vecs.push_back(CE3D2::ZeroVector(3));
    BOOST_CHECK_EQUAL(uut.vectors().size(), 1);
    CE3D2_CHECK_VECTORS_EQUAL(uut.vectors()[0], CE3D2::ZeroVector(3));
    vecs.push_back(CE3D2::UnitVector(3, 2));
    BOOST_CHECK_EQUAL(uut.vectors().size(), 2);
    CE3D2_CHECK_VECTORS_EQUAL(uut.vectors()[0], CE3D2::ZeroVector(3));
    CE3D2_CHECK_VECTORS_EQUAL(uut.vectors()[1], CE3D2::UnitVector(3, 2));
    vecs.clear();
    BOOST_CHECK_EQUAL(uut.vectors().size(), 0);
}

BOOST_AUTO_TEST_CASE(test_ITransformable)
{
    CE3D2::Models::Model uut;
    auto& vecs = uut.vectors();

    vecs.push_back(CE3D2_CREATE_VECTOR(1.0f, 2.0f, 3.0f));
    vecs.push_back(CE3D2_CREATE_VECTOR(-2.0f, 3.3f, 22.0f));
    vecs.push_back(CE3D2_CREATE_VECTOR(4.0f, 2.5f, 0.0f));

    CE3D2::Transformation::Scale scale_transform(
        CE3D2_CREATE_VECTOR(2.0f, 2.0f, 2.0f));

    uut.transform(scale_transform);

    CE3D2_CHECK_VECTORS_EQUAL(vecs[0], CE3D2_CREATE_VECTOR(2.0f, 4.0f, 6.0f));
    CE3D2_CHECK_VECTORS_EQUAL(vecs[1], CE3D2_CREATE_VECTOR(-4.0f, 6.6f, 44.0f));
    CE3D2_CHECK_VECTORS_EQUAL(vecs[2], CE3D2_CREATE_VECTOR(8.0f, 5.0f, 0.0f));
}

BOOST_AUTO_TEST_SUITE_END()
