#include "../../H3D/System/Config.hpp"
#ifdef H3D_SYSTEM_WINDOWS
#include "../../H3D/OS/Win32FileStreamImpl.hpp"
#include "../../H3D/System/Utilities.hpp"

namespace h3d {
	namespace intern {
		bool Win32FileStreamImpl::open(std::string Path,int params) {
			h3dverify(Path.size() != 0);
			h3d::Log::info("Loading %s now", Path.c_str());

			bool _exlusive = params & Mode::Exclusive;
			bool _trunc = params & Mode::Trunc;
			bool _read = params & Mode::Read;
			bool _write = params & Mode::Write;

			DWORD dwShareMode = FILE_SHARE_READ | FILE_SHARE_WRITE;
			DWORD dwDesiredAccess = 0;
			DWORD dwCreationDisposation = 0;

			if (_read) dwDesiredAccess += GENERIC_READ;
			if (_write) dwDesiredAccess += GENERIC_WRITE;

			m_fileHandle = CreateFileA(Path.c_str(),
				dwDesiredAccess,
				dwShareMode,
				NULL,
				dwCreationDisposation,
				FILE_ATTRIBUTE_NORMAL,
				NULL);

			if (m_fileHandle == INVALID_HANDLE_VALUE) {
				h3d::Log::error("INVALID_HANDLE_VALUE @ %s", Path);
				return false;
			}
			return true;
		}
		void Win32FileStreamImpl::close() {
			if (m_isMemoryMapped) {

			}
			else {

			}
		}

		void* Win32FileStreamImpl::openFileMapping(std::string Path,int params, size_t offset) {
			if (open(Path, params)) {
				
				bool _read = params & Mode::Read;
				bool _write = params & Mode::Write;

				DWORD dwDesiredAccess = 0;
				if (_read) dwDesiredAccess += GENERIC_READ;
				if (_write) dwDesiredAccess += GENERIC_WRITE;

				m_mappedFileHandle = CreateFileMapping(m_fileHandle,
					NULL,
					PAGE_EXECUTE_READWRITE,
					0, 0,
					NULL);
				this->m_fileMapPointer = std::make_shared<void*>(
					MapViewOfFileEx(m_mappedFileHandle,
						dwDesiredAccess, 0, 0, 0, NULL)
					);

				if (this->m_fileMapPointer.get() == nullptr) {
					h3d::Log::error("Error @ MapViewOfFileEx");
					return nullptr;
				}
				m_isMemoryMapped = true;
				return m_fileMapPointer.get();
			}
			else {
				h3d::Log::error("Unable to create Filehandle for %s", Path);
				return nullptr;
			}
		}
		void  Win32FileStreamImpl::closeFileMapping() {

		}

		size_t Win32FileStreamImpl::read(size_t length, char* buffer) {
			return 0;
		}
		size_t Win32FileStreamImpl::write(size_t length, char* buffer) {
			return 0;
		}

		void Win32FileStreamImpl::setIteratorPos(size_t pos) {

		}
		size_t Win32FileStreamImpl::getIteratorPos() {
			return 0;
		}
	} 
}

#endif