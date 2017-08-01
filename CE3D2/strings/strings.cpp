#include "CE3D2/strings/strings.h"

#include <stdexcept>


namespace CE3D2
{
namespace Strings
{
    float
    to_float(std::string const& str)
    {
        size_t read_count;
        float value = std::stof(str, &read_count);

        if (read_count != str.length())
        {
            throw std::invalid_argument(
                "Can't convert string to float: " + str);
        }

        return value;
    }
}
}
