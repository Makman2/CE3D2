#ifndef CE3D2_TRANSFORMATION_TRANSLATION_H
#define CE3D2_TRANSFORMATION_TRANSLATION_H

#include "CE3D2/transformation/Transformation.h"


namespace CE3D2
{
namespace Transformation
{
    /// A translation transformation that shifts vectors by a given vector.
    class Translation : public Transformation
    {
    public:
        /// Constructs a new Translation.
        ///
        /// @param translation The inital translation vector.
        Translation(CE3D2::Vector const& translation);

        virtual ~Translation();

        /// Returns the translation vector.
        ///
        /// @returns The translation vector.
        CE3D2::Vector&
        get_translation();

        /// Returns the translation vector (non-modifiable).
        ///
        /// @returns The translation vector.
        CE3D2::Vector const&
        get_translation() const;

        /// Sets the translation vector.
        ///
        /// @param value The new translation vector.
        void
        set_translation(CE3D2::Vector const& value);

        // Inherited documentation.
        void
        transform_vector(CE3D2::Vector& vector) const override;

    private:
        CE3D2::Vector m_Translation;
    };
}
}

#endif
