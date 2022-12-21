#pragma once

// This class serves as a timer object.
// It's given a certain time and manages a stopwatch around it.
class Timer
{
public:
	// C-tor and d-tor.
	Timer(const float cooldown) : m_cooldown(cooldown), m_timeLeft(0) {}
	~Timer() = default;

	// Updates the time.
	float updateTimer()
	{
		auto delta = m_clock.restart().asSeconds();
		this->m_timeLeft -= delta;
		return delta;
	}

	// Timer management.
	float	getCooldown() const { return m_cooldown; }
	bool	isTimeUp() const { return this->m_timeLeft <= 0; }
	void	updateTimer(const float deltaTime) { m_timeLeft -= deltaTime; }
	void	setCooldown(float newCD) { m_cooldown = newCD; }
	void	setTimer() { this->m_timeLeft = this->m_cooldown; }
	float	getTimeLeft() const { return m_timeLeft; }

private:
	float m_cooldown; // Stores the cooldown.
	sf::Clock m_clock; // For updates.
	float m_timeLeft;
};
