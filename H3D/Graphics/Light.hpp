#pragma once
#if defined DLL_EXPORT
#define H3D_API __declspec(dllexport)
#else
#define H3D_API __declspec(dllimport)
#endif
/////////////////////////////////////////////////////////////////
#include <vector>
#include "Color.hpp"
#include "../../H3D/Math/Vector.hpp"
#include "../MemoryMng/memory.hpp"

#include <GL/glew.h>
/////////////////////////////////////////////////////////////////
//	Light Class
/////////////////////////////////////////////////////////////////
namespace h3d {
	class Light
	{
	public:
		enum class Type;
		enum class Tag;
	private:
		// Position
		h3d::Vec3<float> m_pos;
		
		Type m_type;
		Tag  m_tag;

		struct PointData
		{
			h3d::Color<float> m_color;
			float			  m_brightness;
		};
		struct AmbientData
		{
			h3d::Color<float> m_color;
			float			  m_brightness;
		};
		struct DirectionalData
		{
			h3d::Color<float> m_color;
			float			  m_brightness;
			h3d::Vec3<float>  m_direction;
			float             m_length;
		};
		struct SpotData
		{
			h3d::Color<float> m_color;
			float			  m_brightness;
			h3d::Vec3<float>  m_direction;
			float			  m_length;
			float			  m_outerRadius;
		};

		// Light Data
		union tagm_lightData
		{
			inline tagm_lightData() {}
			inline ~tagm_lightData() {}

			PointData       point;
			AmbientData     ambient;
			DirectionalData directional;
			SpotData        spot;
		}m_lightData;

	public:
		H3D_API Light();
		H3D_API ~Light();

		enum class Type {
			Ambient, Directional, Spotlight,Point
		};

		enum class Tag {
			_static,_dynamic
		};

		void H3D_API setType(Type type);
		void H3D_API setTag(Tag tag);

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
		void H3D_API createPoint      (h3d::Color<float>color,
									   float brightness);
	};
	/////////////////////////////////////////////////////////////
	// Lightscene for handling a whole Stage
	/////////////////////////////////////////////////////////////
	class Lightscene
	{
	private:
		// Container of Lights
		std::vector<Light> m_lightVec;
	public:
		// Con-/Destructor
		H3D_API Lightscene(h3d::AllocationSource as);
		H3D_API ~Lightscene();

		// File Loading/Saving
		void H3D_API saveToFile(char Path[]);
		void H3D_API loadFromFile(char Path[]);

		// Adding Lights
		int64_t H3D_API addLight(h3d::Light light);
	};
}
/////////////////////////////////////////////////////////////////