#pragma once
#include "Utilities.hpp"
#include "Vector.hpp"

namespace h3d {
	enum class WindowStyle;
	class ContextSettings;
	namespace intern {
		class WindowImpl : Uncopyable
		{
		protected:
			h3d::Vec2<int> m_Size;
			std::string    m_Title;
			bool           m_isFullscreen;


		public:
			virtual ~WindowImpl() {}

			virtual void create(h3d::Vec2<int>size, std::string title,
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
		};
	}
}
