#include "GLMultithreading.hpp"
/////////////////////////////////////////////////////////////////
//	Implementation of globalCallWorkerThread
/////////////////////////////////////////////////////////////////
namespace h3d {
	namespace GL {
		globalCallWorkerThread::globalCallWorkerThread() {}
		globalCallWorkerThread::~globalCallWorkerThread() {}

		void globalCallWorkerThread::m_callFunction()
		{

		}

		void globalCallWorkerThread::startup()
		{

		}
		void globalCallWorkerThread::shutdown()
		{

		}

		void globalCallWorkerThread::execute(void)
		{

		}
		void globalCallWorkerThread::setState(GLenum cap, GLboolean value)
		{
			m_mutex_setState.lock();
			switch (cap)
			{
			case GL_DEPTH_TEST:
				if (m_state.texture_2d == value) return;
					m_state.texture_2d = value; break;
				if (m_state.depth_test == value) return;
					m_state.depth_test = value; break;
				if (m_state.stencil_test == value) return;
					m_state.stencil_test = value; break;
				if (m_state.depth_clamp == value) return;
				    m_state.depth_clamp = value; break;
			default: break;
			}
			m_mutex_setState.unlock();

			h3d::GL::Packages::gl_ENABLE_DISABLE* __restrict pPacket =
				m_nextPacket<h3d::GL::Packages::gl_ENABLE_DISABLE>();
		}
	}
}
/////////////////////////////////////////////////////////////////