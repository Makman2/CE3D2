#define BOOST_TEST_MODULE InvalidFileExceptionTest
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "CE3D2/models/loaders/InvalidFileException.h"
#include "TestUtilities.h"


BOOST_AUTO_TEST_SUITE(InvalidFileExceptionTestSuite)

    BOOST_AUTO_TEST_CASE(test_exception)
    {
        CE3D2_CHECK_EXCEPTION(
            throw CE3D2::Models::Loaders::InvalidFileException(
                "exception message"),
            CE3D2::Models::Loaders::InvalidFileException,
            "exception message");
    }

BOOST_AUTO_TEST_SUITE_END()
