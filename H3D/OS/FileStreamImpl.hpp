#pragma once
#include <string>

namespace h3d {
	namespace intern {
		class FileStreamImpl {
			std::string m_currentPath;
			unsigned long long m_currentFileSize;
			bool m_isMemoryMapped;
		public:
			enum class StartPos {
				Start,End
			};

			virtual bool open(std::string path) = 0;
			virtual void close() = 0;

			virtual void* getMappedBuffer() = 0;
			
			virtual size_t read(size_t pos, size_t amount,char *buffer);
			virtual size_t write();

			template<typename T>
			T read(size_t pos = -1, StartPos startpos = StartPos::Start) {
				size_t size = sizeof(T);
			}

			template<typename T>
			void write(T& const object,size_t pos=-1,StartPos startpos = StartPos::Start) {
				size_t size = sizeof(T);
			}
		};
	}
}