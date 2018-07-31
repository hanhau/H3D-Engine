#include <H3D/System/Window.hpp>
#include <H3D/Graphics/Color.hpp>
#include <H3D/Model/3DModel.hpp>
#include <H3D/Audio/Audio.hpp>
#include <H3D/Graphics/Program.hpp>
#include <H3D/Graphics/Shader.hpp>
#include <H3D/System/Byte.h>
#include <H3D/Graphics/Vertex.hpp>
#include <H3D/Math/Matrix.hpp>

int main()
{
	h3d::Window app(h3d::Vec2<int>(800, 400), "Test", h3d::WindowStyle::Default,h3d::ContextSettings());

	h3d::Model3D model;
	model.loadFromFile("C:/Users/hanne/Desktop/blender objekte/DING.fbx");
	model.logModelData();

	h3d::Shader vert_shader(h3d::Shader::Type::Vertex,"vert_shader.vert");
	h3d::Shader frag_shader(h3d::Shader::Type::Fragment, "frag_shader.frag");

	h3d::Program program;
	program.attachShader(vert_shader);
	program.attachShader(frag_shader);
	program.link();
	program.use();

	h3d::mat4x4 proj_mat = h3d::Math::projectionMatrix(90.f, 0.001f, 10000.f, 8.f / 4.f);
	program.Uniform.setMatrix4x4(proj_mat, program.Uniform.getLocation("proj_mat"));

	while (app.isOpen())
	{
		h3d::Event event;
		while (app.pollEvent(event)) {
			if (event.type == h3d::EventType::Closed)
				app.close();
		}
		app.clear(h3d::Window::BufferBit::Color,h3d::Color<float>(0.6,1.0,0.2,1.0));

		model.render();

		app.swapBuffers();
	}
}