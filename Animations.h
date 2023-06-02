#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

//class animetion with wil work with animatin
class Animation
{
public:
	std::vector<sf::IntRect> frames, frames_flip;
	float currentFrame;
	float Speed;
	bool  flip, isPlaying;
	sf::Sprite sprite;
	Animation() = default;
	Animation(sf::Texture& texture, int x, int y, int w, int h, int count, float speed, int step);
	void tick(float time, bool direction);
	
};

//class with stores map of animations
class AnimationManager
{

public:
	std::string currentAnim;
	std::map<std::string, Animation> animList;

	AnimationManager();
	//create animation
	void create(std::string name, sf::Texture& texture, int x, int y, int w, int h, int count, float speed, int step);

	void set(std::string name);

	void draw(sf::RenderWindow& window, int x , int y , std::pair<float, float> offset);

	void flip(bool b = 1);
	//go throw sprite
	void tick(float time, bool direction);

	void pause();

	void play();






};