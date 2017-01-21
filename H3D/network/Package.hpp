#pragma once
#if defined DLL_EXPORT
#define H3D_API _declspec(dllexport)
#else
#define H3D_API _declspec(dllimport)
#endif
/////////////////////////////////////////////////////////////////
#include "..\hashing\CRC32.hpp"
#include "..\hashing\UniChecksum.hpp"
/////////////////////////////////////////////////////////////////
// Network Package	
/////////////////////////////////////////////////////////////////
namespace h3d {
	namespace Network {
		class Package
		{
		private:
			unsigned char*    buffer;
			uint64_t          buffersize;
		public:
			template<typename T>
				void H3D_API operator=(T data){
					buffersize = sizeof(data);
					buffer = new unsigned char[buffersize];
					memcpy(buffer, data, buffersize);
				};
			
			H3D_API unsigned char* data() const { return buffer; }

			template<typename T>
			T H3D_API size() const {
				return static_cast<T>(buffersize);
				}

			template<typename checksumtype>
			checksumtype H3D_API checksum(){
				checksumtype checksum;
				checksum.create(buffer,buffersize);
				return checksum;
			}
		};
	}
}
/////////////////////////////////////////////////////////////////