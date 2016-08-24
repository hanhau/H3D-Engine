#pragma once
#if defined DLL_EXPORT
#define H3D_API _declspec(dllexport)
#else
#define H3D_API _declspec(dllimport)
#endif

#include <fstream>
#include <string>
/////////////////////////////////////////////////////////////////
// .dae 3D File Format Handling Class
/////////////////////////////////////////////////////////////////
namespace h3d {
	namespace ModelType {
		class DAE
		{
		private:

		public:
			bool _declspec(dllexport) loadFromFile(char Path[]);
		};
	}
}
/////////////////////////////////////////////////////////////////