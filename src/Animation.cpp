#include "Animation.h"

// Constructor.
Animation::Animation(const sf::Texture* texture, AnimationParams animParms)
	:	m_imageCount(animParms._imageCount), m_switchTime(animParms._switchTime), 
		m_totalTime(0.0f), m_row(0), m_faceRight(true)
{
	this->m_currentImage.x = 0;
	this->uvRect.width = texture->getSize().x / float(animParms._imageCount.x);
	this->uvRect.height = texture->getSize().y / float(animParms._imageCount.y);
	for (size_t i = 0; i < m_imageCount.y; i++)
		m_rowLens.push_back(m_imageCount.x);

}

Animation::Animation(const sf::Texture* texture, AnimationParams animParms, std::vector<int> lengths)
	:Animation(texture,animParms)
{
	m_rowLens=lengths;
}


// Updates the animation.
bool Animation::update(float deltaTime)
{
	auto eor = false; // end of row check
	this->m_currentImage.y = this->m_row;
	this->m_totalTime += deltaTime;

	if (this->m_totalTime >= this->m_switchTime)
	{
		this->m_totalTime -= this->m_switchTime;
		this->m_currentImage.x++;

		if (this->m_currentImage.x >= this->m_rowLens[m_currentImage.y])
		{
			this->m_currentImage.x = 0;
			eor = true;
		}
	}

	this->uvRect.top = this->m_currentImage.y * this->uvRect.height;

	if (this->m_faceRight)
	{
		this->uvRect.left = this->m_currentImage.x * this->uvRect.width;
		this->uvRect.width = abs(this->uvRect.width);
	}
	else
	{
		this->uvRect.left = (m_currentImage.x + 1) * abs(this->uvRect.width);
		this->uvRect.width = -abs(this->uvRect.width);
	}

	return eor;
}

//===================================================

void Animation::setRow(int index)
{ 
	if(m_row != index) // each time we set a new animation row - set to first picture
		this->m_currentImage.x = 0; 
	this->m_row = index; 
}
