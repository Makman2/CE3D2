#ifndef CE3D2_TRANSFORMATION_ORTHOGONALPROJECTION_H
#define CE3D2_TRANSFORMATION_ORTHOGONALPROJECTION_H

#include <vector>

#include "CE3D2/Matrix.h"
#include "CE3D2/transformation/LinearTransformation.h"
#include "CE3D2/Vector.h"


namespace CE3D2
{
namespace Transformation
{
    /// A transformation describing an orthogonal projection onto an
    /// arbitrary-dimensioned (hyper)plane.
    class OrthogonalProjection : public LinearTransformation
    {
    public:
        /// Instantiates a new orthogonal projection without projection vectors.
        OrthogonalProjection();

        /// Instantiates a new orthogonal projection.
        ///
        /// @tparam T      An iterable type to copy projection vectors from.
        /// @param vectors The iterable to copy initial projection vectors from.
        template<typename T>
        OrthogonalProjection(T const& vectors);

        virtual ~OrthogonalProjection();

        /// Returns a read-only reference to the projection vector list to
        /// construct the orthogonal projection for.
        ///
        /// @returns The projection vectors.
        std::vector<CE3D2::Vector> const&
        get_projection_vectors() const;

        /// Sets the projection vectors for this orthogonal projection.
        ///
        /// @tparam T      The iterable type to copy the projection vectors
        ///                from.
        /// @param vectors The iterable to copy the projection vectors from.
        template<typename T>
        void
        set_projection_vectors(T const& vectors);

    protected:
        // Inherited documentation.
        virtual CE3D2::Matrix
        on_update() const override;

    private:
        std::vector<CE3D2::Vector> m_ProjectionVectors;
    };
}
}

#include "CE3D2/transformation/OrthogonalProjection.hpp"

#endif
