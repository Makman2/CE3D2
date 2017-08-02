#include <chrono>
#include <thread>
#include <iostream>
#include <memory>

#include <CE3D2/models/LineModel.h>
#include <CE3D2/render/TextRenderer.h>
#include <CE3D2/render/TextSurface.h>
#include <CE3D2/transformation/OrthogonalProjection.h>
#include <CE3D2/transformation/Rotation.h>
#include <CE3D2/transformation/Scale.h>
#include <CE3D2/transformation/Translation.h>
#include <CE3D2/Vector.h>

using namespace CE3D2;


int main()
{
    auto model = std::make_shared<Models::LineModel>(Models::LineModel::cube());

    model->transform(Transformation::Scale(create_vector(10.0f, 10.0f, 10.0f)));

    Transformation::OrthogonalProjection ortho_projection;
    std::vector<Vector> projection_vecs;
    projection_vecs.push_back(create_vector(0.7f, 0.3f, 0.0f));
    projection_vecs.push_back(create_vector(0.0f, 0.3f, 0.7f));
    ortho_projection.set_projection_vectors(projection_vecs);

    Transformation::Rotation rotation(create_vector(1.0f, 0.0f, 0.0f),
                                      create_vector(0.0f, 1.0f, 0.0f));

    auto translation = Transformation::Translation(create_vector(10.0f, 10.0f));

    Render::TextRenderer renderer;
    renderer.set_target(std::make_shared<Render::TextSurface>(50, 30));

    // Used to compensate the fact that chars in terminals are twice as high
    // than broad.
    auto screenscale = Transformation::Scale(create_vector(2.0f, 1.0f));

    for (unsigned int i = 0; i < 200; i++)
    {
        renderer.line_models().clear();
        auto modelcopy = std::make_shared<Models::LineModel>(*model);
        renderer.line_models().push_back(modelcopy);

        renderer.get_target()->clear();

        rotation.set_angle(rotation.get_angle() + 0.04f);

        modelcopy->transform(rotation);
        modelcopy->transform(ortho_projection);
        modelcopy->transform(translation);
        modelcopy->transform(screenscale);

        renderer.render();
        std::cout << *renderer.get_target();

        std::this_thread::sleep_for(std::chrono::milliseconds(40)); // 25 FPS
    }

    return 0;
}
