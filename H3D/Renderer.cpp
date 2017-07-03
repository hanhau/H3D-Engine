#include "Renderer.hpp"
#include "Utilities.hpp"
#include "FileSystem.hpp"
#include <cstdlib>
/////////////////////////////////////////////////////////////////
// Implementation of GlobalRenderer
/////////////////////////////////////////////////////////////////
namespace h3d {
	GlobalRenderer::GlobalRenderer(h3d::Window& window) :
		m_win(window) {
			if (m_win.isOpen()) 
			{
				m_win.setActive();
				m_isWindowActive = true;


			}
			else AssertFailed(__FILE__,std::to_string(__LINE__).c_str(),
							  "Unable to create GlobalRenderer");
	}
	/////////////////////////////////////////////////////////////
	bool GlobalRenderer::start(std::vector<
							   GlobalRenderer::StartParameter
										   >params())
	{


		return true;
	}
	bool GlobalRenderer::stop()
	{

	}
	/////////////////////////////////////////////////////////////
	bool m_processFunction(std::vector<
						GlobalRenderer::StartParameter
									   >params)
	{
		// Parameter Check
		bool isLoggingFps(false),isLoggingFrametime(false);
		for (auto &iter : params)
		{
			iter == GlobalRenderer::StartParameter::LogFPS ? 
				isLoggingFps = true : false;
			iter == GlobalRenderer::StartParameter::LogFPS ? 
				isLoggingFrametime = true : false;
		}

		FileHandle filehandle(GlobalRenderLogPath);

		bool running = true;
		while (running)
		{
			
		}

		return true;
	}
/////////////////////////////////////////////////////////////////
}