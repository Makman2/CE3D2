#include "CE3D2/models/LineModel.h"

#include <cmath>


namespace CE3D2
{
namespace Models
{
    LineModel::LineModel()
    : Model()
    , m_Edges()
    {}

    LineModel::LineModel(std::string name)
    : Model(name)
    , m_Edges()
    {}

    LineModel::LineModel(Model const& copy)
    : Model(copy)
    , m_Edges()
    {}

    LineModel::~LineModel()
    {}

    LineModel
    LineModel::square()
    {
        return hypercube(2);
    }

    LineModel
    LineModel::cube()
    {
        return hypercube(3);
    }

    LineModel
    LineModel::tesseract()
    {
        return hypercube(4);
    }

    LineModel
    LineModel::hypercube(Vector::size_type dimension)
    {
        using container_size_type = std::remove_reference<decltype(
            std::declval<LineModel>().edges())>::type::size_type;

        // Precompute the size needed to store the index-pairs.
        container_size_type index_count =
            static_cast<container_size_type>(2) << (
                static_cast<container_size_type>(dimension) -
                static_cast<container_size_type>(2)) *
            static_cast<container_size_type>(dimension);

        constexpr auto limit = std::numeric_limits<container_size_type>::digits;
        decltype(limit) bits_needed = static_cast<decltype(limit)>(dimension) -
            static_cast<decltype(limit)>(1) +
            static_cast<decltype(limit)>(ceil(log2(dimension)));
        if (bits_needed > limit)
        {
            throw std::invalid_argument("dimension exceeds machine limits.");
        }

        // The `dimension == 0` case is automatically covered from
        // `Model::hypercube()`.
        auto model = LineModel(Model::hypercube(dimension));
        auto& edges = model.edges();

        // The pre-size calculation formula below doesn't work for
        // `dimension == 1` (because of the bitshift optimizations for 2^x
        // exponential calculations).
        if (dimension == 1)
        {
            edges.push_back(IndexPair(0, 1));
            return model;
        }

        edges.reserve(index_count);

        // Since only `dimension == 2` reaches this code, we can already push
        // back `IndexPair`s we are able to precalculate.
        edges.push_back(IndexPair(0, 1));
        edges.push_back(IndexPair(2, 3));
        edges.push_back(IndexPair(0, 2));
        edges.push_back(IndexPair(1, 3));

        for (container_size_type i = 2; i < dimension; i++)
        {
            // Index duplication phase.
            // Duplicates all existing index-pairs and offsets them by 2^i.
            auto offset = static_cast<container_size_type>(2) << (i - 1);
            auto current_size = edges.size();
            for (container_size_type n = 0; n < current_size; n++)
            {
                auto const& indexpair = edges[n];
                edges.push_back(IndexPair(indexpair.first + offset,
                                                indexpair.second + offset));
            }

            // Cross-link phase.
            // Connect the previously created and duplicated index-pairs.
            for (container_size_type j = 0; j < offset; j++)
            {
                edges.push_back(IndexPair(j, j + offset));
            }
        }

        return model;
    }

    StorageType<IndexPair> const&
    LineModel::edges() const
    {
        return m_Edges;
    }

    StorageType<IndexPair>&
    LineModel::edges()
    {
        return m_Edges;
    }
}
}
