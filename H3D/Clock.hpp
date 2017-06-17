#pragma once
#if defined DLL_EXPORT
#define H3D_API __declspec(dllexport)
#else
#define H3D_API __declspec(dllimport)
#endif
/////////////////////////////////////////////////////////////////
#include <Windows.h>
#include <stdint.h>

namespace h3d {
/////////////////////////////////////////////////////////////////
//	Time Class
/////////////////////////////////////////////////////////////////
	class H3D_API Time
	{
	public:
		double m_seconds;
		double m_milliseconds;
		double m_microseconds;
	};
/////////////////////////////////////////////////////////////////
//	Clock Class
/////////////////////////////////////////////////////////////////
	class Clock
	{
		uint64_t m_actualTick; // actual zero point
		uint64_t m_newTick;    // new tick
		uint64_t m_frequency;  // frequency of the clock
		uint64_t m_tickDiff;
	public:
		// Constructor
		H3D_API Clock();
		H3D_API ~Clock();

		// Return Values
		double H3D_API getSeconds();
		double H3D_API getMilliSeconds();
		double H3D_API getMicroSeconds();
		Time   H3D_API getTime();

		uint64_t H3D_API getPastCycles();
		uint64_t H3D_API getFrequency();
		
		// Update Clock
		void H3D_API reset();
	};
}
/////////////////////////////////////////////////////////////////