#define BOOST_TEST_MODULE stringsTest
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "CE3D2/tests/TestUtilities.h"
#include "CE3D2/strings/strings.h"


BOOST_AUTO_TEST_SUITE(stringsTestSuite)

BOOST_AUTO_TEST_CASE(test_to_float)
{
    BOOST_CHECK_EQUAL(CE3D2::Strings::to_float("1.0"),
                      1.0f);
    BOOST_CHECK_EQUAL(CE3D2::Strings::to_float("133.44"),
                      133.44f);
    BOOST_CHECK_EQUAL(CE3D2::Strings::to_float("-12.0"),
                      -12.0f);

    CE3D2_CHECK_EXCEPTION(CE3D2::Strings::to_float("x"),
                          std::invalid_argument,
                          "stof");
    CE3D2_CHECK_EXCEPTION(CE3D2::Strings::to_float("3.x"),
                          std::invalid_argument,
                          "Can't convert string to float: 3.x");
    CE3D2_CHECK_EXCEPTION(CE3D2::Strings::to_float("2.0 3.0"),
                          std::invalid_argument,
                          "Can't convert string to float: 2.0 3.0");
}

BOOST_AUTO_TEST_SUITE_END()
