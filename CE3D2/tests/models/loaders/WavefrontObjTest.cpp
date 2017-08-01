#define BOOST_TEST_MODULE WavefrontObjTest
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "CE3D2/tests/TestUtilities.h"
#include "CE3D2/models/loaders/FileFormatException.h"
#include "CE3D2/models/loaders/InvalidFileException.h"
#include "CE3D2/models/loaders/WavefrontObj.h"

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


BOOST_AUTO_TEST_SUITE(WavefrontObjTestSuite)

    BOOST_AUTO_TEST_CASE(test_invalid_file)
    {
        std::string path = get_testfile_path(
            "xxx_invalid_nonexisting_file_xxx.obj");
        CE3D2_CHECK_EXCEPTION(
            CE3D2::Models::Loaders::load_wavefront_obj(path),
            CE3D2::Models::Loaders::InvalidFileException,
            "Can't open file: "
                "WavefrontObjTestFiles/xxx_invalid_nonexisting_file_xxx.obj");
    }

    BOOST_AUTO_TEST_CASE(test_simple)
    {
        std::string path = get_testfile_path("simple.obj");
        auto models = CE3D2::Models::Loaders::load_wavefront_obj(path);

        BOOST_CHECK_EQUAL(models.size(), 1);

        auto const& model = *models[0];
        auto expected = CE3D2::Models::LineModel("a_cube");
        expected.vectors().push_back(CE3D2::create_vector(1.0f, 1.0f, -1.0f));
        expected.vectors().push_back(CE3D2::create_vector(2.0f, -2.0f, 0.5f));
        expected.vectors().push_back(CE3D2::create_vector(4.0f, 10.0f, -3.0f));

        CE3D2_CHECK_MODELS_EQUAL(model, expected);
    }

    BOOST_AUTO_TEST_CASE(test_simple_variable_vector_sizes)
    {
        std::string path = get_testfile_path(
            "simple_variable_vector_sizes.obj");
        auto models = CE3D2::Models::Loaders::load_wavefront_obj(path);

        BOOST_CHECK_EQUAL(models.size(), 1);

        auto const& model = *models[0];
        auto expected = CE3D2::Models::LineModel("a_cube");
        expected.vectors().push_back(
            CE3D2::create_vector(1.0f));
        expected.vectors().push_back(
            CE3D2::create_vector(2.0f, 3.0f));
        expected.vectors().push_back(
            CE3D2::create_vector(4.0f, 5.0f, 6.0f));
        expected.vectors().push_back(
            CE3D2::create_vector(7.0f, 8.0f, 9.0f, 10.0f));
        expected.vectors().push_back(
            CE3D2::create_vector(11.0f, 12.0f, 13.0f, 14.0f, 15.0f));

        CE3D2_CHECK_MODELS_EQUAL(model, expected);
    }

    BOOST_AUTO_TEST_CASE(test_simple_multiple_models)
    {
        std::string path = get_testfile_path("simple_multiple_models.obj");
        auto models = CE3D2::Models::Loaders::load_wavefront_obj(path);

        BOOST_CHECK_EQUAL(models.size(), 3);

        auto const& model1 = *models[0];
        auto expected1 = CE3D2::Models::LineModel("cube1");
        expected1.vectors().push_back(CE3D2::create_vector(1.0f, 1.0f, 1.0f));
        CE3D2_CHECK_MODELS_EQUAL(model1, expected1);

        auto const& model2 = *models[1];
        auto expected2 = CE3D2::Models::LineModel("cube2");
        expected2.vectors().push_back(CE3D2::create_vector(2.0f, 2.0f, 2.0f));
        expected2.vectors().push_back(CE3D2::create_vector(3.0f, 3.0f, 3.0f));
        CE3D2_CHECK_MODELS_EQUAL(model2, expected2);

        auto const& model3 = *models[2];
        auto expected3 = CE3D2::Models::LineModel("cube3");
        expected3.vectors().push_back(CE3D2::create_vector(4.0f, 4.0f, 4.0f));
        CE3D2_CHECK_MODELS_EQUAL(model3, expected3);
    }

    BOOST_AUTO_TEST_CASE(test_geometry_definition_without_declaring_object_v)
    {
        std::string path = get_testfile_path(
            "geometry_definition_without_declaring_object.obj");
        auto models = CE3D2::Models::Loaders::load_wavefront_obj(path);

        BOOST_CHECK_EQUAL(models.size(), 1);

        auto const& model = *models[0];
        auto expected = CE3D2::Models::LineModel();
        expected.vectors().push_back(CE3D2::create_vector(1.0f, 2.0f, 3.0f));
        expected.vectors().push_back(CE3D2::create_vector(4.0f, 5.0f, 6.0f));

        CE3D2_CHECK_MODELS_EQUAL(model, expected);
    }

    BOOST_AUTO_TEST_CASE(test_empty_lines)
    {
        std::string path = get_testfile_path("empty_lines_and_comments.obj");
        auto models = CE3D2::Models::Loaders::load_wavefront_obj(path);

        BOOST_CHECK_EQUAL(models.size(), 1);

        auto const& model = *models[0];
        auto expected = CE3D2::Models::LineModel("a_cube");
        expected.vectors().push_back(CE3D2::create_vector(1.0f, 1.0f, -1.0f));
        expected.vectors().push_back(CE3D2::create_vector(4.0f, 4.0f, 4.0f));
        expected.vectors().push_back(CE3D2::create_vector(5.0f, 5.0f, 5.0f));

        CE3D2_CHECK_MODELS_EQUAL(model, expected);
    }

    BOOST_AUTO_TEST_CASE(test_ignored_specifiers)
    {
        std::string path = get_testfile_path("ignored_specifiers.obj");
        auto models = CE3D2::Models::Loaders::load_wavefront_obj(path);

        BOOST_CHECK_EQUAL(models.size(), 1);

        auto const& model = *models[0];
        auto expected = CE3D2::Models::LineModel("Cube");
        expected.vectors().push_back(CE3D2::create_vector(1.0f, -1.0f, -1.0f));

        CE3D2_CHECK_MODELS_EQUAL(model, expected);
    }

    BOOST_AUTO_TEST_CASE(test_specifier_with_spaces_ahead)
    {
        std::string path = get_testfile_path(
            "specifier_with_spaces_ahead.obj");
        auto models = CE3D2::Models::Loaders::load_wavefront_obj(path);

        BOOST_CHECK_EQUAL(models.size(), 1);

        auto const& model = *models[0];
        auto expected = CE3D2::Models::LineModel("some_model");
        expected.vectors().push_back(CE3D2::create_vector(1.0f, 0.0f));
        expected.vectors().push_back(CE3D2::create_vector(0.0f, 1.0f));

        CE3D2_CHECK_MODELS_EQUAL(model, expected);
    }

    BOOST_AUTO_TEST_CASE(test_trailing_whitespaces)
    {
        std::string path = get_testfile_path("trailing_whitespaces.obj");
        auto models = CE3D2::Models::Loaders::load_wavefront_obj(path);

        BOOST_CHECK_EQUAL(models.size(), 1);

        auto const& model = *models[0];
        auto expected =
            CE3D2::Models::LineModel("geometry_with_whitespaces_after_v");
        expected.vectors().push_back(CE3D2::create_vector(1.0f, 1.0f, -1.0f));
        expected.vectors().push_back(CE3D2::create_vector(1.0f, -1.0f, 1.0f));
        expected.vectors().push_back(CE3D2::create_vector(-1.0f, 1.0f, 1.0f));
        expected.connections().emplace_back(0, 1);
        expected.connections().emplace_back(1, 2);
        expected.connections().emplace_back(2, 0);

        CE3D2_CHECK_MODELS_EQUAL(model, expected);
    }

    BOOST_AUTO_TEST_CASE(test_invalid_specifier)
    {
        std::string path = get_testfile_path("invalid_specifier.obj");
        CE3D2_CHECK_EXCEPTION(CE3D2::Models::Loaders::load_wavefront_obj(path),
                              CE3D2::Models::Loaders::FileFormatException,
                              "Unknown specifier at line 3: not-a-specifier");
    }

    BOOST_AUTO_TEST_CASE(test_invalid_vector_value)
    {
        std::string path = get_testfile_path("invalid_vector_value.obj");
        CE3D2_CHECK_EXCEPTION(CE3D2::Models::Loaders::load_wavefront_obj(path),
                              CE3D2::Models::Loaders::FileFormatException,
                              "Illegal floating point value at line 2: 3.x");
    }

    BOOST_AUTO_TEST_CASE(test_vector_value_out_of_bounds)
    {
        std::string path = get_testfile_path("vector_value_out_of_bounds.obj");
        CE3D2_CHECK_EXCEPTION(
            CE3D2::Models::Loaders::load_wavefront_obj(path),
            CE3D2::Models::Loaders::FileFormatException,
            "Floating point value at line 2 out of bounds: "
                "1423823048320948203489704270895735896230573475892374897089237"
                "49582730945702938470592875092387532948288459582438923489");
    }

    BOOST_AUTO_TEST_CASE(test_simple_faces)
    {
        std::string path = get_testfile_path("simple_faces.obj");
        auto models = CE3D2::Models::Loaders::load_wavefront_obj(path);

        BOOST_CHECK_EQUAL(models.size(), 1);

        auto const& model = *models[0];
        auto expected = CE3D2::Models::LineModel("a_cube");
        expected.vectors().push_back(CE3D2::create_vector(1.0f, 2.0f));
        expected.vectors().push_back(CE3D2::create_vector(3.0f, 4.0f));
        expected.vectors().push_back(CE3D2::create_vector(5.0f, 6.0f));
        expected.vectors().push_back(CE3D2::create_vector(7.0f, 8.0f));
        expected.vectors().push_back(CE3D2::create_vector(9.0f, 10.0f));
        expected.vectors().push_back(CE3D2::create_vector(11.0f, 12.0f));
        expected.vectors().push_back(CE3D2::create_vector(13.0f, 14.0f));
        expected.vectors().push_back(CE3D2::create_vector(15.0f, 16.0f));
        expected.vectors().push_back(CE3D2::create_vector(17.0f, 18.0f));
        expected.vectors().push_back(CE3D2::create_vector(19.0f, 20.0f));
        expected.vectors().push_back(CE3D2::create_vector(21.0f, 22.0f));
        expected.vectors().push_back(CE3D2::create_vector(23.0f, 24.0f));
        expected.vectors().push_back(CE3D2::create_vector(25.0f, 26.0f));
        expected.connections().emplace_back(0, 1);
        expected.connections().emplace_back(1, 2);
        expected.connections().emplace_back(2, 0);
        expected.connections().emplace_back(3, 4);
        expected.connections().emplace_back(4, 5);
        expected.connections().emplace_back(5, 3);
        expected.connections().emplace_back(6, 7);
        expected.connections().emplace_back(7, 8);
        expected.connections().emplace_back(8, 9);
        expected.connections().emplace_back(9, 6);
        expected.connections().emplace_back(10, 11);
        expected.connections().emplace_back(11, 12);
        expected.connections().emplace_back(12, 10);

        CE3D2_CHECK_MODELS_EQUAL(model, expected);
    }

    BOOST_AUTO_TEST_CASE(test_negative_face_indexes)
    {
        std::string path = get_testfile_path("negative_face_indexes.obj");
        auto models = CE3D2::Models::Loaders::load_wavefront_obj(path);

        BOOST_CHECK_EQUAL(models.size(), 1);

        auto const& model = *models[0];
        auto expected = CE3D2::Models::LineModel("a_cube");
        expected.vectors().push_back(CE3D2::create_vector(1.0f, 2.0f));
        expected.vectors().push_back(CE3D2::create_vector(3.0f, 4.0f));
        expected.vectors().push_back(CE3D2::create_vector(5.0f, 6.0f));
        expected.vectors().push_back(CE3D2::create_vector(7.0f, 8.0f));
        expected.connections().emplace_back(3, 2);
        expected.connections().emplace_back(2, 0);
        expected.connections().emplace_back(0, 1);
        expected.connections().emplace_back(1, 3);

        CE3D2_CHECK_MODELS_EQUAL(model, expected);
    }

    BOOST_AUTO_TEST_CASE(test_invalid_face_index)
    {
        std::string path = get_testfile_path("invalid_face_index.obj");
        CE3D2_CHECK_EXCEPTION(
            CE3D2::Models::Loaders::load_wavefront_obj(path),
            CE3D2::Models::Loaders::FileFormatException,
            "Illegal integer value at line 1: this-is-not-a-face-index");
    }

    BOOST_AUTO_TEST_CASE(test_invalid_face_syntax)
    {
        std::string path = get_testfile_path("invalid_face_syntax.obj");
        CE3D2_CHECK_EXCEPTION(
            CE3D2::Models::Loaders::load_wavefront_obj(path),
            CE3D2::Models::Loaders::FileFormatException,
            "Invalid face syntax at line 1, too many '/': 1/2/3/4");
    }

    BOOST_AUTO_TEST_CASE(test_invalid_face_syntax_with_empty_elements)
    {
        std::string path = get_testfile_path(
            "invalid_face_syntax_with_empty_elements.obj");
        CE3D2_CHECK_EXCEPTION(
            CE3D2::Models::Loaders::load_wavefront_obj(path),
            CE3D2::Models::Loaders::FileFormatException,
            "Invalid face syntax at line 1, too many '/': 1///4");
    }

    BOOST_AUTO_TEST_CASE(test_face_index_value_out_of_bounds)
    {
        std::string path = get_testfile_path(
            "face_index_value_out_of_bounds.obj");
        CE3D2_CHECK_EXCEPTION(
            CE3D2::Models::Loaders::load_wavefront_obj(path),
            CE3D2::Models::Loaders::FileFormatException,
            "Integer value at line 7 out of bounds: "
                "234723498327049872390472309487230947823094872309487234");
    }

    BOOST_AUTO_TEST_CASE(test_face_index_out_of_bounds_positive_index)
    {
        std::string path = get_testfile_path(
            "face_index_out_of_bounds_positive_index.obj");
        CE3D2_CHECK_EXCEPTION(
            CE3D2::Models::Loaders::load_wavefront_obj(path),
            CE3D2::Models::Loaders::FileFormatException,
            "Index 5 out of bounds at line 8, only 4 vector(s) loaded so far "
                "for model.");
    }

    BOOST_AUTO_TEST_CASE(test_face_index_out_of_bounds_negative_index)
    {
        std::string path = get_testfile_path(
            "face_index_out_of_bounds_negative_index.obj");
        CE3D2_CHECK_EXCEPTION(
            CE3D2::Models::Loaders::load_wavefront_obj(path),
            CE3D2::Models::Loaders::FileFormatException,
            "Index -3 out of bounds at line 6, only 2 vector(s) loaded so far "
                "for model.");
    }

    BOOST_AUTO_TEST_CASE(test_face_index_out_of_bounds_no_vertices)
    {
        std::string path = get_testfile_path(
            "face_index_out_of_bounds_no_vertices.obj");
        CE3D2_CHECK_EXCEPTION(
            CE3D2::Models::Loaders::load_wavefront_obj(path),
            CE3D2::Models::Loaders::FileFormatException,
            "Index 1 out of bounds at line 3, only 0 vector(s) loaded so far "
                "for model.");
    }

    BOOST_AUTO_TEST_CASE(test_blender_exported_file)
    {
        std::string path = get_testfile_path("blender_file.obj");
        auto models = CE3D2::Models::Loaders::load_wavefront_obj(path);

        BOOST_CHECK_EQUAL(models.size(), 1);

        auto const& model = *models[0];
        auto expected = CE3D2::Models::LineModel("Cube");
        expected.vectors().push_back(
            CE3D2::create_vector(1.0f, -1.0f, -1.0f));
        expected.vectors().push_back(
            CE3D2::create_vector(1.0f, -1.0f, 1.0f));
        expected.vectors().push_back(
            CE3D2::create_vector(-1.0f, -1.0f, 1.0f));
        expected.vectors().push_back(
            CE3D2::create_vector(-1.0f, -1.0f, -1.0f));
        expected.vectors().push_back(
            CE3D2::create_vector(1.0f, 1.0f, -0.999999f));
        expected.vectors().push_back(
            CE3D2::create_vector(0.999999f, 1.0f, 1.000001f));
        expected.vectors().push_back(
            CE3D2::create_vector(-1.0f, 1.0f, 1.0f));
        expected.vectors().push_back(
            CE3D2::create_vector(-1.0f, 1.0f, -1.0f));
        expected.connections().emplace_back(1, 2);
        expected.connections().emplace_back(2, 3);
        expected.connections().emplace_back(3, 1);
        expected.connections().emplace_back(7, 6);
        expected.connections().emplace_back(6, 5);
        expected.connections().emplace_back(5, 7);
        expected.connections().emplace_back(0, 4);
        expected.connections().emplace_back(4, 5);
        expected.connections().emplace_back(5, 0);
        expected.connections().emplace_back(1, 5);
        expected.connections().emplace_back(5, 6);
        expected.connections().emplace_back(6, 1);
        expected.connections().emplace_back(6, 7);
        expected.connections().emplace_back(7, 3);
        expected.connections().emplace_back(3, 6);
        expected.connections().emplace_back(0, 3);
        expected.connections().emplace_back(3, 7);
        expected.connections().emplace_back(7, 0);
        expected.connections().emplace_back(0, 1);
        expected.connections().emplace_back(1, 3);
        expected.connections().emplace_back(3, 0);
        expected.connections().emplace_back(4, 7);
        expected.connections().emplace_back(7, 5);
        expected.connections().emplace_back(5, 4);
        expected.connections().emplace_back(1, 0);
        expected.connections().emplace_back(0, 5);
        expected.connections().emplace_back(5, 1);
        expected.connections().emplace_back(2, 1);
        expected.connections().emplace_back(1, 6);
        expected.connections().emplace_back(6, 2);
        expected.connections().emplace_back(2, 6);
        expected.connections().emplace_back(6, 3);
        expected.connections().emplace_back(3, 2);
        expected.connections().emplace_back(4, 0);
        expected.connections().emplace_back(0, 7);
        expected.connections().emplace_back(7, 4);

        CE3D2_CHECK_MODELS_EQUAL(model, expected);
    }

BOOST_AUTO_TEST_SUITE_END()
