#include "../System/Config.hpp"

#ifdef H3D_SYSTEM_WINDOWS
#include "../OS/FileStreamImpl.hpp"
#include <Windows.h>

namespace h3d {
	namespace intern {
		class Win32FileStreamImpl : public h3d::intern::FileStreamImpl
		{
			HANDLE m_fileHandle;
			HANDLE m_mappedFileHandle;
		public:
			inline Win32FileStreamImpl() : FileStreamImpl() {}

			bool open(std::string Path,int params);
			void close();

			void* openFileMapping(std::string Path,int params, size_t offset);
			void  closeFileMapping();

			size_t read(size_t length, char* buffer);
			size_t write(size_t length, char* buffer);

			void setIteratorPos(size_t pos);
			size_t getIteratorPos();
		};
	}
}

#endif