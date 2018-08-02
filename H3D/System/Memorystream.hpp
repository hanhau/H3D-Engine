#pragma once
#if defined DLL_EXPORT
#define H3D_API __declspec(dllexport)
#else
#define H3D_API __declspec(dllimport)
#endif
/////////////////////////////////////////////////////////////////

namespace h3d {
	class MemoryStream
	{
	private:
		char**        m_bufferPtr;
		unsigned long m_bufferSize;
		unsigned long m_currentPos;
	public:
		// Con-/Destructor
		H3D_API MemoryStream();
		H3D_API ~MemoryStream();

		// Open & Close
		void H3D_API open(char* buffer, unsigned long size);
		void H3D_API close();

		// Read bytes
		H3D_API char* read(unsigned long bytes);
	};
}