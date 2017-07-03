#pragma once
#if defined DLL_EXPORT
#define H3D_API __declspec(dllexport)
#else
#define H3D_API __declspec(dllimport)
#endif

#include <vector>
#include <queue>
#include <thread>
#include "Window.hpp"

const std::string GlobalRenderLogPath = "globalrender.log";
/////////////////////////////////////////////////////////////////
// RendererClass
/////////////////////////////////////////////////////////////////
// während ein frame render, werden die nächsten objekte gebatcht
namespace h3d {
	class Drawable;
	class GlobalRenderer  
	{
		enum class StartParameter;

		h3d::Window&		   m_win;
		bool				   m_isWindowActive;
		std::thread			   m_processThread;
		bool				   m_processFunction(std::vector<
										GlobalRenderer::StartParameter
															 >params());
		std::queue<Drawable>   m_drawableQueue;

		// Logging functions


	public:
		H3D_API GlobalRenderer(h3d::Window& window);
		H3D_API ~GlobalRenderer();

		enum class StartParameter{
			// Parameter		 // string input
			LogFrametimes,		 // path where to save
			LogFPS,				 // -      "         -
		};
		
		bool H3D_API start(std::vector<StartParameter> params());
		bool H3D_API stop();

		// Statistic functions
		float H3D_API getFPS();
		float H3D_API getAvgFrametime();

		// Queing Functions
		void H3D_API queueDrawable(Drawable drawobj);
	};

	class Drawable
	{
				
	public:
		enum class Type{
			Model, 
		};

		Drawable();

		virtual void render();
	};
}