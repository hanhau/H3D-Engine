#ifdef _linux_
#include <chrono>

class h3d::Clock::ClockImpl {
public:
	std::chrono::high_resolution_clock m_clock;
	ClockImpl() {
		
	}
};

h3d::Clock::Clock()
{
	m_impl = std::make_unique<auto>(new h3d::Clock::ClockImpl);
}
h3d::Clock::~Clock() {}
/////////////////////////////////////////////////////////////////
// Clock Value returnings
double h3d::Clock::getSeconds()
{

}
double h3d::Clock::getMilliSeconds()
{

}
double h3d::Clock::getMicroSeconds()
{

}
h3d::Time h3d::Clock::getTime()
{

}
/////////////////////////////////////////////////////////////////
uint64_t h3d::Clock::getPastCycles() {
	return 0;
}
uint64_t h3d::Clock::getFrequency() {
	return 0;
}
/////////////////////////////////////////////////////////////////
//	Update Clock (Time)
void h3d::Clock::reset() {
	m_actualTick = m_impl.get()->m_clock.now();
	return m_actualTick;
}
/////////////////////////////////////////////////////////////////

#endif