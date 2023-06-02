#pragma once
#include "Animations.h"



class Map;
class Character;

class Entity {
public:
	float x, y, dx, dy, W, H;
	AnimationManager anim;
	int direction;

	Entity(AnimationManager a, float x, float y, float dX, float dY, float W, float H );
	virtual void draw(sf::RenderWindow& window, std::pair<float, float> offset);
	virtual void update(float time, Map* map) = 0;
	virtual void player_collisions(Character& character, float time) = 0;
	void set(std::string name);
	void tick(float time);
	sf::FloatRect getRect();

};