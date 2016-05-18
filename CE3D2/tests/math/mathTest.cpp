#define BOOST_TEST_MODULE mathTest
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "CE3D2/math/math.h"


BOOST_AUTO_TEST_SUITE(mathTestSuite)

BOOST_AUTO_TEST_CASE(test_line_intersection_with_box)
{
    CE3D2::Math::Box box(1.0f, 1.0f, 4.0f, 2.0f);
    CE3D2::Math::LinearAffineFunction line(0.0f, 2.0f);

    // Hits from left to right.
    auto result = CE3D2::Math::line_intersection_with_box(line, box);
    BOOST_CHECK_EQUAL(result.size(), 2);
    BOOST_CHECK_EQUAL(result[0].first, 1.0f);
    BOOST_CHECK_EQUAL(result[0].second, 2.0f);
    BOOST_CHECK_EQUAL(result[1].first, 5.0f);
    BOOST_CHECK_EQUAL(result[1].second, 2.0f);

    // Hits from bottom to top.
    line = CE3D2::Math::LinearAffineFunction(1.0f, -1.0f);
    result = CE3D2::Math::line_intersection_with_box(line, box);
    BOOST_CHECK_EQUAL(result.size(), 2);
    BOOST_CHECK_EQUAL(result[0].first, 2.0f);
    BOOST_CHECK_EQUAL(result[0].second, 1.0f);
    BOOST_CHECK_EQUAL(result[1].first, 4.0f);
    BOOST_CHECK_EQUAL(result[1].second, 3.0f);

    // Hits from top to bottom.
    line = CE3D2::Math::LinearAffineFunction(-1.0f, 5.0f);
    result = CE3D2::Math::line_intersection_with_box(line, box);
    BOOST_CHECK_EQUAL(result.size(), 2);
    BOOST_CHECK_EQUAL(result[0].first, 4.0f);
    BOOST_CHECK_EQUAL(result[0].second, 1.0f);
    BOOST_CHECK_EQUAL(result[1].first, 2.0f);
    BOOST_CHECK_EQUAL(result[1].second, 3.0f);

    // Doesn't hit at all.
    line = CE3D2::Math::LinearAffineFunction(1.0f, 5.0f);
    result = CE3D2::Math::line_intersection_with_box(line, box);
    BOOST_CHECK_EQUAL(result.size(), 0);

    // Hits from left to top.
    line = CE3D2::Math::LinearAffineFunction(0.5f, 1.5f);
    result = CE3D2::Math::line_intersection_with_box(line, box);
    BOOST_CHECK_EQUAL(result.size(), 2);
    BOOST_CHECK_EQUAL(result[0].first, 1.0f);
    BOOST_CHECK_EQUAL(result[0].second, 2.0f);
    BOOST_CHECK_EQUAL(result[1].first, 3.0f);
    BOOST_CHECK_EQUAL(result[1].second, 3.0f);

    // Hits from left to bottom.
    line = CE3D2::Math::LinearAffineFunction(-0.5f, 2.5f);
    result = CE3D2::Math::line_intersection_with_box(line, box);
    BOOST_CHECK_EQUAL(result.size(), 2);
    BOOST_CHECK_EQUAL(result[0].first, 1.0f);
    BOOST_CHECK_EQUAL(result[0].second, 2.0f);
    BOOST_CHECK_EQUAL(result[1].first, 3.0f);
    BOOST_CHECK_EQUAL(result[1].second, 1.0f);

    // Hits from top to right.
    line = CE3D2::Math::LinearAffineFunction(-2.0f, 11.5f);
    result = CE3D2::Math::line_intersection_with_box(line, box);
    BOOST_CHECK_EQUAL(result.size(), 2);
    BOOST_CHECK_EQUAL(result[0].first, 5.0f);
    BOOST_CHECK_EQUAL(result[0].second, 1.5f);
    BOOST_CHECK_EQUAL(result[1].first, 4.25f);
    BOOST_CHECK_EQUAL(result[1].second, 3.0f);

    // Hits from bottom to right.
    line = CE3D2::Math::LinearAffineFunction(0.5f, -0.5f);
    result = CE3D2::Math::line_intersection_with_box(line, box);
    BOOST_CHECK_EQUAL(result.size(), 2);
    BOOST_CHECK_EQUAL(result[0].first, 5.0f);
    BOOST_CHECK_EQUAL(result[0].second, 2.0f);
    BOOST_CHECK_EQUAL(result[1].first, 3.0f);
    BOOST_CHECK_EQUAL(result[1].second, 1.0f);
}

BOOST_AUTO_TEST_SUITE_END()
