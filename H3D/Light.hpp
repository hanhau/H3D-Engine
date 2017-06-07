#pragma once
#if defined DLL_EXPORT
#define H3D_API _declspec(dllexport)
#else
#define H3D_API _declspec(dllimport)
#endif
/////////////////////////////////////////////////////////////////
#include <vector>
#include "Color.hpp"
#include "Vector.hpp"

#include "externals.h"
#include STR(GLEW_INCLUDE/gl/glew.h)
/////////////////////////////////////////////////////////////////
//	Light Class
/////////////////////////////////////////////////////////////////
namespace h3d {
	class Light
	{
	private:
		// Position
		h3d::Vec3<float> m_pos;
		
		// Light Type
		int m_type;

		// Light Data
		union tagm_data
		{
			struct tagAmbData
			{
				h3d::Color<float> m_color;
				float			  m_brightness;
			}AmbientData();
			struct tagDirData
			{
				h3d::Color<float> m_color;
				float			  m_brightness;
				h3d::Vec3<float>  m_direction;
				float             m_length;
			}DirectionalData();
			struct tagSptData
			{
				h3d::Color<float> m_color;
				float			  m_brightness;
				h3d::Vec3<float>  m_direction;
				float			  m_length;
				float			  m_outerRadius;
			}SpotlightData();
		}m_data();

	public:
		// Con-/Destructor
		H3D_API Light();
		H3D_API ~Light();

		// Light Types
		struct Type {
			static const int Ambient     = 0;
			static const int Directional = 1;
			static const int Spotlight   = 2;
		};

		// Create Light
		void H3D_API createAmbient    (h3d::Color<float>color,
									   float brightness);
		void H3D_API createDirectional(h3d::Color<float>color,
									   float brightness,
									   h3d::Vec3<float>direction,
									   float length);
		void H3D_API createSpotlight  (h3d::Color<float>color,
									   float brightness,
									   h3d::Vec3<float>direction,
									   float length,
									   float outerRadius);
	};
	/////////////////////////////////////////////////////////////
	// Class Lightscene for handling a whole Stage
	/////////////////////////////////////////////////////////////
	class Lightscene
	{
	private:
		// Container of Lights
		std::vector<Light> m_lightVec;
	public:
		// Con-/Destructor
		Lightscene();
		~Lightscene();

		// File Loading/Saving
		void H3D_API saveToFile(char Path[]);
		void H3D_API loadFromFile(char Path[]);

		// Adding Lights
		void addLight(h3d::Light light);
	};
}
/////////////////////////////////////////////////////////////////