#ifndef CE3D2_MODELS_STORAGETYPE_H
#define CE3D2_MODELS_STORAGETYPE_H

#include <vector>


namespace CE3D2
{
namespace Models
{
    /// The type of storage used to store stuff inside models.
    template <typename T>
    using StorageType = std::vector<T>;
}
}

#endif
