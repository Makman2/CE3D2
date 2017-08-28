#ifndef CE3D2_TRANSFORMATION_LINEARTRANSFORMATIONCHAIN_H
#define CE3D2_TRANSFORMATION_LINEARTRANSFORMATIONCHAIN_H

#include "CE3D2/transformation/LinearTransformation.h"


namespace CE3D2
{
namespace Transformation
{
    /// Allows to chain different linear transformations.
    ///
    /// Use this class to gain more performance compared to a plain
    /// `TransformationChain` if you use only `LinearTransformation`
    /// instances.
    class LinearTransformationChain : public LinearTransformation
    {
    public:
        /// Instantiates a new empty `LinearTransformationChain`.
        LinearTransformationChain();

        // Inherited documentation.
        void
        transform_vector(CE3D2::Vector& vector) const override;

        /// Gets the list of transformations.
        ///
        /// Instead of applying transformation one-by-one, the
        /// `LinearTransformationChain` takes advantage of
        /// matrix-associativity: Multiple matrices applied to one vector can
        /// be pre-multiplied and then applied. This improves performance
        /// using many vectors.
        ///
        /// Transformations residing at lower indices have higher priority,
        /// meaning they are applied first to vectors.
        ///
        /// If the `LinearTransformationChain` instance is empty, a
        ///
        /// @return A reference to the list holding shared pointers pointing
        ///         at the stored transformations.
        std::vector<std::shared_ptr<LinearTransformation>>&
        transformations();

    protected:
        virtual CE3D2::Matrix
        on_update() const override;

    private:
        std::vector<std::shared_ptr<LinearTransformation>> m_Transformations;
    };
}
}

#endif
