#ifndef CE3D2_MODELS_MODEL_H
#define CE3D2_MODELS_MODEL_H

#include <string>
#include <vector>

#include "CE3D2/Vector.h"


namespace CE3D2
{
namespace Models
{
    /// The base class for all models.
    ///
    /// A model groups vectors together and allows to transform them.
    class Model
    {
    public:
        /// Instantiates a new model without a name.
        Model();
        /// Instantiates a new model with the given name.
        ///
        /// @param name The name of the model.
        Model(std::string name);

        virtual ~Model();

        /// Returns the name of this model. It can be non-unique!
        ///
        /// @returns The name of the model.
        std::string const&
        get_name() const;

        /// Sets the name of this model. It can be non-unique!
        ///
        /// @param value The new name of the model.
        void
        set_name(std::string value);

        /// Returns whether the model is visible or not.
        ///
        /// @returns true if visible, false if not.
        bool
        is_visible() const;

        /// Sets whether the model should be visible.
        ///
        /// @param value true if visible, false if not.
        void
        set_visibility(bool value);

        /// Returns the vector-list that contains the vectors the model consists
        /// of.
        ///
        /// @returns A reference to the std::vector containing the model
        ///          vectors.
        std::vector<Vector> const&
        get_vectors() const;

        /// Returns a modifiable vector-list that contains the vectors the model
        /// consists of.
        ///
        /// @returns A reference to the std::vector containing the model
        ///          vectors.
        std::vector<Vector>&
        get_vectors();

    private:
        std::string m_Name;
        std::vector<Vector> m_Vectors;
        bool m_IsVisible;
    };
}
}

#endif
