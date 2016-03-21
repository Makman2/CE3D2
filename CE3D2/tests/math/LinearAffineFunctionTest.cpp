#define BOOST_TEST_MODULE LinearAffineFunctionTest
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "CE3D2/math/LinearAffineFunction.h"


BOOST_AUTO_TEST_SUITE(LinearAffineFunctionTestSuite)

BOOST_AUTO_TEST_CASE(test_construction)
{
    CE3D2::Math::LinearAffineFunction uut;
    BOOST_CHECK_EQUAL(uut.get_gradient(), 1.0f);
    BOOST_CHECK_EQUAL(uut.get_yintercept(), 0.0f);

    uut = CE3D2::Math::LinearAffineFunction(-12.0f);
    BOOST_CHECK_EQUAL(uut.get_gradient(), -12.0f);
    BOOST_CHECK_EQUAL(uut.get_yintercept(), 0.0f);

    uut = CE3D2::Math::LinearAffineFunction(4.0f, 2.5f);
    BOOST_CHECK_EQUAL(uut.get_gradient(), 4.0f);
    BOOST_CHECK_EQUAL(uut.get_yintercept(), 2.5f);

    // Test the construction from two coordinate-points.
    uut = CE3D2::Math::LinearAffineFunction(0.0f, 0.0f, 1.0f, 1.0f);
    BOOST_CHECK_EQUAL(uut.get_gradient(), 1.0f);
    BOOST_CHECK_EQUAL(uut.get_yintercept(), 0.0f);

    uut = CE3D2::Math::LinearAffineFunction(1.0f, 1.0f, 3.0f, 0.0f);
    BOOST_CHECK_EQUAL(uut.get_gradient(), -0.5f);
    BOOST_CHECK_EQUAL(uut.get_yintercept(), 1.5f);
}

BOOST_AUTO_TEST_CASE(test_gradient_property)
{
    CE3D2::Math::LinearAffineFunction uut;
    uut.set_gradient(44.0f);
    BOOST_CHECK_EQUAL(uut.get_gradient(), 44.0f);
}

BOOST_AUTO_TEST_CASE(test_yintercept_property)
{
    CE3D2::Math::LinearAffineFunction uut;
    uut.set_yintercept(17.4f);
    BOOST_CHECK_EQUAL(uut.get_yintercept(), 17.4f);
}

BOOST_AUTO_TEST_CASE(test_evaluation)
{
    CE3D2::Math::LinearAffineFunction uut(4.0f, 2.0f);
    BOOST_CHECK_EQUAL(uut(-1.0f), -2.0f);
    BOOST_CHECK_EQUAL(uut(0.0f), 2.0f);
    BOOST_CHECK_EQUAL(uut(2.0f), 10.0f);

    uut = CE3D2::Math::LinearAffineFunction(-0.5f, -1.0f);
    BOOST_CHECK_EQUAL(uut(-2.0f), 0.0f);
    BOOST_CHECK_EQUAL(uut(0.0f), -1.0f);
    BOOST_CHECK_EQUAL(uut(1.0f), -1.5f);
}

BOOST_AUTO_TEST_SUITE_END()
