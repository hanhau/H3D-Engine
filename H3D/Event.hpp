#pragma once
#if defined DLL_EXPORT
#define H3D_API __declspec(dllexport)
#else
#define H3D_API __declspec(dllimport)
#endif
/////////////////////////////////////////////////////////////////
//	class Event
/////////////////////////////////////////////////////////////////
namespace h3d {
class Event 
{
	
};
}
/////////////////////////////////////////////////////////////////