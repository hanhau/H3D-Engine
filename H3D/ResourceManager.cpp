#include "ResourceManager.hpp"
#include <iostream>
#include <random>
#include <climits>
#include <algorithm>
/////////////////////////////////////////////////////////////////
//  Implementation for ResourceHashID
/////////////////////////////////////////////////////////////////
h3d::ResourceHashID::ResourceHashID() {}
h3d::ResourceHashID::~ResourceHashID() {}
/////////////////////////////////////////////////////////////////
uint32_t h3d::ResourceHashID::getID() { return m_ID; }
uint32_t h3d::ResourceHashID::calcHashID(unsigned char* data, size_t size)
{
	unsigned int byte, mask;

	uint32_t m_ID = 0xFFFFFFFF;
	for (unsigned int i=0;i<size;i++)
	{
		byte = data[i];            // Get next byte.
		m_ID = m_ID ^ byte;
		for (int j = 7; j >= 0; j--) {    // Do eight times.
			mask = -(m_ID & 1);
			m_ID = (m_ID >> 1) ^ (0xEDB88320 & mask);
		}
		i = i + 1;
	}
	return ~m_ID;
}
/////////////////////////////////////////////////////////////////
//	Implementation for ResourceManager
/////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////
