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
        return m_Surface[x + y * m_Width];
    }

    char&
    TextSurface::operator ()(size_type x, size_type y)
    {
        return m_Surface[x + y * m_Width];
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
        auto it = m_Surface.begin() + x + y * m_Width;
        auto stop = it + height * m_Width;

        while (it != stop)
        {
            std::fill_n(it, width, chr);
            it += m_Width;
        }
    }

    void
    TextSurface::copy_from(TextSurface const& source)
    {
        copy_from(source, 0, 0);
    }

    void
    TextSurface::copy_from(TextSurface const& source,
                           size_type target_x,
                           size_type target_y)
    {
        copy_from(source,
                  0,
                  0,
                  target_x,
                  target_y,
                  source.width(),
                  source.height());
    }

    void
    TextSurface::copy_from(TextSurface const& source,
                           size_type source_x,
                           size_type source_y,
                           size_type target_x,
                           size_type target_y,
                           size_type width,
                           size_type height)
    {
        auto target_it = m_Surface.begin() + target_x + target_y * m_Width;
        auto stop = target_it + height * m_Width;
        auto source_it =
            source.m_Surface.begin() + source_x + source_y * source.m_Width;

        while (target_it != stop)
        {
            std::copy_n(source_it, width, target_it);
            target_it += m_Width;
            source_it += source.m_Width;
        }
    }

    bool
    TextSurface::is_boundary_valid(size_type x, size_type y) const
    {
        return x < m_Width && y < m_Height;
    }

    bool
    TextSurface::is_boundary_valid(size_type x,
                                   size_type y,
                                   size_type width,
                                   size_type height) const
    {
        return x + width <= m_Width && y + height <= m_Height;
    }
}
}
