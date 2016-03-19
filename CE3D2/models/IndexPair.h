#ifndef CE3D2_MODELS_INDEXPAIR_H
#define CE3D2_MODELS_INDEXPAIR_H

#include <utility>

#include "CE3D2/models/StorageType.h"
#include "CE3D2/Vector.h"


namespace CE3D2
{
namespace Models
{
    /// An IndexPair stores two indices of two vectors inside a model.
    using IndexPair = std::pair<StorageType<CE3D2::Vector>::size_type,
                                StorageType<CE3D2::Vector>::size_type>;
}
}

#endif
