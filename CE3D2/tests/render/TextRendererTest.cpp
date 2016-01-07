#define BOOST_TEST_MODULE TextRendererTest
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "CE3D2/render/TextRenderer.h"
#include "CE3D2/tests/TestUtilities.h"


BOOST_AUTO_TEST_SUITE(TextRendererTestSuite)

BOOST_AUTO_TEST_CASE(test_target)
{
    CE3D2::Render::TextRenderer uut;
    std::shared_ptr<CE3D2::Render::TextSurface> surf(
        new CE3D2::Render::TextSurface(10, 10));

    BOOST_CHECK_EQUAL(uut.get_target().get(),
                      (CE3D2::Render::TextSurface*)nullptr);

    uut.set_target(surf);

    BOOST_CHECK_EQUAL(uut.get_target(), surf);

    (*surf)(3, 8) = 'T';

    BOOST_CHECK_EQUAL((*uut.get_target())(3, 8), 'T');

    // Test modifiability.
    (*uut.get_target())(7, 7) = 'W';
    BOOST_CHECK_EQUAL((*surf)(7, 7), 'W');
}

BOOST_AUTO_TEST_CASE(test_models)
{
    CE3D2::Render::TextRenderer uut;
    std::shared_ptr<CE3D2::Models::Model> model(
        new CE3D2::Models::Model("myModel"));

    BOOST_CHECK(uut.models().empty());

    uut.models().push_back(model);

    BOOST_CHECK_EQUAL(uut.models().size(), 1);
    BOOST_CHECK_EQUAL(uut.models()[0]->get_name(), "myModel");

    model->set_name("new_name");

    BOOST_CHECK_EQUAL(uut.models()[0]->get_name(), "new_name");
}

BOOST_AUTO_TEST_CASE(test_render_without_target)
{
    CE3D2::Render::TextRenderer uut;
    BOOST_CHECK_THROW(uut.render(), std::logic_error)
}

BOOST_AUTO_TEST_CASE(test_render)
{
    auto surface = std::make_shared<CE3D2::Render::TextSurface>(10, 5);

    auto model1 = std::make_shared<CE3D2::Models::Model>();
    model1->vectors().push_back(CE3D2_CREATE_VECTOR(1.0f, 1.0f));
    model1->vectors().push_back(CE3D2_CREATE_VECTOR(4.0f, 5.0f));
    model1->vectors().push_back(CE3D2_CREATE_VECTOR(22.0f, 3.0f));
    model1->vectors().push_back(CE3D2_CREATE_VECTOR(5.7f, 0.1f));
    model1->vectors().push_back(CE3D2_CREATE_VECTOR(-2.0f, 3.3f));
    model1->vectors().push_back(CE3D2_CREATE_VECTOR(0.0f, 4.99f));

    CE3D2::Render::TextRenderer uut;
    uut.set_target(surface);
    uut.models().push_back(model1);

    uut.render();

    auto expected_surface = CE3D2_CREATE_TEXTSURFACE("     .    ",
                                                     " .        ",
                                                     "          ",
                                                     "          ",
                                                     ".         ");
    CE3D2_CHECK_TEXTSURFACES_EQUAL(*surface, *expected_surface);

    auto model2 = std::make_shared<CE3D2::Models::Model>("named model");
    model2->vectors().push_back(CE3D2_CREATE_VECTOR(9.4f, 4.0f));
    model2->vectors().push_back(CE3D2_CREATE_VECTOR(9.2f, 3.0f));
    model2->vectors().push_back(CE3D2_CREATE_VECTOR(9.0f, 2.0f));
    model2->vectors().push_back(CE3D2_CREATE_VECTOR(8.999f, 1.0f));

    uut.models().push_back(model2);
    surface->clear();
    uut.render();

    expected_surface = CE3D2_CREATE_TEXTSURFACE("     .    ",
                                                " .      . ",
                                                "         .",
                                                "         .",
                                                ".        .");
    CE3D2_CHECK_TEXTSURFACES_EQUAL(*surface, *expected_surface);

    model1->set_visibility(false);
    uut.render();

    // The result should be like before, we need to clear the target surface
    // manually!
    CE3D2_CHECK_TEXTSURFACES_EQUAL(*surface, *expected_surface);

    surface->clear();
    uut.render();

    expected_surface = CE3D2_CREATE_TEXTSURFACE("          ",
                                                "        . ",
                                                "         .",
                                                "         .",
                                                "         .");
    CE3D2_CHECK_TEXTSURFACES_EQUAL(*surface, *expected_surface);

    model2->set_visibility(false);
    surface->clear();
    uut.render();

    expected_surface = CE3D2_CREATE_TEXTSURFACE("          ",
                                                "          ",
                                                "          ",
                                                "          ",
                                                "          ");
    CE3D2_CHECK_TEXTSURFACES_EQUAL(*surface, *expected_surface);
}

BOOST_AUTO_TEST_SUITE_END()
