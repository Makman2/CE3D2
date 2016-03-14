#ifndef CE3D2_TRANSFORMATION_LINEARTRANSFORMATION_H
#define CE3D2_TRANSFORMATION_LINEARTRANSFORMATION_H

#include "CE3D2/Matrix.h"
#include "CE3D2/transformation/Transformation.h"


namespace CE3D2
{
namespace Transformation
{
    /// A linear transformation.
    ///
    /// Linear transformations have a significant performance advantage when
    /// it comes to chaining them. Since they are represented by matrices, they
    /// can easily multiplied up to a single matrix instead of applying each
    /// transformation in a row.
    ///
    /// As mentioned linear transformations use matrices in CE3D2. To implement
    /// your own linear transformation override `on_update()` which is invoked
    /// when the matrix needs to be calculated.
    class LinearTransformation : public Transformation
    {
    public:
        /// Instantiates a new `LinearTransformation`.
        ///
        /// A matrix update via `on_update()` is scheduled at instantation.
        LinearTransformation();

        virtual ~LinearTransformation();

        // Still allow to override this function if there are performance
        // advantages when not using the matrix.
        // Inherited documentation.
        virtual void
        transform_vector(CE3D2::Vector& vector) const override;

        /// Returns the matrix the linear transformation is represented by.
        ///
        /// @returns The matrix of the linear transformation.
        CE3D2::Matrix const&
        get_matrix() const;

    protected:
        /// Schedules an update for the matrix calculation.
        ///
        /// This method does not update the matrix itself, `on_update()` does
        /// this instead.
        ///
        /// Invoke this method on setters that affect the matrix values.
        ///
        /// Note that you don't need to invoke this function at the constructor,
        /// since on object creation this instance is automatically scheduled
        /// for update.
        void
        update();

        /// Gets invoked if an update was scheduled and someone wants to fetch
        /// the matrix (via `get_matrix()`).
        ///
        /// Override this method and construct your transformation matrix.
        ///
        /// @returns The updated matrix.
        virtual CE3D2::Matrix
        on_update() const = 0;

    private:
        mutable CE3D2::Matrix m_Matrix;
        mutable bool m_UpdateScheduled;
    };
}
}

#endif
