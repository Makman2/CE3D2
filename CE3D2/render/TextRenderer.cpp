#include "CE3D2/render/TextRenderer.h"

#include "CE3D2/math/LinearAffineFunction.h"
#include "CE3D2/math/math.h"


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

    std::vector<std::shared_ptr<CE3D2::Models::Model>> const&
    TextRenderer::models() const
    {
        return m_Models;
    }

    std::vector<std::shared_ptr<CE3D2::Models::LineModel>>&
    TextRenderer::line_models()
    {
        return m_LineModels;
    }

    std::vector<std::shared_ptr<CE3D2::Models::LineModel>> const&
    TextRenderer::line_models() const
    {
        return m_LineModels;
    }

    void
    TextRenderer::render_points()
    {
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

    void
    TextRenderer::render_lines()
    {
        CE3D2::Math::Box const viewbox(
            static_cast<CE3D2::PrecisionType>(get_target()->width()),
            static_cast<CE3D2::PrecisionType>(get_target()->height()));

        for (auto const& model: m_LineModels)
        {
            if (model->is_visible())
            {
                for (auto const& indexpair: model->edges())
                {
                    auto const& v1 = model->vectors()[indexpair.first];
                    auto const& v2 = model->vectors()[indexpair.second];

                    // We need to distinct 4 different cases:
                    // --> |x1 - x2| >= |y1 - y2|
                    //     We iterate over x to leave no holes. This is equal
                    //     to the condition `abs(gradient) <= 1`. If we would
                    //     iterate over y, our function may jump over a
                    //     character-field and we get char-holes.
                    // --> |x1 - x2| < |y1 - y2|
                    //     We iterate over y to leave no holes. Equal to the
                    //     condition `abs(gradient) > 1`.
                    // --> x1 == x2
                    //     Normally this case should be covered from the
                    //     previous one, but due to limitations inside our
                    //     linear-function-object we can't correctly calculate
                    //     the inverse, inside the inverse value calculations
                    //     `infinity / infinity` happens which is `NaN`.
                    // --> x1 == x2 && y1 == y2
                    //     Special case from previous one, where the gradient is
                    //     not infinity but `NaN`. This case can be ignored,
                    //     because it symbolizes a point to render, and since we
                    //     render lines there's no need to handle this one.
                    //     For more efficient handling, this case can be
                    //     integrated into the previous one, the iteration over
                    //     y would directly cancel.

                    if (v1[0] == v2[0])
                    {
                        auto y_sorted = std::minmax(v1[1], v2[1]);
                        auto y_start = static_cast<TextSurface::size_type>(
                            std::max(viewbox.y, y_sorted.first));
                        // Need to max with 0.0f as a negative value here
                        // results in an overflow, as TextSurface::size_type
                        // is unsigned.
                        auto y_end = static_cast<TextSurface::size_type>(
                            std::max(
                                0.0f,
                                std::min(
                                    viewbox.y + viewbox.height,
                                    y_sorted.second)));

                        for (auto y = y_start; y < y_end; y++)
                        {
                            (*m_Target)(v1[0], y) = '|';
                        }

                        continue;
                    }

                    CE3D2::Math::LinearAffineFunction line(
                        v1[0], v1[1], v2[0], v2[1]);

                    // Calculate the boundaries of the line within a box.
                    auto viewbox_intersections =
                        CE3D2::Math::line_intersection_with_box(line, viewbox);

                    if (viewbox_intersections.size() != 2)
                    {
                        // If we have less than two intersection, this means
                        // we only touch the viewbox or don't hit it at all.
                        // More than two should not occur, but it can happen
                        // due to numerical limitations.
                        continue;
                    }

                    if (fabs(line.get_gradient()) > 1.0f)
                    {
                        // Line has more height than width.

                        auto y_viewbox_bounds = std::minmax(
                            viewbox_intersections[0].second,
                            viewbox_intersections[1].second);

                        auto y_line_bounds = std::minmax(v1[1], v2[1]);

                        // The first element contains the upper bound, and the
                        // second element the lower bound.
                        auto y_bounds_start =
                            static_cast<TextSurface::size_type>(std::max(
                                std::round(y_line_bounds.first),
                                y_viewbox_bounds.first));
                        // Need to max with 0.0f as a negative value here
                        // results in an overflow, as TextSurface::size_type
                        // is unsigned.
                        auto y_bounds_end =
                            static_cast<TextSurface::size_type>(std::max(
                                0.0f,
                                std::min(
                                    std::round(y_line_bounds.second),
                                    y_viewbox_bounds.second)));

                        auto x_prev = static_cast<TextSurface::size_type>(
                            std::round(line.inverse(y_bounds_start)));

                        for (auto y = y_bounds_start; y < y_bounds_end; y++)
                        {
                            auto x_next = static_cast<TextSurface::size_type>(
                                std::round(line.inverse(
                                    static_cast<PrecisionType>(y + 1))));

                            char chr;
                            if (x_prev == x_next)
                            {
                                chr = '|';
                            }
                            else if (x_prev > x_next)
                            {
                                chr = '/';
                            }
                            else
                            {
                                chr = '\\';
                            }

                            // Rounding issues cause x_prev to go still out of
                            // bounds sometimes.
                            if (x_prev < viewbox.x + viewbox.width)
                            {
                                (*m_Target)(x_prev, y) = chr;
                            }

                            x_prev = x_next;
                        }
                    }
                    else
                    {
                        // Line has more width than height or width is equal to
                        // height.

                        auto x_viewbox_bounds = std::minmax(
                            viewbox_intersections[0].first,
                            viewbox_intersections[1].first);

                        auto x_line_bounds = std::minmax(v1[0], v2[0]);

                        // The first element contains the upper bound, and the
                        // second element the lower bound.
                        auto x_bounds_start =
                            static_cast<TextSurface::size_type>(std::max(
                                std::round(x_line_bounds.first),
                                x_viewbox_bounds.first));
                        // Need to max with 0.0f as a negative value here
                        // results in an overflow, as TextSurface::size_type
                        // is unsigned.
                        auto x_bounds_end =
                            static_cast<TextSurface::size_type>(std::max(
                                0.0f,
                                std::min(
                                    std::round(x_line_bounds.second),
                                    x_viewbox_bounds.second)));

                        // Due to integer rounding we could achieve a negative
                        // function value for our line, resulting in an overflow
                        // for our target unsigned integral type and so causing
                        // a segmentation fault.
                        auto y_prev = static_cast<TextSurface::size_type>(
                            std::round(line(x_bounds_start)));

                        for (auto x = x_bounds_start; x < x_bounds_end; x++)
                        {
                            auto y_next = static_cast<TextSurface::size_type>(
                                std::round(line(
                                    static_cast<PrecisionType>(x + 1))));

                            char chr;
                            TextSurface::size_type surface_y;

                            if (y_prev == y_next)
                            {
                                chr = '_';
                                surface_y = y_prev - 1;
                            }
                            else if (y_prev < y_next)
                            {
                                chr = '\\';
                                surface_y = y_prev;
                            }
                            else
                            {
                                chr = '/';
                                surface_y = y_next;
                            }

                            if (surface_y < viewbox.y + viewbox.height)
                            {
                                (*m_Target)(x, surface_y) = chr;
                            }

                            y_prev = y_next;
                        }
                    }
                }
            }
        }
    }

    void
    TextRenderer::render()
    {
        if (!m_Target)
        {
            throw std::logic_error("No render target set! Use `set_target` to "
                                   "link a target surface to this renderer.");
        }

        render_points();
        render_lines();
    }
}
}
