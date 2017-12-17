#pragma once
#if defined DLL_EXPORT
#define H3D_API __declspec(dllexport)
#else
#define H3D_API __declspec(dllimport)
#endif

/////////////////////////////////////////////////////////////////
// ShaderManager 
/////////////////////////////////////////////////////////////////
namespace h3d {
	class Shader;
	class ProgramPipeline
	{

	public:
		enum class Stage {
			Vertex, Geometry, Fragment,
			Compute, TessEvaluation, TessControl
		};

		bool attachShader(Stage stage,h3d::Shader &shader);
	};
}
/////////////////////////////////////////////////////////////////
