#pragma once
#include <string>

namespace h3d {
	namespace intern {
		class FileStreamImpl {
		protected:
			std::string				m_currentPath;
			size_t					m_currentFileSize;
			bool					m_isMemoryMapped;
			std::shared_ptr<void*>	m_fileMapPointer;

		public:
			struct Mode {
				enum Values {
					Read = 0b0001,
					Write = 0b0010,
					Exclusive = 0b0100,
					Trunc = 0b1000
				};
			};

			FileStreamImpl() {};
			virtual ~FileStreamImpl() {};

			virtual bool open(std::string Path, int params) = 0;
			virtual void close() = 0;

			virtual void* openFileMapping(std::string Path,int params,size_t offset) = 0;
			virtual void  closeFileMapping() = 0;

			virtual size_t read(size_t length,char* buffer) = 0;
			virtual size_t write(size_t length, char* buffer) = 0;

			virtual void setIteratorPos(size_t pos) = 0;
			virtual size_t getIteratorPos() = 0;
		};
	}
}