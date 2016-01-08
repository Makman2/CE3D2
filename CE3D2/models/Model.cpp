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

    std::vector<Vector> const&
    Model::vectors() const
    {
        return m_Vectors;
    }

    std::vector<Vector>&
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
