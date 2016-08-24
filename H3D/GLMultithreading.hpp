#pragma once
#if defined DLL_EXPORT
#define H3D_API _declspec(dllexport)
#else
#define H3D_API _declspec(dllimport)
#endif

#include "GLMultithreadingPackages.hpp"
#include <Windows.h>
#include <thread>
#include <list>
#include <GL/glew.h>
#include <mutex>
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
			void		m_callFunction();
			std::mutex  m_mutex_setState;
			std::mutex  m_mutex_queue;

			struct
			{
				GLboolean texture_2d;
				GLboolean depth_test;
				GLboolean stencil_test;
				GLboolean depth_clamp;
			}m_state;

			std::list<h3d::GL::Packages::ALL_PACKAGES> m_queue;
			template<typename T> T* __restrict m_nextPacket(){
				m_mutex_queue.lock();
				m_queue.push_back(h3d::GL::Packages::ALL_PACKAGES());
				m_mutex_queue.unlock();
				return (T*)m_queue[m_queue.size() - 1];
			}
		public:
			~globalCallWorkerThread();

			static globalCallWorkerThread& GetInstance()
			{
			#ifdef _USRDLL
				typedef globalCallWorkerThread* (*GetLoggerFn)();
				HMODULE mod = GetModuleHandle(NULL);
				GetLoggerFn getLogger = (GetLoggerFn)::GetProcAddress(mod, "GetLogger");
				globalCallWorkerThread* Instance = getLogger();
				return *Instance;
			#else
				static Log Instance;
				return Instance;
			#endif
			}
			
			// Startup and shutdown OpenGL call thread
			void startup();
			void shutdown();
			
			// Feed Package Buffer
			void execute(void);
			void setState(GLenum cap,GLboolean value);
		};
	}
#define CallWorkerThread globalCallWorkerThread::getInstance()
}
/////////////////////////////////////////////////////////////////
