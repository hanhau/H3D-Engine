#pragma once
#if defined DLL_EXPORT
#define H3D_API __declspec(dllexport)
#else
#define H3D_API __declspec(dllimport)
#endif

#include <vector>
#include <queue>
#include <thread>
#include "memmng\linear_alloc.hpp"
#include "Window.hpp"
#include "Drawable.hpp"

/////////////////////////////////////////////////////////////////
// RendererClass
/////////////////////////////////////////////////////////////////
namespace h3d {
	class Drawable;
	class GlobalRenderer 
	{
		enum class StartParameter;
		static std::unique_ptr<h3d::Window> m_win;
	public:
		static bool H3D_API init(std::unique_ptr<h3d::Window> winptr,
								 StartParameter				  params[]);

		enum class StartParameter{
			// Parameter		 // string input
			LogFrametimes,		 // path where to save
			LogFPS,				 // -      "         -
		};
		
		// static public Intel
		static std::string H3D_API GlobalRendererLogPath;

		// Statistic functions
		static double H3D_API getFPS();
		static double H3D_API getAvgFrametime();

		// Queing Functions
		static void H3D_API queueDrawable(Drawable &drawobj);
	};
}