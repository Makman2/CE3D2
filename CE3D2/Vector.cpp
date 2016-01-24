#include "CE3D2/Vector.h"


namespace CE3D2
{
    Vector
    create_vector(PrecisionType v0)
    {
        Vector v(1);
        v[0] = v0;
        return v;
    }

    Vector
    create_vector(PrecisionType v0, PrecisionType v1)
    {
        Vector v(2);
        v[0] = v0;
        v[1] = v1;
        return v;
    }

    Vector
    create_vector(PrecisionType v0, PrecisionType v1, PrecisionType v2)
    {
        Vector v(3);
        v[0] = v0;
        v[1] = v1;
        v[2] = v2;
        return v;
    }

    Vector
    create_vector(PrecisionType v0,
                  PrecisionType v1,
                  PrecisionType v2,
                  PrecisionType v3)
    {
        Vector v(4);
        v[0] = v0;
        v[1] = v1;
        v[2] = v2;
        v[3] = v3;
        return v;
    }

    Vector
    create_vector(PrecisionType v0,
                  PrecisionType v1,
                  PrecisionType v2,
                  PrecisionType v3,
                  PrecisionType v4)
    {
        Vector v(5);
        v[0] = v0;
        v[1] = v1;
        v[2] = v2;
        v[3] = v3;
        v[4] = v4;
        return v;
    }
}
