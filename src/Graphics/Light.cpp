#include "../../H3D/Graphics/Light.hpp"
/////////////////////////////////////////////////////////////////
// Implementations of Light Functions
/////////////////////////////////////////////////////////////////
h3d::Light::Light() {}
h3d::Light::~Light() {}
/////////////////////////////////////////////////////////////////
void h3d::Light::setType(h3d::Light::Type type) {
	m_type = type;
}
void h3d::Light::setTag(h3d::Light::Tag tag) {
	m_tag = tag;
}
/////////////////////////////////////////////////////////////////
void h3d::Light::createAmbient(h3d::Color<float>color,
							   float brightness)
{
	m_lightData.ambient = {
		color,brightness
	};
}

void h3d::Light::createDirectional(h3d::Color<float>color,
								   float brightness,
							       h3d::Vec3<float>direction,
								   float length)
{
	m_lightData.directional = { 
		color,brightness,direction,length
	};
}

void h3d::Light::createSpotlight(h3d::Color<float>color,
								 float brightness,
								 h3d::Vec3<float>direction,
								 float length,
								 float outerRadius)
{
	m_lightData.spot = {
		color,brightness,direction,length,outerRadius
	};
}

void h3d::Light::createPoint(h3d::Color<float>color,
							 float brightness)
{
	m_lightData.point = {
		color,brightness
	};
}
/////////////////////////////////////////////////////////////////