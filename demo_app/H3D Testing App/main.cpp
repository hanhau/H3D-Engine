#pragma comment(lib,"../../Release/H3D.lib")
#include <H3D\externals.h>
#pragma comment(lib,STR(GLEW_PATH/lib/Release/Win32/glew32.lib))
#pragma comment(lib,"opengl32.lib")

#include <H3D\Window.hpp>
#include <H3D\LuaScript\LuaScript.hpp>

int main()
{	
	h3d::Window app(h3d::Vec2<unsigned int>(800,600),L"Test",h3d::WindowStyle::Default);

	bool running = true;
	while (running)
	{
		while (GetMessage(app.getMessage(), NULL, 0, 0))
		{
			TranslateMessage(app.getMessage());
			DispatchMessage(app.getMessage());
		}

		app.clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT,
				  h3d::Color<GLfloat>(1.0,0.5,0.25,1.0));

		

		app.swapBuffers();
	}

	app.close();
	return 0;
}