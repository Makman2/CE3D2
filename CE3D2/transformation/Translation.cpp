#include "CE3D2/transformation/Translation.h"


namespace CE3D2
{
namespace Transformation
{
    Translation::Translation(CE3D2::Vector const& translation)
    : m_Translation(translation)
    {}

    Translation::~Translation()
    {}

    CE3D2::Vector&
    Translation::get_translation()
    {
        return m_Translation;
    }

    CE3D2::Vector const&
    Translation::get_translation() const
    {
        return m_Translation;
    }

    void
    Translation::set_translation(CE3D2::Vector const& value)
    {
        m_Translation = value;
    }

    void
    Translation::transform_vector(CE3D2::Vector& vector) const
    {
        vector += m_Translation;
    }
}
}
