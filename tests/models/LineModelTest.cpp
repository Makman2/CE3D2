#define BOOST_TEST_MODULE LineModelTest
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "CE3D2/models/LineModel.h"
#include "TestUtilities.h"


BOOST_AUTO_TEST_SUITE(LineModelTestSuite)

struct HypercubeConnectionsFixture
{
    HypercubeConnectionsFixture()
    : F_connections()
    {
        F_connections.reserve(80);

        F_connections.push_back(CE3D2::Models::IndexPair(0, 1));

        F_connections.push_back(CE3D2::Models::IndexPair(2, 3));

        F_connections.push_back(CE3D2::Models::IndexPair(0, 2));
        F_connections.push_back(CE3D2::Models::IndexPair(1, 3));

        F_connections.push_back(CE3D2::Models::IndexPair(4, 5));
        F_connections.push_back(CE3D2::Models::IndexPair(6, 7));
        F_connections.push_back(CE3D2::Models::IndexPair(4, 6));
        F_connections.push_back(CE3D2::Models::IndexPair(5, 7));

        F_connections.push_back(CE3D2::Models::IndexPair(0, 4));
        F_connections.push_back(CE3D2::Models::IndexPair(1, 5));
        F_connections.push_back(CE3D2::Models::IndexPair(2, 6));
        F_connections.push_back(CE3D2::Models::IndexPair(3, 7));

        F_connections.push_back(CE3D2::Models::IndexPair(8, 9));
        F_connections.push_back(CE3D2::Models::IndexPair(10, 11));
        F_connections.push_back(CE3D2::Models::IndexPair(8, 10));
        F_connections.push_back(CE3D2::Models::IndexPair(9, 11));
        F_connections.push_back(CE3D2::Models::IndexPair(12, 13));
        F_connections.push_back(CE3D2::Models::IndexPair(14, 15));
        F_connections.push_back(CE3D2::Models::IndexPair(12, 14));
        F_connections.push_back(CE3D2::Models::IndexPair(13, 15));
        F_connections.push_back(CE3D2::Models::IndexPair(8, 12));
        F_connections.push_back(CE3D2::Models::IndexPair(9, 13));
        F_connections.push_back(CE3D2::Models::IndexPair(10, 14));
        F_connections.push_back(CE3D2::Models::IndexPair(11, 15));

        F_connections.push_back(CE3D2::Models::IndexPair(0, 8));
        F_connections.push_back(CE3D2::Models::IndexPair(1, 9));
        F_connections.push_back(CE3D2::Models::IndexPair(2, 10));
        F_connections.push_back(CE3D2::Models::IndexPair(3, 11));
        F_connections.push_back(CE3D2::Models::IndexPair(4, 12));
        F_connections.push_back(CE3D2::Models::IndexPair(5, 13));
        F_connections.push_back(CE3D2::Models::IndexPair(6, 14));
        F_connections.push_back(CE3D2::Models::IndexPair(7, 15));

        F_connections.push_back(CE3D2::Models::IndexPair(16, 17));
        F_connections.push_back(CE3D2::Models::IndexPair(18, 19));
        F_connections.push_back(CE3D2::Models::IndexPair(16, 18));
        F_connections.push_back(CE3D2::Models::IndexPair(17, 19));
        F_connections.push_back(CE3D2::Models::IndexPair(20, 21));
        F_connections.push_back(CE3D2::Models::IndexPair(22, 23));
        F_connections.push_back(CE3D2::Models::IndexPair(20, 22));
        F_connections.push_back(CE3D2::Models::IndexPair(21, 23));
        F_connections.push_back(CE3D2::Models::IndexPair(16, 20));
        F_connections.push_back(CE3D2::Models::IndexPair(17, 21));
        F_connections.push_back(CE3D2::Models::IndexPair(18, 22));
        F_connections.push_back(CE3D2::Models::IndexPair(19, 23));
        F_connections.push_back(CE3D2::Models::IndexPair(24, 25));
        F_connections.push_back(CE3D2::Models::IndexPair(26, 27));
        F_connections.push_back(CE3D2::Models::IndexPair(24, 26));
        F_connections.push_back(CE3D2::Models::IndexPair(25, 27));
        F_connections.push_back(CE3D2::Models::IndexPair(28, 29));
        F_connections.push_back(CE3D2::Models::IndexPair(30, 31));
        F_connections.push_back(CE3D2::Models::IndexPair(28, 30));
        F_connections.push_back(CE3D2::Models::IndexPair(29, 31));
        F_connections.push_back(CE3D2::Models::IndexPair(24, 28));
        F_connections.push_back(CE3D2::Models::IndexPair(25, 29));
        F_connections.push_back(CE3D2::Models::IndexPair(26, 30));
        F_connections.push_back(CE3D2::Models::IndexPair(27, 31));
        F_connections.push_back(CE3D2::Models::IndexPair(16, 24));
        F_connections.push_back(CE3D2::Models::IndexPair(17, 25));
        F_connections.push_back(CE3D2::Models::IndexPair(18, 26));
        F_connections.push_back(CE3D2::Models::IndexPair(19, 27));
        F_connections.push_back(CE3D2::Models::IndexPair(20, 28));
        F_connections.push_back(CE3D2::Models::IndexPair(21, 29));
        F_connections.push_back(CE3D2::Models::IndexPair(22, 30));
        F_connections.push_back(CE3D2::Models::IndexPair(23, 31));

        F_connections.push_back(CE3D2::Models::IndexPair(0, 16));
        F_connections.push_back(CE3D2::Models::IndexPair(1, 17));
        F_connections.push_back(CE3D2::Models::IndexPair(2, 18));
        F_connections.push_back(CE3D2::Models::IndexPair(3, 19));
        F_connections.push_back(CE3D2::Models::IndexPair(4, 20));
        F_connections.push_back(CE3D2::Models::IndexPair(5, 21));
        F_connections.push_back(CE3D2::Models::IndexPair(6, 22));
        F_connections.push_back(CE3D2::Models::IndexPair(7, 23));
        F_connections.push_back(CE3D2::Models::IndexPair(8, 24));
        F_connections.push_back(CE3D2::Models::IndexPair(9, 25));
        F_connections.push_back(CE3D2::Models::IndexPair(10, 26));
        F_connections.push_back(CE3D2::Models::IndexPair(11, 27));
        F_connections.push_back(CE3D2::Models::IndexPair(12, 28));
        F_connections.push_back(CE3D2::Models::IndexPair(13, 29));
        F_connections.push_back(CE3D2::Models::IndexPair(14, 30));
        F_connections.push_back(CE3D2::Models::IndexPair(15, 31));
    }

