#ifndef CE3D2_RENDER_TEXTRENDERER_H
#define CE3D2_RENDER_TEXTRENDERER_H

#include "CE3D2/models/LineModel.h"
#include "CE3D2/models/Model.h"
#include "CE3D2/render/TextSurface.h"


namespace CE3D2
{
namespace Render
{
    /// Renders models onto a `TextSurface`.
    ///
    /// This class is responsible for actually drawing 3D graphics as ASCII
    /// text.
    class TextRenderer
    {
    public:
        /// Instantiates a new `TextRenderer`.
        ///
        /// By default `TextRenderer` uses a dot to render points.
        ///
        /// Contains no target and no models at instantation.
        TextRenderer();

        virtual ~TextRenderer();

        /// Returns the char used for rendering points.
        ///
        /// @returns
        ///     The render-char.
        char
        get_rendered_char() const;

        /// Sets the char used for rendering points.
        ///
        /// @param value
        ///     The new char.
        void
        set_rendered_char(char value);

        /// Returns a shared reference to the render target.
        ///
        /// @returns
        ///     A shared reference.
        std::shared_ptr<TextSurface>
        get_target() const;

        /// Sets the render target where the models are rendered to.
        ///
        /// @param target
        ///     A shared reference of a `TextSurface` to use as target.
        void
        set_target(std::shared_ptr<TextSurface> const& target);

        /// Returns a reference to the model list.
        ///
        /// Each model inside this list will be rendered with the render-char at
        /// the specified vectors in it.
        ///
        /// @returns
        ///     A reference to the model list.
        std::vector<std::shared_ptr<CE3D2::Models::Model>>&
        models();

        /// Returns a read-only reference to the model list.
        ///
        /// Each model inside this list will be rendered with the render-char at
        /// the specified vectors in it.
        ///
        /// @returns
        ///     A read-only reference to the model list.
        std::vector<std::shared_ptr<CE3D2::Models::Model>> const&
        models() const;

        /// Returns a reference to the line-model list.
        ///
        /// Each model inside this list will be rendered using the chars `_`,
        /// `\\`, `|` and `/` connecting the specified index pairs.
        ///
        /// Line-models have higher priority than normal models, means the line
        /// connection characters override the dot-characters on the provided
        /// `TextSurface` target!
        ///
        /// @returns
        ///     A reference to the line-model list.
        std::vector<std::shared_ptr<CE3D2::Models::LineModel>>&
        line_models();

        /// Returns a read-only reference to the line-model list.
        ///
        /// Each model inside this list will be rendered using the chars `_`,
        /// `\\`, `|` and `/` connecting the specified index pairs.
        ///
        /// Line-models have higher priority than normal models, means the line
        /// connection characters override the dot-characters on the provided
        /// `TextSurface` target!
        ///
        /// @returns
        ///     A read-only reference to the line-model list.
        std::vector<std::shared_ptr<CE3D2::Models::LineModel>> const&
        line_models() const;

        /// Renders all listed models.
        ///
        /// The target surface is not cleared before rendering, you need to do
        /// it yourself using `TextSurface.clear()`!
        ///
        /// @throws std::logic_error
        ///     Thrown when no target is set.
        void
        render();

    private:
        void render_points();
        void render_lines();

        char m_RenderChar;
        std::shared_ptr<TextSurface> m_Target;
        std::vector<std::shared_ptr<CE3D2::Models::Model>> m_Models;
        std::vector<std::shared_ptr<CE3D2::Models::LineModel>> m_LineModels;
    };
}
}

#endif
