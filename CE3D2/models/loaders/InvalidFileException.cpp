#include "CE3D2/models/loaders/InvalidFileException.h"


namespace CE3D2
{
namespace Models
{
namespace Loaders
{
    InvalidFileException::InvalidFileException(std::string const& message)
    : runtime_error(message)
    {}
}
}
}
