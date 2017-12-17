#pragma once
#include "Utilities.hpp"
#include "Vector.hpp"
#include "Event.hpp"
#include <list>

namespace h3d {
	enum class WindowStyle;
	struct ContextSettings;

	namespace intern {
		class WindowImpl : Uncopyable
		{
		protected:
			h3d::Vec2<int> m_Size;
			std::string    m_Title;
			bool           m_isFullscreen;
			
			std::list<Event> m_eventList;

		public:
			virtual ~WindowImpl() {}

			virtual bool create(h3d::Vec2<int>size, std::string title,
							    h3d::WindowStyle ws, h3d::ContextSettings cs) = 0;

			// Virtual Interface
			virtual void setSize(h3d::Vec2<int> param) = 0;
			virtual void resize() = 0;
			virtual void setTitle(std::string param) = 0;
			virtual void setFullscreen(bool param) = 0;
			virtual void setVSync(bool param) = 0;
			virtual void setActive(bool val) = 0;
			virtual void swapBuffers() = 0;
			virtual void allowResize(bool val) = 0;
			virtual void showCursor(bool val) = 0;
			virtual void close() = 0;
			virtual bool isOpen() = 0;

			virtual void processEvents() = 0;

			bool popEvent(h3d::Event &event);
			void pushEvent(const h3d::Event& event);
		};
	}
}
