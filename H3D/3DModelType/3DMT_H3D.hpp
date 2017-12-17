#pragma once
#if defined DLL_EXPORT
#define H3D_API __declspec(dllexport)
#else
#define H3D_API __declspec(dllimport)
#endif

/////////////////////////////////////////////////////////////////
// Hero 3D Model Format
/////////////////////////////////////////////////////////////////
namespace h3d {
	namespace ModelType {
		class H3D
		{

		public:
			bool H3D_API loadFromFile(char path[]);
			bool H3D_API loadFromMemory(void * mem);

			void H3D_API update(float deltaTime);
			void H3D_API render();
		};
	}
}
/////////////////////////////////////////////////////////////////
