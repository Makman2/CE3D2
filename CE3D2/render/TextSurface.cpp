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

    void
    TextSurface::clear()
    {
        fill(' ');
    }

    void
    TextSurface::fill(char chr)
    {
        m_Surface.assign(m_Surface.size(), chr);
    }

    void
    TextSurface::fill(char chr,
                      size_type x,
                      size_type y,
                      size_type width,
                      size_type height)
    {
        auto it = m_Surface.begin() + x * m_Width + y;
        auto stop = it + height * m_Width;

        while (it != stop)
        {
            std::fill_n(it, width, chr);
            it += m_Width;
        }
    }

    bool
    TextSurface::is_boundary_valid(size_type x, size_type y) const
    {
        return x < m_Height && y < m_Width;
    }

    bool
    TextSurface::is_boundary_valid(size_type x,
                                   size_type y,
                                   size_type width,
                                   size_type height) const
    {
        return x + height <= m_Height && y + width <= m_Width;
    }
}
}
