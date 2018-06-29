#pragma once
#if defined DLL_EXPORT
#define H3D_API __declspec(dllexport)
#else
#define H3D_API __declspec(dllimport)
#endif

#include "GLMultithreadingPackages.hpp"
#include "../OS/OpenGLContext.hpp"
#include <Windows.h>
#include <thread>
#include <list>
#include <mutex>

#include "externals.h"
#include STR(GLEW_INCLUDE/gl/glew.h)
/////////////////////////////////////////////////////////////////
// Package for sending off a call from a different thread
/////////////////////////////////////////////////////////////////
namespace h3d {
	namespace GL {
		class packet_stream;

		class globalCallWorkerThread
		{
		private:
			globalCallWorkerThread();

			std::thread m_callThread;
			void		m_callFunction(GLContext &context,bool* condition);
			bool        m_callFunctionRunning;
			std::mutex  m_mutex_setState;
			std::mutex  m_mutex_queue;

			struct
			{
				GLboolean texture_2d;
				GLboolean depth_test;
				GLboolean stencil_test;
				GLboolean depth_clamp;
			}m_state;

			std::list<Packages::ALL_PACKAGES> m_queue;
			template<typename T> T* __restrict m_nextPacket(){
				m_mutex_queue.lock();
				m_queue.push_back(Packages::ALL_PACKAGES());
				m_mutex_queue.unlock();
				return reinterpret_cast<T*>(&m_queue.end());
			}
		public:
			~globalCallWorkerThread();

			static globalCallWorkerThread& GetInstance()
			{
			#ifdef DLL_EXPORT
				typedef globalCallWorkerThread* (*GetCWTFn)();
				HMODULE mod = GetModuleHandle(NULL);
				GetCWTFn GetCWT = (GetCWTFn)::GetProcAddress(mod, "GetCWT");
				globalCallWorkerThread* Instance = GetCWT();
				return *Instance;
			#else
				static globalCallWorkerThread Instance;
				return Instance;
			#endif
			}
			
			// Startup and shutdown OpenGL call thread
			void startup(GLContext &context);
			void shutdown();
			
			// Feed Package Buffer
			void execute(void);
			void setState(GLenum cap,GLboolean value);
		};
	}
	#define CallWorkerThread globalCallWorkerThread::getInstance()
}
/////////////////////////////////////////////////////////////////
