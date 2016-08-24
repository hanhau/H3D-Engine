#include "Scenegraph.hpp"
#if defined DLL_EXPORT
#define H3D_API _declspec(dllexport)
#else
#define H3D_API _declspec(dllimport)
#endif
/////////////////////////////////////////////////////////////////
// Implementaion of Scenegraph functions
/////////////////////////////////////////////////////////////////
//	Con-/Destructors
h3d::ScenegraphNodeBase::ScenegraphNodeBase() {}
h3d::ScenegraphNodeBase::~ScenegraphNodeBase() { destroy(); }
/////////////////////////////////////////////////////////////////
// Memory Release
void h3d::ScenegraphNodeBase::release() { delete this; }
/////////////////////////////////////////////////////////////////
// If Node is Branch
bool h3d::ScenegraphNodeBase::isBranch() { return m_children.empty(); }
/////////////////////////////////////////////////////////////////
// Virtual Update Function
void h3d::ScenegraphNodeBase::update()
{
	for (auto &iter : m_children)
		iter.update();
}
/////////////////////////////////////////////////////////////////
// add Child
void h3d::ScenegraphNodeBase::addChild(const h3d::ScenegraphNodeBase &child)
{
	m_children.push_back(child);
}
// destroy this Node with all Children
void h3d::ScenegraphNodeBase::destroy()
{
	for (auto &iter : m_children) iter.release();
	m_children.clear();
}
/////////////////////////////////////////////////////////////////