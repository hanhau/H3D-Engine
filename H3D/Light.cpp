#include "Light.hpp"
/////////////////////////////////////////////////////////////////
// Implementations of Light Functions
/////////////////////////////////////////////////////////////////
h3d::Light::Light() {}
h3d::Light::~Light() {}
/////////////////////////////////////////////////////////////////
void h3d::Light::createAmbient(h3d::Color<float>color,
							   float brightness)
{

}
void h3d::Light::createDirectional(h3d::Color<float>color,
								   float brightness,
							       h3d::Vec3<float>direction,
								   float length)
{

}
void h3d::Light::createSpotlight(h3d::Color<float>color,
								 float brightness,
								 h3d::Vec3<float>direction,
								 float length,
								 float outerRadius)
{

}
/////////////////////////////////////////////////////////////////