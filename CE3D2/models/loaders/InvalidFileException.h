#ifndef CE3D2_MODELS_LOADERS_INVALIDFILEEXCEPTION_H
#define CE3D2_MODELS_LOADERS_INVALIDFILEEXCEPTION_H

#include <stdexcept>


namespace CE3D2
{
namespace Models
{
namespace Loaders
{
    /// An exception that is thrown when a file can't be opened (whatever the
    /// reason).
    class InvalidFileException: public std::runtime_error
    {
    public:
        InvalidFileException(std::string const& message);
    };
}
}
}

#endif
