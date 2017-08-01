#ifndef CE3D2_MODELS_LOADERS_WAVEFRONTOBJ_H
#define CE3D2_MODELS_LOADERS_WAVEFRONTOBJ_H

#include <istream>
#include <memory>
#include <string>
#include <vector>

#include "CE3D2/models/LineModel.h"


namespace CE3D2
{
namespace Models
{
namespace Loaders
{
    /// Loads a Wavefront-OBJ file.
    ///
    /// The model is loaded into a CE3D2::Models::LineModel. Faces are
    /// resolved by connecting each of the defined indices in specification
    /// order and finally the last with the first.
    ///
    /// Because vectors in CE3D2 can have more than 3 or 4 dimensions, the
    /// syntax is extended to support vectors of arbitrary length, even
    /// 2- or 1-dimensional ones.
    ///
    /// Following specifiers that are officially defined in the Wavefront-OBJ
    /// specification are not supported and ignored by this function:
    /// - mtllib (include material library)
    /// - usemtl (use material)
    /// - vn (define normal vector)
    /// - vt (define texture coordinate)
    /// - g (define group)
    /// - s (shading)
    ///
    /// @param filename
    ///     The filename to load from.
    /// @return
    ///     A collection of CE3D2::Models::LineModel.
    std::vector<std::shared_ptr<LineModel>>
    load_wavefront_obj(std::string const& filename);

    /// Loads a Wavefront-OBJ file.
    ///
    /// The model is loaded into a CE3D2::Models::LineModel. Faces are
    /// resolved by connecting each of the defined indices in specification
    /// order and finally the last with the first.
    ///
    /// Because vectors in CE3D2 can have more than 3 or 4 dimensions, the
    /// syntax is extended to support vectors of arbitrary length, even
    /// 2- or 1-dimensional ones.
    ///
    /// Following specifiers that are officially defined in the Wavefront-OBJ
    /// specification are not supported and ignored by this function:
    /// - mtllib (include material library)
    /// - usemtl (use material)
    /// - vn (define normal vector)
    /// - vt (define texture coordinate)
    /// - g (define group)
    /// - s (shading)
    ///
    /// @param stream
    ///     The stream to load from.
    /// @return
    ///     A collection of CE3D2::Models::LineModel.
    std::vector<std::shared_ptr<LineModel>>
    load_wavefront_obj(std::istream& stream);
}
}
}

#endif
