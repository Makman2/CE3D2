#include "CE3D2/math/matrices/matrices.h"


namespace CE3D2
{
namespace Math
{
namespace Matrices
{
    template<typename T>
    bool
    invert(boost::numeric::ublas::matrix<T> const& input,
           boost::numeric::ublas::matrix<T>& inverse)
    {
        // Create a working copy of the input.
        boost::numeric::ublas::matrix<T> A(input);

        // Create a permutation matrix for the LU-factorization.
        boost::numeric::ublas::permutation_matrix<std::size_t> pm(A.size1());

        // Perform LU-factorization.
        int res = lu_factorize(A, pm);
        if (res != 0)
        {
            return false;
        }

        // Create identity matrix of "inverse".
        inverse = boost::numeric::ublas::identity_matrix<T>(A.size1());

        // Backsubstitute to get the inverse.
        lu_substitute(A, pm, inverse);

        return true;
    }
}
}
}
