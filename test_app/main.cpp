#include <H3D/System/Window.hpp>

int main()
{
	h3d::Window app(h3d::Vec2<int>(800, 600), "Test", h3d::WindowStyle::Default,h3d::ContextSettings());
	while (app.isOpen())
	{
		h3d::Event event;
		while (app.pollEvent(event)) {
			if (event.type == h3d::EventType::Closed)
				app.close();

			
		}
	}
}