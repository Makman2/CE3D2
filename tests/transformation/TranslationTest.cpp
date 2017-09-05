#define BOOST_TEST_MODULE TranslationTest
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "CE3D2/transformation/Translation.h"
#include "TestUtilities.h"


BOOST_AUTO_TEST_SUITE(TranslationTestSuite)

BOOST_AUTO_TEST_CASE(test_translation_vector)
{
    CE3D2::Vector translation = CE3D2::create_vector(0.1f, 0.2f, 0.3f);
    auto uut = CE3D2::Transformation::Translation(translation);

    CE3D2_CHECK_VECTORS_EQUAL(uut.get_translation(), translation);

    translation = CE3D2::create_vector(2.4f, -3.0f);
    uut.set_translation(translation);

    CE3D2_CHECK_VECTORS_EQUAL(uut.get_translation(), translation);

    // Check for mutability.
    translation[0] = 88.0f;
    uut.get_translation()[0] = 88.0f;

    CE3D2_CHECK_VECTORS_EQUAL(uut.get_translation(), translation);
}

BOOST_AUTO_TEST_CASE(test_translation)
{
    auto testvector1 = CE3D2::create_vector(-1.0f, 0.0f);
    auto testvector2 = CE3D2::create_vector(22.4f, 7.2f);

    auto uut = CE3D2::Transformation::Translation(
        CE3D2::create_vector(2.0f, 3.0f));

    uut.transform_vector(testvector1);
    CE3D2_CHECK_VECTORS_EQUAL(testvector1, CE3D2::create_vector(1.0f, 3.0f));
    uut.transform_vector(testvector2);
    CE3D2_CHECK_VECTORS_EQUAL(testvector2, CE3D2::create_vector(24.4f, 10.2f));
}

BOOST_AUTO_TEST_SUITE_END()
