#include "CE3D2/render/TextRenderer.h"


namespace CE3D2
{
namespace Render
{
    TextRenderer::TextRenderer()
    : m_RenderChar('.')
    , m_Target(nullptr)
    , m_Models()
    {}

    TextRenderer::~TextRenderer()
    {}

    char
    TextRenderer::get_rendered_char() const
    {
        return m_RenderChar;
    }

    void
    TextRenderer::set_rendered_char(char value)
    {
        m_RenderChar = value;
    }

    std::shared_ptr<TextSurface>
    TextRenderer::get_target() const
    {
        return m_Target;
    }

    void
    TextRenderer::set_target(std::shared_ptr<TextSurface> const& target)
    {
        m_Target = target;
    }

    std::vector<std::shared_ptr<CE3D2::Models::Model>>&
    TextRenderer::models()
    {
        return m_Models;
    }

    void
    TextRenderer::render()
    {
        if (!m_Target)
        {
            throw std::logic_error("No render target set! Use `set_target` to "
                                   "link a target surface to this renderer.");
        }

        for (auto const& model: m_Models)
        {
            if (model->is_visible())
            {
                for (auto const& vector: model->vectors())
                {
                    TextSurface::size_type x =
                        static_cast<TextSurface::size_type>(vector[0]);
                    TextSurface::size_type y =
                        static_cast<TextSurface::size_type>(vector[1]);

                    if (m_Target->is_boundary_valid(x, y))
                    {
                        (*m_Target)(x, y) = m_RenderChar;
                    }
                }
            }
        }
    }
}
}
