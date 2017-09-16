#ifndef CE3D2_TRANSFORMATION_SCALE_H
#define CE3D2_TRANSFORMATION_SCALE_H

#include "CE3D2/transformation/LinearTransformation.h"


namespace CE3D2
{
namespace Transformation
{
    /// A scaling transformation.
    ///
    /// Let \f$ S \f$ be the scale matrix and \f$ s_{ij} \f$ an element of it
    /// where \f$ i \f$ denotes the line position and \f$ j \f$ the column
    /// position of \f$ S \f$. Further let \f$ v \f$ be the scaling vector while
    /// \f$ v_k \f$ denotes the \f$ k \f$-th element of the vector. For every
    /// \f$ i \neq j \f$ applies \f$ s_{ij} = 0\f$ and for every \f$ i = j\f$
    /// applies \f$ a_{ii} = a_{jj} = v_i \f$.
    class Scale : public LinearTransformation
    {
    public:
        /// Instantiates a new scaling transformation.
        ///
        /// @param scale
        ///     The initial scaling vector.
        Scale(CE3D2::Vector const& scale);

        virtual ~Scale();

        /// Returns the scaling vector which contains the scaling factors.
        ///
        /// @returns
        ///     The scaling vector.
        CE3D2::Vector const&
        get_scale() const;

        /// Sets the scaling vector which contains the scaling factors.
        ///
        /// @param scale
        ///     The new scaling vector.
        void
        set_scale(CE3D2::Vector const& scale);

        /// Sets a scaling factor inside the scaling vector.
        ///
        /// @param index
        ///     The index of the vector-element to set the scaling for.
        /// @param scale
        ///     The new scaling factor.
        void
        set_scale(CE3D2::Vector::size_type index, CE3D2::PrecisionType scale);

        // Inherited documentation.
        void
        transform_vector(CE3D2::Vector& vector) const override;

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
