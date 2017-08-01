#ifndef CE3D2_STRINGS_STRINGS_H
#define CE3D2_STRINGS_STRINGS_H

#include <string>


namespace CE3D2
{
namespace Strings
{
    /// Converts a string to a float value.
    ///
    /// This function is effectively the same as std::stof(), with the
    /// exception that this function checks additionally whether the complete
    /// string was consumed for parsing. If not the whole string was used, an
    /// std::invalid_argument error is thrown.
    ///
    /// @param str
    ///     The string to convert.
    /// @return
    ///     The float value.
    float
    to_float(std::string const& str);

    /// Converts a string to a float value.
    ///
    /// This function is effectively the same as std::stoi(), with the
    /// exception that this function checks additionally whether the complete
    /// string was consumed for parsing. If not the whole string was used, an
    /// std::invalid_argument error is thrown.
    ///
    /// @param str
    ///     The string to convert.
    /// @return
    ///     The integer value.
    int
    to_int(std::string const& str);
}
}

#endif
