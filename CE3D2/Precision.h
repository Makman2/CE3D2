#ifndef CE3D2_PRECISION_H
#define CE3D2_PRECISION_H


namespace CE3D2
{
    /// The precision type of CE3D2 used by algebraic types like vectors,
    /// matrices etc.
    ///
    /// Change this if you want to increase precision of mathematical
    /// calculations from types using this.
    using PrecisionType = float;

    /// The constant `pi` matching the precision given in PrecisionType.
    PrecisionType constexpr PI = 3.1415926535897932384626433832795028841971693f;
}

#endif