    std::remove_reference<decltype(std::declval<
        CE3D2::Models::LineModel>().connections())>::type
    F_connections;
};

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

#define CHECK_HYPERCUBE_CONNECTIONS(result)                                \
    for (std::remove_reference<decltype(                                   \
             std::declval<CE3D2::Models::LineModel>().connections())>      \
             ::type::size_type i = 0;                                      \
         i < (result).size();                                              \
         i++)                                                              \
    {                                                                      \
        CE3D2_CHECK_INDEX_PAIRS_EQUAL((result)[i], F_connections[i]);      \
    }

BOOST_FIXTURE_TEST_CASE(test_square, HypercubeConnectionsFixture)
{
    auto uut = CE3D2::Models::LineModel::square();

    BOOST_CHECK_EQUAL(uut.vectors().size(), 4);
    CE3D2_CHECK_VECTORS_EQUAL(uut.vectors()[0],
                              CE3D2::create_vector(0.5f, 0.5f));
    CE3D2_CHECK_VECTORS_EQUAL(uut.vectors()[1],
                              CE3D2::create_vector(-0.5f, 0.5f));
    CE3D2_CHECK_VECTORS_EQUAL(uut.vectors()[2],
                              CE3D2::create_vector(0.5f, -0.5f));
    CE3D2_CHECK_VECTORS_EQUAL(uut.vectors()[3],
                              CE3D2::create_vector(-0.5f, -0.5f));

    BOOST_CHECK_EQUAL(uut.connections().size(), 4);
    CHECK_HYPERCUBE_CONNECTIONS(uut.connections());
}

