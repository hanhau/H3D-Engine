#define _CRT_SECURE_NO_WARNINGS
#include <H3D\externals.h>

#ifdef _DEBUG
#pragma comment(lib,"../Debug/H3D.lib")
#pragma comment(lib,STR(GLEW_PATH/lib/Release/Win32/glew32.lib))
#else 
#pragma comment(lib,"../Release/H3D.lib")
#pragma comment(lib,STR(GLEW_PATH/lib/Release/Win32/glew32.lib))
#endif 

#pragma comment(lib,"opengl32.lib")

#include <H3D\Window.hpp>
#include <H3D\3DModel.hpp>
#include <H3D\LuaScript\LuaScript.hpp>
#include <H3D\Program.hpp>
#include <H3D\Audio.hpp>
#include <H3D\Clock.hpp>
#include <H3D\Camera.hpp>

#include <iostream>
#include <vector>

#include <H3D\Color.hpp>

#include <H3D\hashing\SHA256.hpp>
#include <H3D\memmng\memory.hpp>

const h3d::Vec2<int> WINDOW_SIZE(600,400);

#include <H3D\ItemContainer.hpp>
#include <H3D\Quaternion.hpp>

int main()
{	
	h3d::DebugMode = true;

	h3d::Log::debug("lewl %s", "lewl");

	h3d::Window app(WINDOW_SIZE,
					"Damokles Digger",
					h3d::WindowStyle::Default,
					h3d::ContextSettings(0,0,0,0,true));

	GLfloat points[] = {
		0.0,0.0,0.0,0.0,
		0.5,0.0,0.0,0.0,
		0.5,0.5,0.0,0.0,
		0.0,0.5,0.0,0.0,
	};

	GLuint vao;
	glCreateVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint buffer;
	glCreateBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

	glVertexArrayVertexBuffer(vao, 0, buffer, 0, 16);
	glVertexArrayAttribFormat(vao, 0, 4, GL_FLOAT, GL_FALSE, 0);
	glEnableVertexArrayAttrib(vao, 0);

	h3d::Shader vertexShader(GL_VERTEX_SHADER, "vert_shader.vert"); 
	h3d::Shader	fragmentShader(GL_FRAGMENT_SHADER,"frag_shader.frag");

	h3d::Program gl_program;
	gl_program.attachShader(vertexShader);
	gl_program.attachShader(fragmentShader);

	gl_program.link();
	gl_program.use(true);
	
	glViewport(0, 0,WINDOW_SIZE.x,WINDOW_SIZE.y);

	h3d::Clock globalClock;
	globalClock.reset();

	glPointSize(3);

	h3d::Quaternion b(0.1, 0.1, 0.4, 0.4);
	h3d::Quaternion quatA(1.0, 0.0, 0.0, 0.0);
	quatA *= b;

	h3d::mat4x4 rot = quatA.toRotateMat4x4();

	h3d::Vec3<float> point(0.1f, 0.5f, 1.0f);
	h3d::Vec4 p = rot * h3d::Vec4(point,0.0);
	h3d::Vec3<float> pp = rot * point;
	h3d::Log::info("%f %f %f", p.x, p.y, p.z);
	h3d::Log::info("%f %f %f", pp.x, pp.y, pp.z);

	h3d::Camera cam;
	cam.setShaderValues(gl_program, "proj_mat", "view_mat");

	h3d::Log::screenshot("demo/", app);

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
				  h3d::Color<GLfloat>(cos(globalClock.getSeconds()),
									  tan(globalClock.getSeconds()),
									  sin(globalClock.getSeconds()),0.0));

		app.swapBuffers();
	}

	return 0;
}