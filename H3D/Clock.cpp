#include "Clock.hpp"
/////////////////////////////////////////////////////////////////
//	Implementations of Clock Class
/////////////////////////////////////////////////////////////////
h3d::Clock::Clock()
{
	LARGE_INTEGER t;
	QueryPerformanceFrequency(&t);
	m_frequency = *reinterpret_cast<uint64_t*>((void*)&t);
}
h3d::Clock::~Clock() {}
/////////////////////////////////////////////////////////////////
// Clock Value returnings
double h3d::Clock::getSeconds()
{
	static LARGE_INTEGER t;
	QueryPerformanceCounter(&t);
	m_newTick = *reinterpret_cast<uint64_t*>((void*)&t);
	if (m_newTick < m_actualTick)
		m_tickDiff = 0;
	else 
		m_tickDiff = m_newTick - m_actualTick;

	return (double)m_tickDiff/(double)m_frequency;
}
double h3d::Clock::getMilliSeconds()
{
	static LARGE_INTEGER t;
	QueryPerformanceCounter(&t);
	m_newTick = *reinterpret_cast<uint64_t*>((void*)&t);
	if (m_newTick < m_actualTick)
		m_tickDiff = 0;
	else
		m_tickDiff = m_newTick - m_actualTick;

	return (double)m_tickDiff / (double)m_frequency * 1000;
}
double h3d::Clock::getMicroSeconds()
{
	static LARGE_INTEGER t;
	QueryPerformanceCounter(&t);
	m_newTick = *reinterpret_cast<uint64_t*>((void*)&t);
	if (m_newTick < m_actualTick)
		m_tickDiff = 0;
	else
		m_tickDiff = m_newTick - m_actualTick;

	return (double)m_tickDiff / (double)m_frequency * 1000000;
}
h3d::Time h3d::Clock::getTime()
{
	Time temp;
	temp.m_seconds      = getSeconds();
	temp.m_milliseconds = getMilliSeconds();
	temp.m_microseconds = getMicroSeconds();
	return temp;
}
/////////////////////////////////////////////////////////////////
uint64_t h3d::Clock::getPastCycles(){
	return m_actualTick;
}
uint64_t h3d::Clock::getFrequency() {
	return m_frequency;
}
/////////////////////////////////////////////////////////////////
//	Update Clock (Time)
void h3d::Clock::reset() {
	LARGE_INTEGER t;
	QueryPerformanceCounter(&t);
	m_actualTick = *reinterpret_cast<uint64_t*>((void*)&t);
}
/////////////////////////////////////////////////////////////////