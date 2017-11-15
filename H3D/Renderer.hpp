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
#include "Camera.hpp"

/////////////////////////////////////////////////////////////////
// RendererClass
/////////////////////////////////////////////////////////////////
namespace h3d {
	class Drawable;
	class GlobalRenderer 
	{
		std::vector<Drawable> m_drawables;

		enum class StartParameter;
		static std::unique_ptr<h3d::Window> m_win;
	public:
		static bool H3D_API init(std::unique_ptr<h3d::Window> winptr,
								 StartParameter				  params[]);

		static void H3D_API setSceneCamera(h3d::Camera& camera);

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

		// Thread functions
		static void H3D_API receiveOpenGLContext(const h3d::GLContext& context);
		static bool H3D_API startRendering();
		static bool H3D_API endRendering();

		// Queing Functions
		static uint64_t H3D_API queueDrawable(Drawable &drawobj);
	};
}