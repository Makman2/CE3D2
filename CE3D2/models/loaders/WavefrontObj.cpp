#include <boost/algorithm/string.hpp>

#include <fstream>
#include <sstream>
#include <unordered_map>

#include "CE3D2/models/loaders/FileFormatException.h"
#include "CE3D2/models/loaders/InvalidFileException.h"
#include "CE3D2/models/loaders/WavefrontObj.h"
#include "CE3D2/strings/strings.h"


namespace CE3D2
{
namespace Models
{
namespace Loaders
{
    enum WavefrontObjSpecifiers
    {
        comment, face, group, material_library, none, object,
        parameter_space_vertex, smoothing, texture_coordinate, use_material,
        vertex, vertex_normal
    };

    template<typename VectorCountType,
             typename FaceIndexType,
             typename LineNumberType>
    VectorCountType
    map_face_index_to_real_index(VectorCountType vector_count,
                                 FaceIndexType face_index,
                                 LineNumberType line_number)
    {
        VectorCountType real_index;
        if (face_index < 0)
        {
            real_index = face_index + vector_count;
        }
        else
        {
            real_index = face_index - 1;
        }

        if (real_index < 0 || real_index >= vector_count)
        {
            std::ostringstream error_stream;
            error_stream << "Index "
                         << face_index
                         << " out of bounds at line "
                         << line_number
                         << ", only "
                         << vector_count
                         << " vector(s) loaded so far for model.";
            throw FileFormatException(error_stream.str());
        }

        return real_index;
    };

    std::vector<std::shared_ptr<LineModel>>
    load_wavefront_obj(std::string const& filename)
    {
        std::ifstream file(filename);

        if (!file.is_open()) {
            throw InvalidFileException("Can't open file: " + filename);
        }

        auto models = load_wavefront_obj(file);
        file.close();
        return models;
    }

