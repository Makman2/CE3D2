#include "CE3D2/render/TextSurface.h"

#include <algorithm>


namespace CE3D2
{
namespace Render
{
    TextSurface::TextSurface(size_type width, size_type height)
    : m_Width(width)
    , m_Height(height)
    , m_Surface(width * height, ' ')
    {
        m_Surface.shrink_to_fit();
    }

    TextSurface::~TextSurface()
    {}

    TextSurface::size_type
    TextSurface::width() const
    {
        return m_Width;
    }

    TextSurface::size_type
    TextSurface::height() const
    {
        return m_Height;
    }

    char
    TextSurface::operator ()(size_type x, size_type y) const
    {
        return m_Surface[x * m_Width + y];
    }

    char&
    TextSurface::operator ()(size_type x, size_type y)
    {
        return m_Surface[x * m_Width + y];
    }
}
}
