#pragma once
#if defined DLL_EXPORT
#define H3D_API __declspec(dllexport)
#else
#define H3D_API __declspec(dllimport)
#endif

#include <string>
#include <vector>
#include "..\Vector.hpp"
#include "..\Color.hpp"
#include "..\Vertex.hpp"
#include "..\Texture.hpp"
/////////////////////////////////////////////////////////////////
// .x 3D File Format Handling Class
/////////////////////////////////////////////////////////////////
namespace h3d {
	namespace ModelType {
		class X
		{
		private:
			// Storage of a single Material
			struct Material {
				std::string       m_name;

				h3d::Color<float> m_faceColor;
				float			  m_power;
				h3d::Color<float> m_specularColor;
				h3d::Color<float> m_emissiveColor;

				std::string       m_textureFilename;
			};
			// Sum of Material a Mesh is using
			struct MaterialList {
				unsigned long m_nMaterials;
				unsigned long m_nFaceIndexes;
				std::vector<unsigned long> m_FaceIndexes;

				std::vector<Material> m_materials;
			};
			// Mesh class
			struct Mesh {
				std::string m_name;
				MaterialList m_materialList;
			};

			// Set up OpenGL Buffers
			void prepareRendering();

			// Additional Data
			std::string m_comments;
			std::vector<Mesh> m_meshes;

		public:
			// Con-/Destructor
			X();
			~X();

			// Model Methods
			bool H3D_API loadFromFile(char Path[]);
			void H3D_API render();
			
			// Log Model Intel
			void H3D_API logModelData();
		};
	}
}
/////////////////////////////////////////////////////////////////