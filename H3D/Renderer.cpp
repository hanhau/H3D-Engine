#include "Renderer.hpp"
#include "Utilities.hpp"
#include "FileSystem.hpp"
#include <cstdlib>

/////////////////////////////////////////////////////////////////
// Implementation of GlobalRenderer
/////////////////////////////////////////////////////////////////
namespace h3d {
	std::string GlobalRenderer::GlobalRendererLogPath = "globalrender.log";
	std::unique_ptr<h3d::Window> GlobalRenderer::m_win;
	
	bool GlobalRenderer::init(std::unique_ptr<h3d::Window> winptr, 
							  StartParameter			   params[])
	{
		if (winptr != nullptr && winptr->isOpen())
		{
			winptr->setActive(true);
			return true;
		} 
		else 
		AssertFailed(__FILE__,std::to_string(__LINE__).c_str(),
					 "Unable to create GlobalRenderer");
		return false;	}
	
	double GlobalRenderer::getFPS() {
		return double();
	}

	double GlobalRenderer::getAvgFrametime() {
		return double();
	}

	uint64_t GlobalRenderer::queueDrawable(Drawable &drawobj) {
		return 0;
	}
}