BOOST_FIXTURE_TEST_CASE(test_cube, HypercubeConnectionsFixture)
{
    auto uut = CE3D2::Models::LineModel::cube();

    BOOST_CHECK_EQUAL(uut.vectors().size(), 8);
    CE3D2_CHECK_VECTORS_EQUAL(uut.vectors()[0],
                              CE3D2::create_vector(0.5f, 0.5f, 0.5f));
    CE3D2_CHECK_VECTORS_EQUAL(uut.vectors()[1],
                              CE3D2::create_vector(-0.5f, 0.5f, 0.5f));
    CE3D2_CHECK_VECTORS_EQUAL(uut.vectors()[2],
                              CE3D2::create_vector(0.5f, -0.5f, 0.5f));
    CE3D2_CHECK_VECTORS_EQUAL(uut.vectors()[3],
                              CE3D2::create_vector(-0.5f, -0.5f, 0.5f));
    CE3D2_CHECK_VECTORS_EQUAL(uut.vectors()[4],
                              CE3D2::create_vector(0.5f, 0.5f, -0.5f));
    CE3D2_CHECK_VECTORS_EQUAL(uut.vectors()[5],
                              CE3D2::create_vector(-0.5f, 0.5f, -0.5f));
    CE3D2_CHECK_VECTORS_EQUAL(uut.vectors()[6],
                              CE3D2::create_vector(0.5f, -0.5f, -0.5f));
    CE3D2_CHECK_VECTORS_EQUAL(uut.vectors()[7],
                              CE3D2::create_vector(-0.5f, -0.5f, -0.5f));

    BOOST_CHECK_EQUAL(uut.connections().size(), 12);
    CHECK_HYPERCUBE_CONNECTIONS(uut.connections());
}

BOOST_FIXTURE_TEST_CASE(test_tesseract, HypercubeConnectionsFixture)
{
    auto uut = CE3D2::Models::LineModel::tesseract();

    BOOST_CHECK_EQUAL(uut.vectors().size(), 16);
    CE3D2_CHECK_VECTORS_EQUAL(uut.vectors()[0],
                              CE3D2::create_vector(0.5f, 0.5f, 0.5f, 0.5f));
    CE3D2_CHECK_VECTORS_EQUAL(uut.vectors()[1],
                              CE3D2::create_vector(-0.5f, 0.5f, 0.5f, 0.5f));
    CE3D2_CHECK_VECTORS_EQUAL(uut.vectors()[2],
                              CE3D2::create_vector(0.5f, -0.5f, 0.5f, 0.5f));
    CE3D2_CHECK_VECTORS_EQUAL(uut.vectors()[3],
                              CE3D2::create_vector(-0.5f, -0.5f, 0.5f, 0.5f));
    CE3D2_CHECK_VECTORS_EQUAL(uut.vectors()[4],
                              CE3D2::create_vector(0.5f, 0.5f, -0.5f, 0.5f));
    CE3D2_CHECK_VECTORS_EQUAL(uut.vectors()[5],
                              CE3D2::create_vector(-0.5f, 0.5f, -0.5f, 0.5f));
    CE3D2_CHECK_VECTORS_EQUAL(uut.vectors()[6],
                              CE3D2::create_vector(0.5f, -0.5f, -0.5f, 0.5f));
    CE3D2_CHECK_VECTORS_EQUAL(uut.vectors()[7],
                              CE3D2::create_vector(-0.5f, -0.5f, -0.5f, 0.5f));
    CE3D2_CHECK_VECTORS_EQUAL(uut.vectors()[8],
                              CE3D2::create_vector(0.5f, 0.5f, 0.5f, -0.5f));
    CE3D2_CHECK_VECTORS_EQUAL(uut.vectors()[9],
                              CE3D2::create_vector(-0.5f, 0.5f, 0.5f, -0.5f));
    CE3D2_CHECK_VECTORS_EQUAL(uut.vectors()[10],
                              CE3D2::create_vector(0.5f, -0.5f, 0.5f, -0.5f));
    CE3D2_CHECK_VECTORS_EQUAL(uut.vectors()[11],
                              CE3D2::create_vector(-0.5f, -0.5f, 0.5f, -0.5f));
    CE3D2_CHECK_VECTORS_EQUAL(uut.vectors()[12],
                              CE3D2::create_vector(0.5f, 0.5f, -0.5f, -0.5f));
    CE3D2_CHECK_VECTORS_EQUAL(uut.vectors()[13],
                              CE3D2::create_vector(-0.5f, 0.5f, -0.5f, -0.5f));
    CE3D2_CHECK_VECTORS_EQUAL(uut.vectors()[14],
                              CE3D2::create_vector(0.5f, -0.5f, -0.5f, -0.5f));
    CE3D2_CHECK_VECTORS_EQUAL(uut.vectors()[15],
                              CE3D2::create_vector(-0.5f, -0.5f, -0.5f, -0.5f));

    BOOST_CHECK_EQUAL(uut.connections().size(), 32);
    CHECK_HYPERCUBE_CONNECTIONS(uut.connections());
}