    std::vector<std::shared_ptr<LineModel>>
    load_wavefront_obj(std::istream& stream)
    {
        // Build specifier map.
        std::unordered_map<std::string, WavefrontObjSpecifiers> specifiers = {
            {"#", WavefrontObjSpecifiers::comment},
            {"f", WavefrontObjSpecifiers::face},
            {"g", WavefrontObjSpecifiers::group},
            {"mtllib", WavefrontObjSpecifiers::material_library},
            {"", WavefrontObjSpecifiers::none},
            {"o", WavefrontObjSpecifiers::object},
            {"vp", WavefrontObjSpecifiers::parameter_space_vertex},
            {"s", WavefrontObjSpecifiers::smoothing},
            {"vt", WavefrontObjSpecifiers::texture_coordinate},
            {"usemtl", WavefrontObjSpecifiers::use_material},
            {"v", WavefrontObjSpecifiers::vertex},
            {"vn", WavefrontObjSpecifiers::vertex_normal}
        };

        std::vector<std::shared_ptr<LineModel>> models;
        std::shared_ptr<LineModel> current_model;

        unsigned long line_number = 0;
        while (!stream.eof())
        {
            std::string line;
            std::getline(stream, line);
            line_number++;

            std::istringstream line_stream(line);

            std::string specifier_string;
            line_stream >> specifier_string;

            WavefrontObjSpecifiers specifier;
            try
            {
                specifier = specifiers.at(specifier_string);
            }
            catch (std::out_of_range const&)
            {
                // Unknown specifier.
                std::ostringstream error_stream;
                error_stream << "Unknown specifier at line "
                             << line_number
                             << ": "
                             << specifier_string;
                throw FileFormatException(error_stream.str());
            }

            switch (specifier)
            {
                case WavefrontObjSpecifiers::comment:
                case WavefrontObjSpecifiers::none:
                case WavefrontObjSpecifiers::group:
                case WavefrontObjSpecifiers::material_library:
                case WavefrontObjSpecifiers::parameter_space_vertex:
                case WavefrontObjSpecifiers::smoothing:
                case WavefrontObjSpecifiers::texture_coordinate:
                case WavefrontObjSpecifiers::use_material:
                case WavefrontObjSpecifiers::vertex_normal:
                {
                    // Ignore comments and empty lines.
                    // Also ignore specifiers that are officially supported by
                    // the file specification, but have no corresponding
                    // implementation in CE3D2.
                    break;
                }
                case WavefrontObjSpecifiers::object:
                {
                    std::string name;
                    line_stream >> name;
                    current_model = std::make_shared<LineModel>(name);
                    models.push_back(current_model);
                    break;
                }
                case WavefrontObjSpecifiers::face:
                case WavefrontObjSpecifiers::vertex:
                {
                    // Push back new model without name if specifiers occur
                    // that modify geometry and no existent model was created
                    // yet.
                    if (!current_model)
                    {
                        current_model = std::make_shared<LineModel>();
                        models.push_back(current_model);
                    }

                    switch (specifier) {
                        case WavefrontObjSpecifiers::face:
                        {
                            std::vector<int> face_indices;

                            while (true)
                            {
                                std::string value_string;
                                line_stream >> value_string;

                                // Trailing whitespaces are allowed.
                                if (value_string.empty()) {
                                    break;
                                }

                                std::vector<std::string> fields;
                                boost::split(fields,
                                             value_string,
                                             boost::is_any_of("/"),
                                             boost::token_compress_off);

                                if (fields.size() > 3)
                                {
                                    std::ostringstream error_stream;
                                    error_stream
                                        << "Invalid face syntax at line "
                                        << line_number
                                        << ", too many '/': "
                                        << value_string;
                                    throw FileFormatException(
                                        error_stream.str());
                                }

                                int value;

                                try
                                {
                                    // Only relevant is the vertex index.
                                    // Normal and texture coordinate
                                    // information is dismissed.
                                    value = CE3D2::Strings::to_int(fields[0]);
                                }
                                catch (std::invalid_argument const&)
                                {
                                    std::ostringstream error_stream;
                                    error_stream
                                        << "Illegal integer value at line "
                                        << line_number
                                        << ": "
                                        << fields[0];
                                    throw FileFormatException(
                                        error_stream.str());
                                }
                                catch (std::out_of_range const&)
                                {
                                    std::ostringstream error_stream;
                                    error_stream
                                        << "Integer value at line "
                                        << line_number
                                        << " out of bounds: "
                                        << value_string;
                                    throw FileFormatException(
                                        error_stream.str());
                                }

                                face_indices.push_back(value);

                                if (line_stream.eof())
                                {
                                    break;
                                }
                            }

                            // Connect each index in a row with an edge.
                            auto vector_count = current_model->vectors().size();
                            auto& connections = current_model->connections();
                            for (decltype(face_indices)::size_type i = 0;
                                 i < face_indices.size() - 1;
                                 i++)
                            {
                                // To enforce loading order of indices and
                                // throw exceptions in correct order, store
                                // them into variables. Inlining them into the
                                // call lets the calling convention define the
                                // evaluation order of indices.
                                int real_index1 = map_face_index_to_real_index(
                                    vector_count,
                                    face_indices[i],
                                    line_number);
                                int real_index2 = map_face_index_to_real_index(
                                    vector_count,
                                    face_indices[i+1],
                                    line_number);

                                connections.emplace_back(
                                    real_index1, real_index2);
                            }
                            // And connect the first and last element. Loading
                            // order is not important here, as all indices were
                            // already checked before.
                            connections.emplace_back(
                                map_face_index_to_real_index(
                                    vector_count,
                                    face_indices.back(),
                                    line_number),
                                map_face_index_to_real_index(
                                    vector_count,
                                    face_indices.front(),
                                    line_number));

                            break;
                        }
                        case WavefrontObjSpecifiers::vertex:
                        {
                            std::vector<PrecisionType> vector;

                            while (true)
                            {
                                std::string value_string;
                                line_stream >> value_string;

                                // Trailing whitespaces are allowed.
                                if (value_string.empty()) {
                                    break;
                                }

                                float value;

                                try
                                {
                                    value = CE3D2::Strings::to_float(
                                        value_string);
                                }
                                catch (std::invalid_argument const&)
                                {
                                    std::ostringstream error_stream;
                                    error_stream
                                        << "Illegal floating point value at "
                                           "line "
                                        << line_number
                                        << ": "
                                        << value_string;
                                    throw FileFormatException(
                                        error_stream.str());
                                }
                                catch (std::out_of_range const&)
                                {
                                    std::ostringstream error_stream;
                                    error_stream
                                        << "Floating point value at line "
                                        << line_number
                                        << " out of bounds: "
                                        << value_string;
                                    throw FileFormatException(
                                        error_stream.str());
                                }

                                vector.push_back(value);

                                if (line_stream.eof())
                                {
                                    break;
                                }
                            }

                            current_model->vectors().emplace_back(
                                vector.size());
                            std::copy(vector.cbegin(),
                                      vector.cend(),
                                      current_model->vectors().back().begin());

                            break;
                        }
                        default:
                        {
                            throw std::runtime_error(
                                "Bug - Unhandled specifier: "
                                + specifier_string);
                        }
                    }
                    break;
                }
            }
        }

        return models;
    }
}
}
}
