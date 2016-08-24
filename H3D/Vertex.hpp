#pragma once
#if defined DLL_EXPORT
#define H3D_API _declspec(dllexport)
#else
#define H3D_API _declspec(dllimport)
#endif

#include "Vector.hpp"
#include "Color.hpp"
/////////////////////////////////////////////////////////////////
//	class Vertex
/////////////////////////////////////////////////////////////////
namespace h3d {
class H3D_API Vertex
{
public:
	char bone_bindings;
	char *bones;								 

	h3d::Vec3<float>  Position;
	h3d::Vec2<float>  TexCoord;
	h3d::Color<float> Color;
};
}
/////////////////////////////////////////////////////////////////