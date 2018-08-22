#pragma once
#if defined DLL_EXPORT
#define H3D_API __declspec(dllexport)
#else
#define H3D_API __declspec(dllimport)
#endif

#include "../../H3D/Math/Vector.hpp"

/////////////////////////////////////////////////////////////////
//	class Vertex
/////////////////////////////////////////////////////////////////
namespace h3d {
class Vertex
{
public:				 
	h3d::Vec3<float>  position;
	h3d::Vec3<float>  normal;
	h3d::Vec2<float>  texCoord;
};
}
/////////////////////////////////////////////////////////////////