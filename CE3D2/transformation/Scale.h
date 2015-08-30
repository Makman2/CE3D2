#ifndef CE3D2_TRANSFORMATION_SCALE_H
#define CE3D2_TRANSFORMATION_SCALE_H

#include "CE3D2/transformation/LinearTransformation.h"


namespace CE3D2
{
namespace Transformation
{
    /// A scaling transformation.
    class Scale : public LinearTransformation
    {
    public:
        /// Instantiates a new scaling transformation.
        ///
        /// @param scale The initial scaling vector.
        Scale(CE3D2::Vector const& scale);

        virtual ~Scale();

        /// Returns the scaling vector which contains the scaling factors.
        ///
        /// @returns The scaling vector.
        CE3D2::Vector const&
        get_scale() const;

        /// Sets the scaling vector which contains the scaling factors.
        ///
        /// @param scale The new scaling vector.
        void
        set_scale(CE3D2::Vector const& scale);

        /// Sets a scaling factor inside the scaling vector.
        ///
        /// @param index The index of the vector-element to set the scaling for.
        /// @param scale The new scaling factor.
        void
        set_scale(CE3D2::Vector::size_type index, CE3D2::PrecisionType scale);

    protected:
        // Inherited documentation.
        virtual CE3D2::Matrix
        on_update() const override;

    private:
        CE3D2::Vector m_Scale;
    };
}
}

#endif
