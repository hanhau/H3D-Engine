#pragma comment(lib,"../../Release/H3D.lib")

#include <H3D\externals.h>
#pragma comment(lib,STR(GLEW_PATH/lib/Release/Win32/glew32.lib))
#pragma comment(lib,"opengl32.lib")

#include <H3D\Window.hpp>
#include <H3D\3DModel.hpp>
#include <H3D\LuaScript\LuaScript.hpp>
#include <H3D\Program.hpp>
#include <H3D\FileSystem.hpp>
#include <H3D\Matrix.hpp>

#include <iostream>

int main()
{	
	h3d::Window app(h3d::Vec2<unsigned int>(1280,720),L"Test",h3d::WindowStyle::Default);
	
	h3d::DebugMode = true;

	h3d::Model3D obj;
	obj.loadFromFile("demoobj.obj");

	GLchar* strvert = { "#version 330\n"

						"layout(location=0) in vec3 position;"
						"out vec3 pos;"

						"void main(){"
						"gl_Position = position;"
						"}" 
						};
	h3d::Shader vertexShader(GL_VERTEX_SHADER, strvert); 

	GLchar* strfrag = { "#version 330\n"
						"out vec4 color;"
						"void main(){"
							"color = vec4(0.35,0.35,0.25,0.5);"
						"}" };
	h3d::Shader	fragmentShader(GL_FRAGMENT_SHADER, strfrag);

	h3d::Program gl_program;

	gl_program.attachShader(vertexShader);
	gl_program.attachShader(fragmentShader);

	std::cout << gl_program.link() << std::endl;
	gl_program.use(true);

	h3d::FileHandle fh;
	std::cout << fh.open("demoobj.obj", true) << std::endl;	
	std::cout << fh.getMappingPtr<char*>() << std::endl;	
	fh.close();
	
	glViewport(0, 0, 1920, 1080);

	auto polygons = { 1.0f,0.2f,0.7f,
					  1.0f,0.7f,1.0f,
					  1.0f,0.2f,0.6f};
	GLuint buffer;

	glGenBuffers(1, &buffer);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 9,
				 &polygons, GL_STREAM_READ);

	bool running = true;
	while (running)
	{
		if (::PeekMessage(app.getMessage(), 0, 0, 0, PM_REMOVE))
		{
			if (app.getMessage()->message == WM_QUIT ||
				app.getMessage()->message == WM_CLOSE ||
				app.getMessage()->message == WM_DESTROY)
				app.close();

			::TranslateMessage(app.getMessage());
			::DispatchMessage(app.getMessage());
		}

		app.clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT,
				  h3d::Color<GLfloat>(1.0,0.5,0.25,1.0));

		obj.render();
		
		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		glDrawArrays(GL_LINE_LOOP, 0, 9);

		app.swapBuffers();
	}

	app.close();
	return 0;
}