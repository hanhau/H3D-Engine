#pragma once
#if defined DLL_EXPORT
#define H3D_API __declspec(dllexport)
#else
#define H3D_API __declspec(dllimport)
#endif

#include <vector>
#include <queue>
#include <thread>
#include "../../H3D/MemoryMng/linear_alloc.hpp"
#include "../../H3D/System/Window.hpp"
#include "../../H3D/Graphics/Drawable.hpp"
#include "../../H3D/Scene/Camera.hpp"

/////////////////////////////////////////////////////////////////
// RendererClass
/////////////////////////////////////////////////////////////////
namespace h3d {
	class Drawable;
	class GlobalRenderer 
	{
	public:
		enum class StartParameter;
	private:
		std::vector<Drawable> m_drawables;
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
		static std::string GlobalRendererLogPath;

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