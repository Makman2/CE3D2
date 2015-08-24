#ifndef CE3D2_TRANSFORMATION_TRANSFORMATION_H
#define CE3D2_TRANSFORMATION_TRANSFORMATION_H

#include "CE3D2/Vector.h"


namespace CE3D2
{
namespace Transformation
{
    class Transformation
    {
    public:
        virtual ~Transformation();

        /// Transforms an iterable of vectors (in-place).
        ///
        /// @tparam T      The iterable type of vectors to transform.
        /// @param vectors The iterable of vectors to transform.
        template<typename T>
        void
        transform(T& vectors) const;

        /// Transforms a vector (in-place).
        ///
        /// Override this function to implement your own transformation.
        ///
        /// @param vector The vector to transform.
        virtual void
        transform_vector(CE3D2::Vector& vector) const = 0;
    };
}
}

#include "CE3D2/transformation/Transformation.hpp"

#endif
