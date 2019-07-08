#pragma once
#if defined DLL_EXPORT
#define H3D_API __declspec(dllexport)
#else
#define H3D_API __declspec(dllimport)
#endif
/////////////////////////////////////////////////////////////////
namespace h3d {
	namespace {
		class SocketDescriptor {
		public:
			enum class Family {
			};
			enum class SocketType {
				UDP, TCP
			};
			enum class Protocol {
				IP
			};

			Family family;
			SocketType sockettype;
			Protocol protocol;
		};
	}
}
