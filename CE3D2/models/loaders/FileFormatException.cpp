#include "CE3D2/models/loaders/FileFormatException.h"


namespace CE3D2
{
namespace Models
{
namespace Loaders
{
    FileFormatException::FileFormatException(std::string const& message)
    : runtime_error(message)
    {}
}
}
}