BOOST_FIXTURE_TEST_CASE(test_hypercube, HypercubeConnectionsFixture)
{
    // Test the machine limit by providing an insane number.
    BOOST_CHECK_THROW(CE3D2::Models::LineModel::hypercube(1000000),
                      std::invalid_argument);

    // Test the 1D case.
    auto uut = CE3D2::Models::LineModel::hypercube(1);
    BOOST_CHECK_EQUAL(uut.vectors().size(), 2);
    CE3D2_CHECK_VECTORS_EQUAL(uut.vectors()[0], CE3D2::create_vector(0.5f));
    CE3D2_CHECK_VECTORS_EQUAL(uut.vectors()[1], CE3D2::create_vector(-0.5f));

    BOOST_CHECK_EQUAL(uut.connections().size(), 1);
    CHECK_HYPERCUBE_CONNECTIONS(uut.connections());

    // Test the 5D case.
    uut = CE3D2::Models::LineModel::hypercube(5);

    BOOST_CHECK_EQUAL(uut.vectors().size(), 32);
    CE3D2_CHECK_VECTORS_EQUAL(
        uut.vectors()[0],
        CE3D2::create_vector(0.5f, 0.5f, 0.5f, 0.5f, 0.5f));
    CE3D2_CHECK_VECTORS_EQUAL(
        uut.vectors()[1],
        CE3D2::create_vector(-0.5f, 0.5f, 0.5f, 0.5f, 0.5f));
    CE3D2_CHECK_VECTORS_EQUAL(
        uut.vectors()[2],
        CE3D2::create_vector(0.5f, -0.5f, 0.5f, 0.5f, 0.5f));
    CE3D2_CHECK_VECTORS_EQUAL(
        uut.vectors()[3],
        CE3D2::create_vector(-0.5f, -0.5f, 0.5f, 0.5f, 0.5f));
    CE3D2_CHECK_VECTORS_EQUAL(
        uut.vectors()[4],
        CE3D2::create_vector(0.5f, 0.5f, -0.5f, 0.5f, 0.5f));
    CE3D2_CHECK_VECTORS_EQUAL(
        uut.vectors()[5],
        CE3D2::create_vector(-0.5f, 0.5f, -0.5f, 0.5f, 0.5f));
    CE3D2_CHECK_VECTORS_EQUAL(
        uut.vectors()[6],
        CE3D2::create_vector(0.5f, -0.5f, -0.5f, 0.5f, 0.5f));
    CE3D2_CHECK_VECTORS_EQUAL(
        uut.vectors()[7],
        CE3D2::create_vector(-0.5f, -0.5f, -0.5f, 0.5f, 0.5f));
    CE3D2_CHECK_VECTORS_EQUAL(
        uut.vectors()[8],
        CE3D2::create_vector(0.5f, 0.5f, 0.5f, -0.5f, 0.5f));
    CE3D2_CHECK_VECTORS_EQUAL(
        uut.vectors()[9],
        CE3D2::create_vector(-0.5f, 0.5f, 0.5f, -0.5f, 0.5f));
    CE3D2_CHECK_VECTORS_EQUAL(
        uut.vectors()[10],
        CE3D2::create_vector(0.5f, -0.5f, 0.5f, -0.5f, 0.5f));
    CE3D2_CHECK_VECTORS_EQUAL(
        uut.vectors()[11],
        CE3D2::create_vector(-0.5f, -0.5f, 0.5f, -0.5f, 0.5f));
    CE3D2_CHECK_VECTORS_EQUAL(
        uut.vectors()[12],
        CE3D2::create_vector(0.5f, 0.5f, -0.5f, -0.5f, 0.5f));
    CE3D2_CHECK_VECTORS_EQUAL(
        uut.vectors()[13],
        CE3D2::create_vector(-0.5f, 0.5f, -0.5f, -0.5f, 0.5f));
    CE3D2_CHECK_VECTORS_EQUAL(
        uut.vectors()[14],
        CE3D2::create_vector(0.5f, -0.5f, -0.5f, -0.5f, 0.5f));
    CE3D2_CHECK_VECTORS_EQUAL(
        uut.vectors()[15],
        CE3D2::create_vector(-0.5f, -0.5f, -0.5f, -0.5f, 0.5f));
    CE3D2_CHECK_VECTORS_EQUAL(
        uut.vectors()[16],
        CE3D2::create_vector(0.5f, 0.5f, 0.5f, 0.5f, -0.5f));
    CE3D2_CHECK_VECTORS_EQUAL(
        uut.vectors()[17],
        CE3D2::create_vector(-0.5f, 0.5f, 0.5f, 0.5f, -0.5f));
    CE3D2_CHECK_VECTORS_EQUAL(
        uut.vectors()[18],
        CE3D2::create_vector(0.5f, -0.5f, 0.5f, 0.5f, -0.5f));
    CE3D2_CHECK_VECTORS_EQUAL(
        uut.vectors()[19],
        CE3D2::create_vector(-0.5f, -0.5f, 0.5f, 0.5f, -0.5f));
    CE3D2_CHECK_VECTORS_EQUAL(
        uut.vectors()[20],
        CE3D2::create_vector(0.5f, 0.5f, -0.5f, 0.5f, -0.5f));
    CE3D2_CHECK_VECTORS_EQUAL(
        uut.vectors()[21],
        CE3D2::create_vector(-0.5f, 0.5f, -0.5f, 0.5f, -0.5f));
    CE3D2_CHECK_VECTORS_EQUAL(
        uut.vectors()[22],
        CE3D2::create_vector(0.5f, -0.5f, -0.5f, 0.5f, -0.5f));
    CE3D2_CHECK_VECTORS_EQUAL(
        uut.vectors()[23],
        CE3D2::create_vector(-0.5f, -0.5f, -0.5f, 0.5f, -0.5f));
    CE3D2_CHECK_VECTORS_EQUAL(
        uut.vectors()[24],
        CE3D2::create_vector(0.5f, 0.5f, 0.5f, -0.5f, -0.5f));
    CE3D2_CHECK_VECTORS_EQUAL(
        uut.vectors()[25],
        CE3D2::create_vector(-0.5f, 0.5f, 0.5f, -0.5f, -0.5f));
    CE3D2_CHECK_VECTORS_EQUAL(
        uut.vectors()[26],
        CE3D2::create_vector(0.5f, -0.5f, 0.5f, -0.5f, -0.5f));
    CE3D2_CHECK_VECTORS_EQUAL(
        uut.vectors()[27],
        CE3D2::create_vector(-0.5f, -0.5f, 0.5f, -0.5f, -0.5f));
    CE3D2_CHECK_VECTORS_EQUAL(
        uut.vectors()[28],
        CE3D2::create_vector(0.5f, 0.5f, -0.5f, -0.5f, -0.5f));
    CE3D2_CHECK_VECTORS_EQUAL(
        uut.vectors()[29],
        CE3D2::create_vector(-0.5f, 0.5f, -0.5f, -0.5f, -0.5f));
    CE3D2_CHECK_VECTORS_EQUAL(
        uut.vectors()[30],
        CE3D2::create_vector(0.5f, -0.5f, -0.5f, -0.5f, -0.5f));
    CE3D2_CHECK_VECTORS_EQUAL(
        uut.vectors()[31],
        CE3D2::create_vector(-0.5f, -0.5f, -0.5f, -0.5f, -0.5f));

    BOOST_CHECK_EQUAL(uut.connections().size(), 80);
    CHECK_HYPERCUBE_CONNECTIONS(uut.connections());
}

BOOST_AUTO_TEST_SUITE_END()
