#define BOOST_TEST_MODULE AllTest
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "CE3D2/models/loaders/All.h"
#include "TestUtilities.h"

#include <boost/filesystem.hpp>


std::string
get_testfile_path(std::string testfile)
{
    boost::filesystem::path current_file_path(__FILE__);
    boost::filesystem::path test_directory = current_file_path.stem();
    test_directory += "Files";
    boost::filesystem::path testfile_path(testfile);
    return (test_directory / testfile_path).string();
}


BOOST_AUTO_TEST_SUITE(AllTestSuite)

    BOOST_AUTO_TEST_CASE(test_obj_extension)
    {
        std::string path = get_testfile_path("simple_model.obj");
        auto models = CE3D2::Models::Loaders::load(path);

        BOOST_CHECK_EQUAL(models.size(), 1);

        auto const& model = *models[0];
        auto expected = CE3D2::Models::LineModel("a_cube");
        expected.vectors().push_back(CE3D2::create_vector(1.0f, 1.0f, -1.0f));
        expected.vectors().push_back(CE3D2::create_vector(2.0f, -2.0f, 0.5f));
        expected.vectors().push_back(CE3D2::create_vector(4.0f, 10.0f, -3.0f));

        CE3D2_CHECK_MODELS_EQUAL(model, expected);
    }

    BOOST_AUTO_TEST_CASE(test_invalid_extension)
    {
        std::string path = get_testfile_path("non_existing_file.txt");
        CE3D2_CHECK_EXCEPTION(CE3D2::Models::Loaders::load(path),
                              std::invalid_argument,
                              "Unrecognized file extension: .txt");
    }

BOOST_AUTO_TEST_SUITE_END()
