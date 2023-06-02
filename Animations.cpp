#include <SFML/Graphics.hpp>
#include "Animations.h"




	Animation::Animation(sf::Texture& texture, int x, int y, int w, int h, int count, float speed, int step)
	{
		Speed = speed;
		sprite.setTexture(texture);
		
		currentFrame = 0;
		isPlaying = true;
		flip = false;

		for (int i = 0; i < count; i++)
		{
			frames.push_back(sf::IntRect(x + i * step, y, w, h));
			frames_flip.push_back(sf::IntRect(x + i * step + w, y, -w, h));
		}
		
		
	}

	void Animation::tick(float time, bool direction)
	{
		flip = direction;
		if (!isPlaying) return;

		currentFrame +=  Speed * time ;

		if (currentFrame > frames.size()) {
			currentFrame -= frames.size();
		}

		int i = currentFrame;
		sprite.setTextureRect(frames[currentFrame]);
		if (flip) 
		 { 
			sprite.setTextureRect(frames_flip[i]); 
		}

	}







	AnimationManager::AnimationManager()= default;

	
	void AnimationManager::create(std::string name, sf::Texture& texture, int x, int y, int w, int h, int count, float speed, int step)
	{
		animList[name] = Animation(texture, x, y, w, h, count, speed, step);
		currentAnim = name;
	
	}

	

	void AnimationManager::set(std::string name)
	{
		currentAnim = name;
		animList[currentAnim].flip = 0;
	}

	void AnimationManager::draw(sf::RenderWindow& window, int x , int y, std::pair<float, float> offset)
	{
		animList[currentAnim].sprite.setPosition(x - offset.first, y - offset.second);
		window.draw(animList[currentAnim].sprite);
	}

	void AnimationManager::flip(bool b ) { animList[currentAnim].flip = b; }

	void AnimationManager::tick(float time,bool direction) { animList[currentAnim].tick(time, direction); }

	void AnimationManager::pause() { animList[currentAnim].isPlaying = false; }

	void AnimationManager::play() { animList[currentAnim].isPlaying = true; }



	





