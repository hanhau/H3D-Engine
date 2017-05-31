#pragma comment(lib,"../../Release/H3D.lib")
#include "..\..\H3D.hpp"

int main()
{	
	h3d::Window win(h3d::Vec2<unsigned int>(800,600),L"Testing App",h3d::WindowStyle::Default);
	Sleep(1000);
	win.close();
	return 0;
}