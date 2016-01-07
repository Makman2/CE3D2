#ifndef CE3D2_TRANSFORMATION_TRANSFORMATIONCHAIN_H
#define CE3D2_TRANSFORMATION_TRANSFORMATIONCHAIN_H

#include "CE3D2/transformation/Transformation.h"


namespace CE3D2
{
namespace Transformation
{
    /// Allows to chain different transformations.
    class TransformationChain : public Transformation
    {
    public:
        /// Instantiates a new empty TransformationChain.
        TransformationChain();

        // Inherited documentation.
        void
        transform_vector(CE3D2::Vector& vector) const override;

        /// Gets the list of transformations.
        ///
        /// Transformations are applied top-down, means the transformation
        /// residing at the lowest index is applied first and the one at the
        /// highest index last.
        ///
        /// @return A reference to the list holding shared pointers pointing at
        ///         the stored transformations.
        std::vector<std::shared_ptr<Transformation>>&
        transformations();

    private:
        std::vector<std::shared_ptr<Transformation>> m_Transformations;
    };
}
}

#endif
