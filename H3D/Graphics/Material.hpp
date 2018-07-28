#pragma once
#if defined DLL_EXPORT
#define H3D_API __declspec(dllexport)
#else
#define H3D_API __declspec(dllimport)
#endif
/////////////////////////////////////////////////////////////////
#include <string>
#include "../../H3D/Math/Vector.hpp"
#include "Color.hpp"
typedef float GLfloat;
/////////////////////////////////////////////////////////////////
// Material Class
/////////////////////////////////////////////////////////////////
struct aiMaterial;
namespace h3d {
    class Material 
    {
        std::string m_name;
        Color<GLfloat> m_colDiffuse;
        Color<GLfloat> m_colSpecular;
        Color<GLfloat> m_colAmbient;
        Color<GLfloat> m_colEmissive;
        Color<GLfloat> m_colTransparent;
        float m_opacity;
        float m_shininess;
        float m_shininessStrength;
    public:
        bool loadFromAssimpMaterial(aiMaterial* mat);
    };
}
/////////////////////////////////////////////////////////////////