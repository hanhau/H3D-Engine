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
	enum class EventType {
		Closed, Resized, LostFocus, GainedFocus,
		KeyDown, KeyUp
	};

	class Event 
	{
		
	public:
		EventType type;
	};
}
/////////////////////////////////////////////////////////////////