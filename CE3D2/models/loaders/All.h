#ifndef CE3D2_MODELS_LOADERS_ALL_H
#define CE3D2_MODELS_LOADERS_ALL_H

#include "CE3D2/models/LineModel.h"
#include "CE3D2/models/loaders/WavefrontObj.h"


namespace CE3D2
{
namespace Models
{
namespace Loaders
{
    /// Loads models from file.
    ///
    /// This function determines the right loader-function via the file
    /// extension. Current supported extensions and their formats are:
    /// - Wavefront-OBJ (`load_wavefront_obj()`)
    ///   - `.obj`
    ///
    /// @param filename
    ///     The filename to load the model from.
    /// @returns
    ///     A list of loaded models.
    std::vector<std::shared_ptr<LineModel>>
    load(std::string filename);
}
}
}

#endif
