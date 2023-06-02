#pragma once
#include <SFML/Graphics.hpp>
#include "Animations.h"
#include "Character.h"
#include <list>
#include "Entity.h"

class Character;
//base object class from with we are going to inheritance
class base_object:public Entity {
public:


	base_object(AnimationManager a, float x, float y, float w, float h);
	void draw(sf::RenderWindow& window, std::pair<float, float> offset);
	sf::FloatRect getRect();
};

//objects classes which inheritance from base_enemy
class jumppad:public base_object {

public:
	jumppad(AnimationManager a, float x, float y, float h, float w);
	void player_collisions(Character& character, float time);
	void update(float time, Map* map);
	
};




class moving_platform :public base_object {
	float dx, dy;
	float timer;
public:
	moving_platform(AnimationManager a, float x, float y, float h, float w, float dx, float dy);
	void update(float time, Map* map);
	void player_collisions(Character& character, float time);
	float get_speedX();
	
};

class Coins :public base_object {
	bool taken;
public:
	Coins(AnimationManager a, float x, float y, float h, float w);
	void draw(sf::RenderWindow& window, std::pair<float, float> offset);
	void player_collisions(Character& character, float time);
	void update(float time, Map* map);
};