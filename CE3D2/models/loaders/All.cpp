#include "CE3D2/models/loaders/All.h"

#include <boost/filesystem/path.hpp>


namespace CE3D2
{
namespace Models
{
namespace Loaders
{
    std::vector<std::shared_ptr<LineModel>>
    load(std::string filename)
    {
        std::string extension = boost::filesystem::path(filename)
            .extension().string().substr(1);

        if (extension == "obj")
        {
            return load_wavefront_obj(filename);
        }
        else
        {
            throw std::invalid_argument(
                "Unrecognized file extension: ." + extension);
        }
    }
}
}
}
