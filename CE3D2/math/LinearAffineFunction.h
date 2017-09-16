#ifndef CE3D2_MATH_LINEARAFFINEFUNCTION_H
#define CE3D2_MATH_LINEARAFFINEFUNCTION_H

#include "CE3D2/Precision.h"


namespace CE3D2
{
namespace Math
{
    /// A linear affine function that maps a scalar onto another scalar.
    class LinearAffineFunction
    {
    public:

        /// Creates a new `LinearAffineFunction` with a gradient of 1 and
        /// y-intercept of 0.
        LinearAffineFunction();

        /// Creates a new `LinearAffineFunction` with the given gradient and
        /// an y-intercept of 0.
        ///
        /// @param gradient
        ///     The gradient.
        LinearAffineFunction(PrecisionType gradient);

        /// Creates a new `LinearAffineFunction` from two given coordinates.
        ///
        /// @param x1
        ///     The x-coordinate of the first point.
        /// @param y1
        ///     The y-coordinate of the first point.
        /// @param x2
        ///     The x-coordinate of the second point.
        /// @param y2
        ///     The y-coordinate of the second point.
        LinearAffineFunction(PrecisionType x1,
                             PrecisionType y1,
                             PrecisionType x2,
                             PrecisionType y2);

        /// Creates a new `LinearAffineFunction`.
        ///
        /// @param gradient
        ///     The gradient.
        /// @param yintercept
        ///     The y-intercept.
        LinearAffineFunction(PrecisionType gradient, PrecisionType yintercept);

        /// Returns the gradient.
        ///
        /// @returns
        ///     The gradient.
        PrecisionType
        get_gradient() const;

        /// Sets the gradient.
        ///
        /// @param value
        ///     The new gradient.
        void
        set_gradient(PrecisionType value);

        /// Returns the y-intercept.
        ///
        /// @returns
        ///     The y-intercept.
        PrecisionType
        get_yintercept() const;

        /// Sets the y-intercept.
        ///
        /// @param value
        ///     The new y-intercept.
        void
        set_yintercept(PrecisionType value);

        /// Calculates the y-value of the linear-affine-function at x.
        ///
        /// @returns
        ///     `gradient * x + y-intercept`.
        PrecisionType operator ()(PrecisionType x) const;

        /// Calculates the x-value of the linear-affine-function at y. This is
        /// the inverse of `operator ()`.
        ///
        /// @returns
        ///     `(y - y-intercept) / gradient`.
        PrecisionType inverse(PrecisionType y) const;

    private:
        PrecisionType m_Gradient;
        PrecisionType m_YIntercept;
        PrecisionType m_InverseGradient;
        PrecisionType m_InverseYIntercept;
    };
}
}

#endif
