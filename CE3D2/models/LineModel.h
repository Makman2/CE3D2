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
        /// @param name
        ///     The name of the model.
        LineModel(std::string name);
        /// Instantiates a new `LineModel` from an existing `Model` copying it's
        /// vectors without connections.
        ///
        /// @param copy
        ///     The `Model` to copy.
        LineModel(Model const& copy);

        virtual ~LineModel();

        /// Constructs a (2D) unit-square.
        ///
        /// @returns
        ///     A model containing the square.
        static LineModel
        square();

        /// Constructs a (3D) unit-cube.
        ///
        /// @returns
        ///     A model containing the cube.
        static LineModel
        cube();

        /// Constructs a unit-tesseract (a 4D-cube).
        ///
        /// @returns
        ///     A model containing the tesseract.
        static LineModel
        tesseract();

        /// Constructs a unit-hypercube.
        ///
        /// @param dimensions
        ///     The dimension of the hypercube.
        /// @throws std::invalid_argument
        ///     Thrown when dimension is 0 or less or it's so big that it
        ///     would exceed the machine address space (so on x86 systems the
        ///     limit should be usually 28 and on x64 systems 59).
        /// @returns
        ///     A model containing the hypercube.
        static LineModel
        hypercube(Vector::size_type dimension);

        /// Returns a modifiable `StorageType` that contains the pairs that
        /// define the line-connections of the model between the vectors.
        ///
        /// @returns
        ///     A reference to the `StorageType` containing the
        ///     connection-index-pairs.
        StorageType<IndexPair>&
        connections();

        /// Returns a read-only `StorageType` that contains the pairs that
        /// define the line-connections of the model between the vectors.
        ///
        /// @returns
        ///     A `const` reference to the `StorageType` containing the
        ///     connection-index-pairs.
        StorageType<IndexPair> const&
        connections() const;

    private:
        StorageType<IndexPair> m_Connections;
    };
}
}

#endif
