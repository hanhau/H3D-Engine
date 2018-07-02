#include "../../H3D/OpenGL/GLMultithreading.hpp"
/////////////////////////////////////////////////////////////////
//	Implementation of globalCallWorkerThread
/////////////////////////////////////////////////////////////////
namespace h3d {
	namespace GL {
		globalCallWorkerThread::globalCallWorkerThread() {}
		globalCallWorkerThread::~globalCallWorkerThread() {}

		void globalCallWorkerThread::m_callFunction(GLContext &context,bool* condition)
		{
			
			GL::Packages::ALL_PACKAGES* __restrict pPacket;

			bool temp_condition = *condition;
			while (temp_condition == true)
			{
				{
					std::lock_guard<std::mutex> mut(m_mutex_queue);
					while (!m_queue.empty()) {
						//m_queue.front().execute((GL::base*)0);
						m_queue.pop_front();
					}
				}
			}
		}

		void globalCallWorkerThread::startup(GLContext &context)
		{
			//m_callThread = std::thread(m_callFunction, context,(bool*)&m_callFunctionRunning);
		}

		void globalCallWorkerThread::shutdown()
		{
			m_callThread.join();

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