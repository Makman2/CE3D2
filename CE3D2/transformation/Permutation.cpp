#include "CE3D2/transformation/Permutation.h"


namespace CE3D2
{
namespace Transformation
{
    Permutation::Permutation(PermutationVector const& permutation)
    : m_PermutationVector(permutation)
    {}

    Permutation::Permutation(PermutationVector::size_type size)
    : Permutation(generate_reverse_permutation(size))
    {}

    Permutation::~Permutation()
    {}

    CE3D2::Matrix
    Permutation::on_update() const
    {
        Matrix m(ZeroMatrix(m_PermutationVector.size(),
                            m_PermutationVector.size()));

        for (PermutationVector::size_type i = 0;
             i < m_PermutationVector.size();
             i++) {
            m(i, m_PermutationVector[i]) = 1.0f;
        }

        return m;
    }

    PermutationVector const&
    Permutation::get_permutation_vector() const
    {
        return m_PermutationVector;
    }

    void
    Permutation::set_permutation_vector(PermutationVector const& value)
    {
        m_PermutationVector = value;
        update();
    }

    PermutationVector
    Permutation::generate_reverse_permutation(PermutationVector::size_type size)
    {
        CE3D2::Transformation::PermutationVector vector(size);

        PermutationVector::size_type v = size - 1;
        for (PermutationVector::size_type i = 0; i < size; i++) {
            vector[i] = v;
            v--;
        }

        return vector;
    }
}
}
