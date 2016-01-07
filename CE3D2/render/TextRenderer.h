#ifndef CE3D2_RENDER_TEXTRENDERER_H
#define CE3D2_RENDER_TEXTRENDERER_H

#include "CE3D2/models/Model.h"
#include "CE3D2/render/TextSurface.h"


namespace CE3D2
{
namespace Render
{
    /// Renders models onto a TextSurface.
    ///
    /// This class is responsible for actually drawing 3D graphics as ASCII
    /// text.
    class TextRenderer
    {
    public:
        /// Instantiates a new TextRenderer.
        ///
        /// Contains no target and no models at instantation.
        TextRenderer();

        virtual ~TextRenderer();

        /// Returns a shared reference to the render target.
        ///
        /// @returns A shared reference.
        std::shared_ptr<TextSurface>
        get_target() const;

        /// Sets the render target where the models are rendered to.
        ///
        /// @param target A shared reference of a TextSurface to use as target.
        void
        set_target(std::shared_ptr<TextSurface> const& target);

        /// Returns a reference to the model list.
        ///
        /// Each model inside this list will be rendered.
        ///
        /// @returns A reference to the model list.
        std::vector<std::shared_ptr<CE3D2::Models::Model>>&
        models();

        /// Renders all listed models.
        ///
        /// The target surface is not cleared before rendering, you need to do
        /// it yourself using TextSurface.clear!
        ///
        /// @throws std::logic_error Thrown when no target is set.
        void
        render();

    private:
        std::shared_ptr<TextSurface> m_Target;
        std::vector<std::shared_ptr<CE3D2::Models::Model>> m_Models;
    };
}
}

#endif
