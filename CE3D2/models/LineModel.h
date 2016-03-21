#ifndef CE3D2_MODELS_LINEMODEL_H
#define CE3D2_MODELS_LINEMODEL_H

#include "CE3D2/models/IndexPair.h"
#include "CE3D2/models/Model.h"


namespace CE3D2
{
namespace Models
{
    /// A kind of model that also stores line-connection index-pairs that define
    /// connections between single vectors.
    class LineModel : public CE3D2::Models::Model
    {
    public:
        /// Instantiates a new `LineModel` without a name.
        LineModel();
        /// Instantiates a new `LineModel` with the given name.
        ///
        /// @param name The name of the model.
        LineModel(std::string name);
        /// Instantiates a new `LineModel` from an existing `Model` copying it's
        /// vectors without connections.
        ///
        /// @param copy The `Model` to copy.
        LineModel(Model const& copy);

        virtual ~LineModel();

        /// Returns a modifiable `StorageType` that contains the pairs that
        /// define the line-connections of the model between the vectors.
        ///
        /// @returns A reference to the `StorageType` containing the
        ///          connection-index-pairs.
        StorageType<IndexPair>&
        connections();

        /// Returns a read-only `StorageType` that contains the pairs that
        /// define the line-connections of the model between the vectors.
        ///
        /// @returns A `const` reference to the `StorageType` containing the
        ///          connection-index-pairs.
        StorageType<IndexPair> const&
        connections() const;

    private:
        StorageType<IndexPair> m_Connections;
    };
}
}

#endif
