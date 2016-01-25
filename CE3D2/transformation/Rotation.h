#ifndef CE3D2_TRANSFORMATION_ROTATION_H
#define CE3D2_TRANSFORMATION_ROTATION_H

#include <vector>

#include "CE3D2/Matrix.h"
#include "CE3D2/Precision.h"
#include "CE3D2/transformation/LinearTransformation.h"
#include "CE3D2/Vector.h"


namespace CE3D2
{
namespace Transformation
{
    /// A transformation describing a rotation inside a plane on an
    /// arbitrary-dimensional space.
    class Rotation : public LinearTransformation
    {
    public:
        /// Instantiates a new Rotation without rotation-plane vectors and
        /// an angle of 0.
        Rotation();

        /// Instantiates a new Rotation with an angle of 0.
        ///
        /// @param v1 The first plane vector.
        /// @param v2 The second plane vector.
        Rotation(CE3D2::Vector const& v1, CE3D2::Vector const& v2);

        /// Instantiates a new Rotation.
        ///
        /// @param v1    The first plane vector.
        /// @param v2    The second plane vector.
        /// @param angle The rotation angle (in radians).
        Rotation(CE3D2::Vector const& v1,
                 CE3D2::Vector const& v2,
                 PrecisionType angle);

        virtual ~Rotation();

        /// Gets the first vector describing the rotation plane.
        ///
        /// @returns A vector.
        CE3D2::Vector const&
        get_plane_vector1() const;

        /// Sets the first vector describing the rotation plane.
        ///
        /// @param value The new vector.
        void
        set_plane_vector1(CE3D2::Vector const& value);

        /// Gets the second vector describing the rotation plane.
        ///
        /// @returns A vector.
        CE3D2::Vector const&
        get_plane_vector2() const;

        /// Sets the second vector describing the rotation plane.
        ///
        /// @param value The new vector.
        void
        set_plane_vector2(CE3D2::Vector const& value);

        /// Gets the rotation angle (in radians).
        ///
        /// @returns The angle in radians.
        PrecisionType
        get_angle() const;

        /// Sets the rotation angle (in radians).
        ///
        /// @param value The new angle in radians.
        void
        set_angle(PrecisionType value);

        /// Gets the rotation angle (in degrees).
        ///
        /// @returns The angle in degrees.
        PrecisionType
        get_angle_in_degrees() const;

        /// Sets the rotation angle (in degrees).
        ///
        /// @param value The new angle in degrees.
        void
        set_angle_in_degrees(PrecisionType value);

    protected:
        // Inherited documentation.
        virtual CE3D2::Matrix
        on_update() const override;

    private:
        CE3D2::Vector m_PlaneVector1;
        CE3D2::Vector m_PlaneVector2;
        PrecisionType m_Angle;

        mutable bool m_MatricesCached;
        mutable CE3D2::Matrix m_CachedMatrixV;
        mutable CE3D2::Matrix m_CachedMatrixW;
        mutable CE3D2::IdentityMatrix m_CachedIdentity;
    };
}
}

#endif
