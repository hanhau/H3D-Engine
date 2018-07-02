#include "../../H3D/System/WindowImpl.hpp"
#include "../../H3D/System/Event.hpp"

namespace h3d {
	namespace intern {
		bool WindowImpl::popEvent(h3d::Event &event) {
			if (m_eventList.empty())
			{
				processEvents();
			}
			if (!m_eventList.empty())
			{
				event = m_eventList.front();
				m_eventList.pop_front();

				return true;
			}

			return false;
		}
		void WindowImpl::pushEvent(const h3d::Event& event) {
			m_eventList.push_back(event);
		}
	}
}
