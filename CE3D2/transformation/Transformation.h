#ifndef CE3D2_TRANSFORMATION_TRANSFORMATION_H
#define CE3D2_TRANSFORMATION_TRANSFORMATION_H

#include "CE3D2/Vector.h"


namespace CE3D2
{
namespace Transformation
{
    /// The base class for all transformations.
    ///
    /// A transformation in CE3D2 is considered as a mapping from an
    /// m-dimensional vector onto an arbitrary n-dimensional vector.
    class Transformation
    {
    public:
        virtual ~Transformation();

        /// Transforms an iterable of vectors (in-place).
        ///
        /// @tparam T
        ///     The iterable type of vectors to transform.
        /// @param vectors
        ///     The iterable of vectors to transform.
        template<typename T>
        void
        transform(T& vectors) const;

        /// Transforms a vector (in-place).
        ///
        /// Override this function to implement your own transformation.
        ///
        /// @param vector
        ///     The vector to transform.
        virtual void
        transform_vector(CE3D2::Vector& vector) const = 0;
    };
}
}

#include "CE3D2/transformation/Transformation.hpp"

#endif
