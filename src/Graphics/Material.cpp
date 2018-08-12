#include "../../H3D/Graphics/Material.hpp"
#include <assimp/material.h>
/////////////////////////////////////////////////////////////////
inline h3d::Color<float> fromAssimpCol(aiColor3D col) {
    return h3d::Color<float>(col.r, col.g, col.b, 1.0);
}

bool h3d::Material::loadFromAssimpMaterial(const aiMaterial* mat) {
	if (mat != nullptr) {
		aiString temp_str;
		aiColor3D temp_col;

		mat->Get(AI_MATKEY_NAME, temp_str);
		m_name = temp_str.C_Str();

		mat->Get(AI_MATKEY_COLOR_DIFFUSE, temp_col);
		m_colDiffuse = fromAssimpCol(temp_col);
		mat->Get(AI_MATKEY_COLOR_SPECULAR, temp_col);
		m_colSpecular = fromAssimpCol(temp_col);
		mat->Get(AI_MATKEY_COLOR_AMBIENT, temp_col);
		m_colAmbient = fromAssimpCol(temp_col);
		mat->Get(AI_MATKEY_COLOR_EMISSIVE, temp_col);
		m_colEmissive = fromAssimpCol(temp_col);
		mat->Get(AI_MATKEY_COLOR_TRANSPARENT, temp_col);
		m_colTransparent = fromAssimpCol(temp_col);

		mat->Get(AI_MATKEY_SHININESS, m_shininess);
		return true;
	}
	return false;
}
/////////////////////////////////////////////////////////////////