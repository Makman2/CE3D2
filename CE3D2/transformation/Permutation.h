#ifndef CE3D2_TRANSFORMATION_PERMUTATION_H
#define CE3D2_TRANSFORMATION_PERMUTATION_H

#include "CE3D2/transformation/LinearTransformation.h"
#include "CE3D2/transformation/PermutationVector.h"


namespace CE3D2
{
namespace Transformation
{
    /// Creates a permutation matrix.
    ///
    /// A permutation matrix switches vector entries. To specify the switching
    /// order, a vector is specified. The vector contains the numbers @code 0
    /// @endcode up to @code size-of-vector - 1 @endcode. The number refers to
    /// the position of the entry that shall be taken and the position where the
    /// number is placed inside the permutation vector refers to the position of
    /// the new vector.
    ///
    /// For example a permutation vector \f$ (0,1,2,3) \f$ would perform no
    /// permutation at all, the underlying matrix is an identity matrix. A
    /// permutation vector of \f$ (3,2,1,0) \f$ would reverse the vector. And
    /// \f$ (1,0,2,3) \f$ would switch the first two elements of a vector.
    class Permutation : public LinearTransformation
    {
    public:
        /// Creates a new permutation transformation.
        ///
        /// @param permutation
        ///     The permutation vector.
        Permutation(PermutationVector const& permutation);

        /// Creates a new permutation transformation which reverses the elements
        /// inside the givwen vector.
        ///
        /// @param size
        ///     The size of the permutation matrix.
        Permutation(PermutationVector::size_type size);

        virtual ~Permutation();

        /// Gets the permutation vector set.
        ///
        /// @return
        ///     The permutation vector.
        PermutationVector const&
        get_permutation_vector() const;

        /// Sets the permutation vector.
        ///
        /// @param value
        ///     The new permutation vector.
        void
        set_permutation_vector(PermutationVector const& value);

    protected:
        // Inherited documentation.
        virtual CE3D2::Matrix
        on_update() const override;

    private:
        /// Creates a reverse-permutation vector.
        ///
        /// @param size
        ///     The size of the permutation vector.
        /// @return
        ///     A permutation vector.
        static PermutationVector
        generate_reverse_permutation(PermutationVector::size_type size);

        PermutationVector m_PermutationVector;
    };
}
}

#endif
