#define BOOST_TEST_MODULE LineModelTest
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "CE3D2/models/LineModel.h"
#include "CE3D2/tests/TestUtilities.h"


BOOST_AUTO_TEST_SUITE(LineModelTestSuite)

BOOST_AUTO_TEST_CASE(test_inheritted_interface)
{
    CE3D2::Models::LineModel uut;
    BOOST_CHECK_EQUAL(uut.get_name(), "");
    uut.set_name("Hello world");
    BOOST_CHECK_EQUAL(uut.get_name(), "Hello world");

    uut = CE3D2::Models::LineModel("initial-name");
    BOOST_CHECK_EQUAL(uut.get_name(), "initial-name");
}

BOOST_AUTO_TEST_CASE(test_from_model_constructor)
{
    std::vector<CE3D2::Vector> vecs;
    vecs.push_back(CE3D2::create_vector(2.0f, 3.4f));
    vecs.push_back(CE3D2::create_vector(4.1f, -11.1f));
    vecs.push_back(CE3D2::create_vector(0.0f, 0.0f));

    CE3D2::Models::Model model("mymodel");
    model.vectors().push_back(vecs[0]);
    model.vectors().push_back(vecs[1]);
    model.vectors().push_back(vecs[2]);

    auto uut = CE3D2::Models::LineModel(model);

    BOOST_CHECK_EQUAL(uut.get_name(), "mymodel");

    BOOST_CHECK_EQUAL(uut.vectors().size(), 3);
    CE3D2_CHECK_VECTORS_EQUAL(uut.vectors()[0], vecs[0]);
    CE3D2_CHECK_VECTORS_EQUAL(uut.vectors()[1], vecs[1]);
    CE3D2_CHECK_VECTORS_EQUAL(uut.vectors()[2], vecs[2]);

    BOOST_CHECK_EQUAL(uut.connections().size(), 0);
}

BOOST_AUTO_TEST_CASE(test_connections)
{
    CE3D2::Models::LineModel uut;

    BOOST_CHECK_EQUAL(uut.connections().size(), 0);

    auto ip = CE3D2::Models::IndexPair(0, 1);
    uut.connections().push_back(ip);
    BOOST_CHECK_EQUAL(uut.connections().size(), 1);
    CE3D2_CHECK_INDEX_PAIRS_EQUAL(uut.connections()[0], ip);

    auto ip2 = CE3D2::Models::IndexPair(55, 142);
    uut.connections().push_back(ip2);
    BOOST_CHECK_EQUAL(uut.connections().size(), 2);
    CE3D2_CHECK_INDEX_PAIRS_EQUAL(uut.connections()[0], ip);
    CE3D2_CHECK_INDEX_PAIRS_EQUAL(uut.connections()[1], ip2);

    uut.connections().clear();
    BOOST_CHECK_EQUAL(uut.connections().size(), 0);
}

BOOST_AUTO_TEST_SUITE_END()
