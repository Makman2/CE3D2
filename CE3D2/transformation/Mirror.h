#ifndef CE3D2_TRANSFORMATION_MIRROR_H
#define CE3D2_TRANSFORMATION_MIRROR_H

#include "CE3D2/Matrix.h"
#include "CE3D2/transformation/LinearTransformation.h"
#include "CE3D2/Vector.h"


namespace CE3D2
{
namespace Transformation
{
    /// The Householder transformation that mirrors a vector on a given
    /// hyperplane.
    class Mirror : public LinearTransformation
    {
    public:
        /// Instantiates a new mirror transformation.
        ///
        /// @param reflection_plane_normal The normal vector of the reflection
        ///                                plane.
        Mirror(CE3D2::Vector const& reflection_plane_normal);

        virtual ~Mirror();

        /// Returns the normal vector of the reflection plane.
        ///
        /// @returns The normal vector.
        CE3D2::Vector const&
        get_reflection_plane_normal() const;

        /// Sets the normal vector of the reflection plane.
        ///
        /// @param value The new normal vector.
        void
        set_reflection_plane_normal(CE3D2::Vector const& value);

        // Inherited documentation.
        void
        transform_vector(CE3D2::Vector& vector) const override;

    protected:
        // Inherited documentation.
        virtual CE3D2::Matrix
        on_update() const override;

    private:
        static CE3D2::Vector
        calculate_matrix_part_cache(
            CE3D2::Vector const& reflection_plane_normal);

        CE3D2::Vector m_ReflectionPlaneNormal;
        // This cache holds the value `2 * v / (v^T * v)` from the complete
        // formula (`I - 2 * v * v^T / (v^T * v)`) for caching purposes when
        // applying the transformation on a single vector. Calculated by
        // `calculate_matrix_part_cache`.
        CE3D2::Vector m_MatrixPartCache;
    };
}
}

#endif
