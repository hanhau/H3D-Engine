#pragma once
#if defined DLL_EXPORT
#define H3D_API __declspec(dllexport)
#else
#define H3D_API __declspec(dllimport)
#endif

#include <string>
#include <cstdint>
#include <cstddef>
/////////////////////////////////////////////////////////////////
//	Resource
/////////////////////////////////////////////////////////////////
namespace h3d {
	struct ResourceBase {
	protected:
		union {
			uint64_t v[4];
		}m_uid;
	public:
		virtual bool loadFromFile(char path[])    = 0;
		virtual bool loadFromMemory(void * mem)   = 0;

		virtual void setParameters(char params[]) = 0;

		virtual bool unload()         = 0;
		virtual bool load()           = 0;
		virtual bool makeReadyToUse() = 0;
	};
    
	class Resource
	{
	public:
		enum class State;
	private:
		friend Resource createResource(std::string name, std::string path);

		ResourceBase *m_base;

		// Reference count
		uint64_t m_refCount;

		// Path 
		std::string m_path;
		std::string m_filename;
		std::string m_name;

		// State
		State m_state;
	public:
		// Con-/Destructor
		H3D_API Resource();
		H3D_API ~Resource();
		H3D_API Resource(const Resource&& res);

		// Getter
		std::string H3D_API getPath();
		std::string H3D_API getFilename();
		std::string H3D_API getName();
		long        H3D_API getSize();

		enum class State {
			loaded,       // Loaded and ready to use
			hot,          // Loaded, needs to be made ready
			cold,         // Exists
		};

		// Apply the new State
		void H3D_API updateState(State state);

		// Reference counter
		void H3D_API increaseRefCount();
		void H3D_API decreaseRefCount();
		bool H3D_API isReferenced();
	};

	Resource createResource(std::string name, std::string path);
}
/////////////////////////////////////////////////////////////////