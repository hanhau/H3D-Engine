#pragma once
#if defined DLL_EXPORT
#define H3D_API _declspec(dllexport)
#else
#define H3D_API _declspec(dllimport)
#endif
/////////////////////////////////////////////////////////////////
#include "Scenegraph.hpp"

namespace h3d{ namespace ScenegraphNode {
	/////////////////////////////////////////////////////////////////
	// Switch Node
	/////////////////////////////////////////////////////////////////
	class Switch : public ScenegraphNodeBase
	{
	private:
		
	public:
		
	};
	/////////////////////////////////////////////////////////////////
	// TransformationNode
	/////////////////////////////////////////////////////////////////
	class Transformation : public ScenegraphNodeBase
	{
	private:
			
	public:

	};
	/////////////////////////////////////////////////////////////////
	// Drawable Node
	/////////////////////////////////////////////////////////////////
	class Drawable : public ScenegraphNodeBase
	{
	private:

	public:

	};
	/////////////////////////////////////////////////////////////////
	// Camera Node
	/////////////////////////////////////////////////////////////////
	class Camera : public ScenegraphNodeBase
	{
	private:

	public:

	};
	/////////////////////////////////////////////////////////////////
	// Light Node
	/////////////////////////////////////////////////////////////////
	class Light : public ScenegraphNodeBase
	{
	private:

	public:

	};
	/////////////////////////////////////////////////////////////////
}}