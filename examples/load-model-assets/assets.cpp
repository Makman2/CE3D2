#include <iostream>
#include <memory>

#include <CE3D2/models/loaders/All.h>
#include <CE3D2/render/TextRenderer.h>
#include <CE3D2/render/TextSurface.h>
#include <CE3D2/transformation/OrthogonalProjection.h>
#include <CE3D2/transformation/Scale.h>
#include <CE3D2/transformation/Translation.h>
#include <CE3D2/Vector.h>

using namespace CE3D2;


#define print_to_stderr(text) (std::cout << text << std::endl)


class system_exit: public std::exception
{};


struct ApplicationParameters
{
    std::string model_to_display;
};


void print_available_assets()
{
    print_to_stderr("Available assets are:");
    print_to_stderr("- octagon");
    print_to_stderr("- pyramid");
    print_to_stderr("- icosphere");
    print_to_stderr("- torus");
}


int run(ApplicationParameters parameters)
{
    std::string asset_filename;
    float model_scale;
    Vector projection_vector1;
    Vector projection_vector2;

    // Tune display parameters a bit to show the assets in an optimal fashion.
    if (parameters.model_to_display == "octagon")
    {
        asset_filename = "octagon.obj";
        model_scale = 3.0;
        projection_vector1 = create_vector(0.7f, 0.3f, 0.0f);
        projection_vector2 = create_vector(0.0f, 0.3f, 0.7f);
    }
    else if(parameters.model_to_display == "pyramid")
    {
        asset_filename = "pyramid.obj";
        model_scale = 6.5;
        projection_vector1 = create_vector(0.7f, 0.0f, 0.3f);
        projection_vector2 = create_vector(0.3f, -0.7f, -0.7f);
    }
    else if(parameters.model_to_display == "icosphere")
    {
        asset_filename = "icosphere.obj";
        model_scale = 5.0;
        projection_vector1 = create_vector(0.6f, 0.0f, 0.4f);
        projection_vector2 = create_vector(0.4f, -0.2f, -0.6f);
    }
    else if(parameters.model_to_display == "torus")
    {
        asset_filename = "torus.obj";
        model_scale = 12.0;
        projection_vector1 = create_vector(0.7f, 0.3f, 0.0f);
        projection_vector2 = create_vector(0.0f, 0.3f, 0.7f);
    }
    else
    {
        print_to_stderr("Invalid asset specified: " << parameters.model_to_display);
        print_available_assets();

        throw system_exit();
    }


    // OBJ-files can contain multiple models. However, each of the examples
    // contains only a single model.
    auto model = Models::Loaders::load(asset_filename)[0];

    // Set up view and projections.
    Transformation::OrthogonalProjection ortho_projection;
    std::vector<Vector> projection_vecs;
    projection_vecs.push_back(projection_vector1);
    projection_vecs.push_back(projection_vector2);
    ortho_projection.set_projection_vectors(projection_vecs);

    auto translation = Transformation::Translation(create_vector(20.0f, 20.0f));

    // Used to compensate the fact that chars in terminals are twice as high
    // than broad.
    auto screenscale = Transformation::Scale(create_vector(2.0f, 1.0f));

    // Transform model.
    model->transform(Transformation::Scale(ScalarVector(3, model_scale)));
    model->transform(ortho_projection);
    model->transform(translation);
    model->transform(screenscale);

    // Render.
    Render::TextRenderer renderer;
    renderer.set_target(std::make_shared<Render::TextSurface>(80, 40));
    renderer.line_models().push_back(model);
    renderer.render();
    std::cout << *renderer.get_target();

    return 0;
}


ApplicationParameters parse_arguments(int argc, char* argv[])
{
    if (argc == 1)
    {
        print_to_stderr("Please specify an asset you want to render.");
        print_available_assets();

        throw system_exit();
    }
    else if (argc > 2)
    {
        print_to_stderr("Please specify a single asset only.");

        throw system_exit();
    }

    ApplicationParameters parameters;
    parameters.model_to_display = std::string(argv[1]);

    return parameters;
}


int main(int argc, char* argv[])
{
    try
    {
        return run(parse_arguments(argc, argv));
    }
    catch (system_exit const&)
    {
        // Do nothing, system exits signalize to end the program.
        // We do not need to cleanup anything specifically.
    }
}
