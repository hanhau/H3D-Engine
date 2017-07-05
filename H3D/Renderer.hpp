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

const std::string GlobalRenderLogPath = "globalrender.log";
/////////////////////////////////////////////////////////////////
// RendererClass
/////////////////////////////////////////////////////////////////
namespace h3d {
	class Drawable;
	class GlobalRendererImpl  
	{
		enum class StartParameter;

		h3d::Window&		   m_win;
		bool				   m_isWindowActive;

	public:
		GlobalRendererImpl(h3d::Window& window);
		~GlobalRendererImpl();

		enum class StartParameter{
			// Parameter		 // string input
			LogFrametimes,		 // path where to save
			LogFPS,				 // -      "         -
		};
		
		

		// Statistic functions
		float H3D_API getFPS();
		float H3D_API getAvgFrametime();

		// Queing Functions
		void H3D_API queueDrawable(Drawable &drawobj);
	};
}