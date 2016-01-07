#define BOOST_TEST_MODULE TextRendererTest
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "CE3D2/render/TextRenderer.h"


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

BOOST_AUTO_TEST_SUITE_END()
