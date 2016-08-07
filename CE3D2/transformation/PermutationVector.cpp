#include "CE3D2/transformation/PermutationVector.h"


namespace CE3D2
{
namespace Transformation
{
    PermutationVector
    create_permutation_vector(size_t v0)
    {
        PermutationVector v(1);
        v[0] = v0;
        return v;
    }

    PermutationVector
    create_permutation_vector(size_t v0, size_t v1)
    {
        PermutationVector v(2);
        v[0] = v0;
        v[1] = v1;
        return v;
    }

    PermutationVector
    create_permutation_vector(size_t v0, size_t v1, size_t v2)
    {
        PermutationVector v(3);
        v[0] = v0;
        v[1] = v1;
        v[2] = v2;
        return v;
    }

    PermutationVector
    create_permutation_vector(size_t v0, size_t v1, size_t v2, size_t v3)
    {
        PermutationVector v(4);
        v[0] = v0;
        v[1] = v1;
        v[2] = v2;
        v[3] = v3;
        return v;
    }

    PermutationVector
    create_permutation_vector(size_t v0,
                              size_t v1,
                              size_t v2,
                              size_t v3,
                              size_t v4)
    {
        PermutationVector v(5);
        v[0] = v0;
        v[1] = v1;
        v[2] = v2;
        v[3] = v3;
        v[4] = v4;
        return v;
    }
}
}
