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
	model.loadFromFile("C:/Users/hanne/Downloads/M4A1/ak47.obj");
	model.logModelData();

	h3d::Shader vert_shader(h3d::Shader::Type::Vertex,"vert_shader.vert");
	h3d::Shader frag_shader(h3d::Shader::Type::Fragment, "frag_shader.frag");

	h3d::Program program;
	program.attachShader(vert_shader);
	program.attachShader(frag_shader);
	program.link();
	program.use();

	h3d::mat4x4 mat_scale = h3d::Math::scale(0.8, 0.8, 0.8);
	program.Uniform.setMatrix4x4(mat_scale, "mat_scale");

	h3d::mat4x4 mat_proj = h3d::Math::projectionMatrix(95.f,0.0001f,10000.f,1500.f/750.f);
	program.Uniform.setMatrix4x4(mat_scale, "mat_proj");

	h3d::Clock clock;

	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	while (app.isOpen())
	{
		h3d::Event event;
		while (app.pollEvent(event)) {
			if (event.type == h3d::EventType::Closed)
				app.close();
		}

		app.clear(h3d::Window::BufferBit::Color | h3d::Window::BufferBit::Depth,
				  h3d::Color<float>(0.6,1.0,0.2,1.0));

		h3d::mat4x4 mat_rotate = h3d::Math::rotate(-35,45,3);
		program.Uniform.setMatrix4x4(mat_rotate, "mat_rotate");

		program.Uniform.setUniform3f(h3d::Vec3<float>(sinf(clock.getSeconds()),10.f,cosf(clock.getSeconds())), "lightPos");

		model.render();
		
		app.swapBuffers();
	}
}