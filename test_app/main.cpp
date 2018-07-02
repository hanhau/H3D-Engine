#define _CRT_SECURE_NO_WARNINGS

#ifdef _DEBUG
#pragma comment(lib,"../Debug/H3D.lib")
#pragma comment(lib,STR(GLEW_PATH/lib/Release/Win32/glew32.lib))
#else 
#pragma comment(lib,"../Release/H3D.lib")
#pragma comment(lib,STR(GLEW_PATH/lib/Release/Win32/glew32.lib))
#endif 

#pragma comment(lib,"opengl32.lib")

#include <H3D/Model/3DModel.hpp>
#include <H3D/LuaScript/LuaScript.hpp>
#include <H3D/Graphics/Program.hpp>
#include <H3D/Audio/Audio.hpp>
#include <H3D\Clock.hpp>
#include <H3D\Camera.hpp>
#include <H3D/hashing/SHA256.hpp>

#include <iostream>
#include <vector>

#include <H3D\Color.hpp>

#include <H3D\hashing\SHA256.hpp>
#include <H3D/hashing/CRC32.hpp>
#include <H3D\memmng\memory.hpp>

const h3d::Vec2<int> WINDOW_SIZE(600,400);

#include <H3D\ItemContainer.hpp>
#include <H3D\Quaternion.hpp>

int main()
{	
    h3d::CRC32Sum sum;
    unsigned char a[] = { "asdaffwd" };
    sum.create(a,sizeof a);

    h3d::Log::debug("%x", sum.getKey());

	h3d::DebugMode = true;

	h3d::Log::debug("lewl %s", "lewl");

	h3d::Window app(WINDOW_SIZE,
					"Damokles Digger",
					h3d::WindowStyle::Default,
					h3d::ContextSettings(0,0,0,0,false));
	glewInit();

	h3d::Model3D md_obj;
	md_obj.loadFromFile("C:\\Users\\hanne\\Documents\\untitled.obj");
    md_obj.logModelData();

    h3d::Model3D md_fbx;
    md_fbx.loadFromFile("C:\\Users\\hanne\\Documents\\untitled.fbx");
    md_fbx.logModelData();

    glPointSize(10.f);
	h3d::Shader vertexShader(GL_VERTEX_SHADER, "vert_shader.vert"); 
	h3d::Shader	fragmentShader(GL_FRAGMENT_SHADER,"frag_shader.frag");

	h3d::Program gl_program;
	gl_program.attachShader(vertexShader);
	gl_program.attachShader(fragmentShader);

	gl_program.link();
	gl_program.use(true);
	
	glViewport(0, 0,WINDOW_SIZE.x,WINDOW_SIZE.y);

	while (app.isOpen())
	{
		h3d::Event event;

		while(app.pollEvent(event))
		{
			if (event.type == h3d::EventType::Closed) {
				app.close();
				return 0;
			}
		}

		app.clear(GL_COLOR_BUFFER_BIT,
				  h3d::Color<GLfloat>(0.0,0.0,0.0,0.0));



		app.swapBuffers();
	}

	return 0;
}