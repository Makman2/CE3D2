#define BOOST_TEST_MODULE FileFormatExceptionTest
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "CE3D2/models/loaders/FileFormatException.h"
#include "TestUtilities.h"


BOOST_AUTO_TEST_SUITE(FileFormatExceptionTestSuite)

    BOOST_AUTO_TEST_CASE(test_exception)
    {
        CE3D2_CHECK_EXCEPTION(
            throw CE3D2::Models::Loaders::FileFormatException(
                "exception message"),
            CE3D2::Models::Loaders::FileFormatException,
            "exception message");
    }

BOOST_AUTO_TEST_SUITE_END()
