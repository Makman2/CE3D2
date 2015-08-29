#define BOOST_TEST_MODULE ModelTest
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "CE3D2/models/Model.h"
#include "CE3D2/tests/TestUtilities.h"


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
    auto& vecs = uut.get_vectors();

    BOOST_CHECK_EQUAL(uut.get_vectors().size(), 0);
    vecs.push_back(CE3D2::ZeroVector(3));
    BOOST_CHECK_EQUAL(uut.get_vectors().size(), 1);
    BOOST_CHECK_VECTORS_EQUAL(uut.get_vectors()[0], CE3D2::ZeroVector(3));
    vecs.push_back(CE3D2::UnitVector(3, 2));
    BOOST_CHECK_EQUAL(uut.get_vectors().size(), 2);
    BOOST_CHECK_VECTORS_EQUAL(uut.get_vectors()[0], CE3D2::ZeroVector(3));
    BOOST_CHECK_VECTORS_EQUAL(uut.get_vectors()[1], CE3D2::UnitVector(3, 2));
    vecs.clear();
    BOOST_CHECK_EQUAL(uut.get_vectors().size(), 0);
}

BOOST_AUTO_TEST_SUITE_END()