#define BOOST_TEST_MODULE IndexPairTest
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "CE3D2/models/IndexPair.h"


BOOST_AUTO_TEST_SUITE(IndexPairTestSuite)

BOOST_AUTO_TEST_CASE(test_pair)
{
    auto uut = CE3D2::Models::IndexPair(0, 50);
    BOOST_CHECK_EQUAL(uut.first, 0);
    BOOST_CHECK_EQUAL(uut.second, 50);
}

BOOST_AUTO_TEST_SUITE_END()
