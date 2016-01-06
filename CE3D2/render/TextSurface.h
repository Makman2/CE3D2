#ifndef CE3D2_RENDER_TEXTSURFACE_H
#define CE3D2_RENDER_TEXTSURFACE_H

#include <vector>


namespace CE3D2
{
namespace Render
{
    /// A TextSurface represent a two-dimensional surface of char-elements.
    ///
    /// Important: Due to performance reasons non-const accessors like
    /// `operator ()` do not perform boundary checks!  You can do that manually
    /// by using the `is_boundary_valid` functions.
    class TextSurface
    {
        using surface_type = std::vector<char>;

    public:
        using size_type = surface_type::size_type;

        /// Instantiates a new TextSurface.
        ///
        /// The surface gets cleared during instantation with spaces.
        ///
        /// @param width  The width of the surface.
        /// @param height The height of the surface.
        TextSurface(size_type width, size_type height);

        virtual ~TextSurface();

        /// Gets the width of this surface.
        ///
        /// @returns The width in pixels.
        size_type
        width() const;

        /// Gets the height of this surface.
        ///
        /// @returns The height in pixels.
        size_type
        height() const;

        /// Accesses a surface pixel (read-only).
        ///
        /// @param x The x-coordinate.
        /// @param y The y-coordinate.
        char
        operator ()(size_type x, size_type y) const;

        /// Accesses a surface pixel.
        ///
        /// @param x The x-coordinate.
        /// @param y The y-coordinate.
        char&
        operator ()(size_type x, size_type y);

        /// Clears the surface with spaces.
        void
        clear();

        /// Fills the complete surface with the given char.
        ///
        /// @param chr The char to fill with.
        void
        fill(char chr);

        /// Fills a block of this surface with the given char.
        ///
        /// @param chr    The char to fill with.
        /// @param x      The x-coordinate where to start filling from.
        /// @param y      The y-coordinate where to start filling from.
        /// @param width  The width of the block to fill.
        /// @param height The height of the block to fill.
        void
        fill(char chr,
             size_type x,
             size_type y,
             size_type width,
             size_type height);

        /// Checks whether the given boundary is valid.
        ///
        /// You can invoke this function before using the `operator ()` on this
        /// object to check for boundary validity.
        ///
        /// @param x The x-coordinate to check.
        /// @param y The y-coordinate to check.
        /// @returns `true` if boundary is valid, `false` if not.
        bool
        is_boundary_valid(size_type x, size_type y) const;

        /// Checks whether the given block-boundary is valid.
        ///
        /// You can invoke this function before using e.g. `fill()` on this
        /// object to check for boundary validity.
        ///
        /// @param x      The x-coordinate of the block to check.
        /// @param y      The y-coordinate of the block to check.
        /// @param width  The width of the block to check.
        /// @param height The height of the block to check.
        /// @returns      `true` if boundary is valid, `false` if not.
        bool
        is_boundary_valid(size_type x,
                          size_type y,
                          size_type width,
                          size_type height) const;

    private:
        size_type m_Width;
        size_type m_Height;
        surface_type m_Surface;
    };
}
}

#endif
