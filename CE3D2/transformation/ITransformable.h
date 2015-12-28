#ifndef CE3D2_TRANSFORMATION_ITRANSFORMABLE_H
#define CE3D2_TRANSFORMATION_ITRANSFORMABLE_H

#include "CE3D2/transformation/Transformation.h"


namespace CE3D2
{
namespace Transformation
{
    /// Defines an interface that allows to transform objects.
    class ITransformable
    {
    public:
        virtual ~ITransformable();

        /// Transforms the object with the given Transformation.
        ///
        /// Override this function to define how your object should get
        /// transformed.
        ///
        /// @param transform The Transformation to transform with.
        virtual void
        transform(Transformation const& transform) = 0;
    };
}
}

#endif
