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

#include <iostream>
#include <vector>

#include <H3D\Color.hpp>

#include <H3D\hashing\SHA256.hpp>

template <class T>
struct Mallocator {
	typedef T value_type;

	Mallocator() = default;

	template <class U> constexpr Mallocator(const Mallocator<U>&) noexcept {}

	T* allocate(std::size_t n) {
		if (n > std::size_t(-1) / sizeof(T)) throw std::bad_alloc();
		if (auto p = static_cast<T*>(std::malloc(n * sizeof(T)))) return p;
		throw std::bad_alloc();
	}

	void deallocate(T* p, std::size_t) noexcept { std::free(p); }
};
template <class T, class U>
bool operator==(const Mallocator<T>&, const Mallocator<U>&) { return true; }
template <class T, class U>
bool operator!=(const Mallocator<T>&, const Mallocator<U>&) { return false; }

std::vector<int, Mallocator<int>> a;

#include <H3D\memmng\memory.hpp>

int main()
{	
	h3d::DebugMode = true;

	h3d::GlobalAllocator::allocate(100000);
	h3d::GlobalAllocator::deallocate();

	a.push_back(1);
	a.size();

	h3d::DebugMode = true;

	h3d::Window app(h3d::Vec2<int>(1280,720),
					"Test",
					h3d::WindowStyle::Default,
					h3d::ContextSettings(0,0,0,0));


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
	
	glViewport(0, 0, 1920, 1080);

	GLfloat polygons[] = { 1.0f,0.2f,0.7f,
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

	std::cout << "test" << std::endl;

	h3d::Clock clock;

	while (app.isOpen())
	{
		clock.reset();
		h3d::Event event;

		while(app.pollEvent(event))
		{
			if (event.type == h3d::EventType::Closed) {
				app.close();
				return 0;
			}
		}		
		
		app.clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT,
				  h3d::Color<GLfloat>(1.0,0.5,0.25,1.0));
		
		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		glDrawArrays(GL_LINE_LOOP, 0, 9);

		app.swapBuffers();

		std::cout << (double)1 / clock.getSeconds() << "\n";
	}

	return 0;
}
