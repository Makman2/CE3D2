#include "CE3D2/models/LineModel.h"


namespace CE3D2
{
namespace Models
{
    LineModel::LineModel()
    : Model()
    , m_Connections()
    {}

    LineModel::LineModel(std::string name)
    : Model(name)
    , m_Connections()
    {}

    LineModel::LineModel(Model const& copy)
    : Model(copy)
    , m_Connections()
    {}

    LineModel::~LineModel()
    {}

    StorageType<IndexPair> const&
    LineModel::connections() const
    {
        return m_Connections;
    }

    StorageType<IndexPair>&
    LineModel::connections()
    {
        return m_Connections;
    }
}
}
