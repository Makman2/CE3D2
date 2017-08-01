#include "CE3D2/models/Model.h"


namespace CE3D2
{
namespace Models
{
    Model::Model()
    : Model("")
    {}

    Model::Model(std::string name)
    : m_Name(name)
    , m_Vectors()
    , m_IsVisible(true)
    {}

    Model::~Model()
    {}

    Model
    Model::square()
    {
        return hypercube(2);
    }

    Model
    Model::cube()
    {
        return hypercube(3);
    }

    Model
    Model::tesseract()
    {
        return hypercube(4);
    }

    Model
    Model::hypercube(Vector::size_type dimension)
    {
        if (dimension <= 0)
        {
            throw std::invalid_argument("dimension can't be less or equal 0!");
        }

        using container_size_type =
            std::remove_reference<decltype(std::declval<Model>().vectors())>
            ::type::size_type;
        constexpr auto limit = std::numeric_limits<container_size_type>::digits;
        if (dimension > limit)
        {
            std::ostringstream error_stream;
            error_stream << "dimension can't exceed " << limit << " due to "
                            "machine limits.";
            throw std::invalid_argument(error_stream.str());
        }

        Model model;
        auto& vectors = model.vectors();

        container_size_type permutations =
            2 << (static_cast<container_size_type>(dimension) - 1);
        vectors.assign(permutations, Vector(dimension));

        // Use bit-permutations inside a 2^dimension big number to calculate all
        // possible permutations of 0.5 and -0.5 inside the vector of given
        // dimension.
        for (container_size_type i = 0; i < permutations; i++)
        {
            for (Vector::size_type vi = 0; vi < dimension; vi++)
            {
                // Retrieves the `vi`th bit digit, and depending on if it's 1 or
                // 0 it sets the vector entry to -0.5f or  0.5f.
                vectors[i][vi] = (1.0f - 2.0f * ((i >> vi) & 1)) * 0.5f;
            }
        }

        return model;
    }

    std::string const&
    Model::get_name() const
    {
        return m_Name;
    }

    void
    Model::set_name(std::string value)
    {
        m_Name = value;
    }

    bool
    Model::is_visible() const
    {
        return m_IsVisible;
    }

    void
    Model::set_visibility(bool value)
    {
        m_IsVisible = value;
    }

    StorageType<Vector> const&
    Model::vectors() const
    {
        return m_Vectors;
    }

    StorageType<Vector>&
    Model::vectors()
    {
        return m_Vectors;
    }

    void
    Model::transform(CE3D2::Transformation::Transformation const& transform)
    {
        transform.transform(m_Vectors);
    }
}
}
