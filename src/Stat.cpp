#include "Stat.h"

Stat::Stat(float initVal, float max) // init stat value
	: m_val(initVal) , m_max(max)
{}

bool Stat::handleStat(float amount) //lower stat and check for higher the 0.f
{
	m_val -= amount;
	m_val = std::min(m_val, m_max);
	return (m_val > 0.f);
}
