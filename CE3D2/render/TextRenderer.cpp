#include "CE3D2/render/TextRenderer.h"


namespace CE3D2
{
namespace Render
{
    TextRenderer::TextRenderer()
    : m_Target(nullptr)
    , m_Models()
    {}

    TextRenderer::~TextRenderer()
    {}

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
}
}
