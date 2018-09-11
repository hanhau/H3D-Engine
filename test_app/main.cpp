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
#include <H3D/Math/Math.hpp>

#include <gl/GL.h>
#include <any>
#pragma comment(lib,"opengl32.lib")

int main()
{
	h3d::ModelConverter::convert("C:/Users/Hannes/Downloads/M4A1/M4A1.obj", "demo.mh3d");

	std::any a;
	a = 12;
	a = "12";
	a = 12.f;

	h3d::mat4x4 mat1;
	h3d::mat4x4 mat2;
	h3d::mat4x4 mat3 = mat1 * mat2;

	h3d::Math::Triangle tri;
	tri.m_pos[0] = h3d::Vec3<float>(0.0, 0.0, 0.0);
	tri.m_pos[1] = h3d::Vec3<float>(1.0, 1.0, 0.0);
	tri.m_pos[2] = h3d::Vec3<float>(1.0, 0.0, 0.0);

	h3d::Math::Ray ray;
	ray.m_pos = h3d::Vec3<float>(0.1, 0.1, 1.0);
	ray.m_target = h3d::Vec3<float>(0.1, 0.1, 0.5);

	h3d::Vec3<float> aaaaaa;
	std::cout << h3d::Math::intersectRay(ray, tri,aaaaaa);
	std::cout << "\n";

	h3d::Window app(h3d::Vec2<int>(900, 900), "Test", h3d::WindowStyle::Default,h3d::ContextSettings());

	h3d::Audio::initialize();

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

	h3d::mat4x4 mat_scale = h3d::Math::scale(0.20, 0.20, 0.20);
	program.Uniform.setMatrix4x4(mat_scale, "mat_scale");

	h3d::mat4x4 mat_proj = h3d::Math::projectionMatrix(95.f,0.0001f,10000.f,1.f);
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
			if (event.type == h3d::EventType::Closed) {
				app.close();
			}
			if (event.type == h3d::EventType::KeyDown) {
				std::cout << "lol\n";
			}
		}

		app.clear(h3d::Window::BufferBit::Color | h3d::Window::BufferBit::Depth,
				  h3d::Color<float>(0.6,1.0,0.2,1.0));

		const float x = h3d::Mouse::getPosition().x;
		const float y = h3d::Mouse::getPosition().y;

		h3d::mat4x4 mat_rotate = h3d::Math::rotate(y, x, 0);
		program.Uniform.setMatrix4x4(mat_rotate, "mat_rotate");

		program.Uniform.setUniform3f(h3d::Vec3<float>(5.f,10.f,7.f), "lightPos");

		model.render();
		
		app.swapBuffers();
	}
}