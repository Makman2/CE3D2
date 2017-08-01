#ifndef CE3D2_MODELS_LOADERS_FILEFORMATEXCEPTION_H
#define CE3D2_MODELS_LOADERS_FILEFORMATEXCEPTION_H

#include <stdexcept>


namespace CE3D2
{
namespace Models
{
namespace Loaders
{
    /// An exception that is thrown when an invalid format is encountered in a
    /// file (for arbitrary formats).
    class FileFormatException: public std::runtime_error
    {
    public:
        FileFormatException(std::string const& message);
    };
}
}
}

#endif
