#include <H3D/System/Window.hpp>
#include <H3D/Graphics/Color.hpp>
#include <H3D/Model/3DModel.hpp>
#include <H3D/Audio/Audio.hpp>
#include <H3D/Graphics/Program.hpp>
#include <H3D/Graphics/Shader.hpp>
#include <H3D/System/Byte.h>
#include <H3D/Graphics/Vertex.hpp>
#include <H3D/Math/Matrix.hpp>
#include <H3D/System/Mouse.hpp>
#include <H3D/System/Clock.hpp>

#include <gl/GL.h>
#pragma comment(lib,"opengl32.lib")

int main()
{
	h3d::Window app(h3d::Vec2<int>(1500, 750), "Test", h3d::WindowStyle::Default,h3d::ContextSettings());

	h3d::Model3D model;
	model.loadFromFile("C:/Users/Hannes/Downloads/M4A1/M4A1.obj");
	model.logModelData();

	h3d::Shader vert_shader(h3d::Shader::Type::Vertex,"vert_shader.vert");
	h3d::Shader frag_shader(h3d::Shader::Type::Fragment, "frag_shader.frag");

	h3d::Program program;
	program.attachShader(vert_shader);
	program.attachShader(frag_shader);
	program.link();
	program.use();

	h3d::mat4x4 mat_scale = h3d::Math::scale(0.25, 0.25, 0.25);
	program.Uniform.setMatrix4x4(mat_scale, "mat_scale");

	h3d::mat4x4 mat_proj = h3d::Math::projectionMatrix(90,0.0001f,10000.f,15.f/7.5f);
	program.Uniform.setMatrix4x4(mat_scale, "mat_proj");

	h3d::Clock clock;

	while (app.isOpen())
	{
		h3d::Event event;
		while (app.pollEvent(event)) {
			if (event.type == h3d::EventType::Closed)
				app.close();
		}

		app.clear(h3d::Window::BufferBit::Color,h3d::Color<float>(0.6,1.0,0.2,1.0));

		h3d::mat4x4 mat_rotate = h3d::Math::rotate(0,clock.getMilliSeconds()/25,0);
		program.Uniform.setMatrix4x4(mat_rotate, "mat_rotate");

		model.render();
		
		app.swapBuffers();
	}
}