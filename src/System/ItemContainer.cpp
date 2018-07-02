#include "../../H3D/System/ItemContainer.hpp"

h3d::ItemContainer::ItemContainer(size_t typesize,
								  AllocationSource as) {
	m_as = as;
	if (m_as == AllocationSource::Global) {

	}
	else {

	}
}

h3d::ItemContainer::~ItemContainer() {
	if (m_as == AllocationSource::Global) {
		
	}
	else {

	}
}

h3d::ItemID h3d::ItemContainer::add(void* item) {
	return h3d::ItemID();
}
bool h3d::ItemContainer::del(h3d::ItemID id) {
	return true;
}

void* h3d::ItemContainer::get(h3d::ItemID id) const {
	return 0;
}
void* h3d::ItemContainer::pop(h3d::ItemID id) {
	return 0;
}