#include "Renderer.hpp"
#include "Utilities.hpp"
#include "FileSystem.hpp"
#include <cstdlib>
/////////////////////////////////////////////////////////////////
// Implementation of GlobalRenderer
/////////////////////////////////////////////////////////////////
namespace h3d {
	GlobalRendererImpl::GlobalRendererImpl(h3d::Window& window) :
		m_win(window){
			if (m_win.isOpen()) 
			{
				m_win.setActive();
				m_isWindowActive = true;


			}
			else 
		AssertFailed(__FILE__,std::to_string(__LINE__).c_str(),
					 "Unable to create GlobalRenderer");
	}
	/////////////////////////////////////////////////////////////
	
/////////////////////////////////////////////////////////////////
}