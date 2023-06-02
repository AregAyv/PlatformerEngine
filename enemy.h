#pragma once
#include <SFML/Graphics.hpp>
#include "Animations.h"
#include <list>
#include "map.h"
#include "Character.h"
#include "Entity.h"


class Character;
class Map;
//base enemy class from with we are going to inheritance
class base_enemy:public Entity {
public:
	
	float timer;
	enum { walk, dead } State;
	bool alive;

	base_enemy(AnimationManager a, float x, float y, float dX, float dY, float H, float W, bool dir);
	
	
	void draw_enemy(sf::RenderWindow& window, std::pair<float, float> offset);
    void set_enemy(std::string name);
	void kill();
	sf::FloatRect getRect();
};

//enemy classes which inheritance from base_enemy
class Mushroom:public base_enemy {

public:
	
	Mushroom(AnimationManager a, int x, int y, bool dir);
	void update(float time, Map* map);
	void player_collisions(Character& character, float time);
	
	
};


class Thwomp :public base_enemy {
	bool waiting;
public:
	Thwomp(AnimationManager a, int x, int y, bool dir);
	void update(float time, Map *map);
	void player_collisions(Character& character, float time);
};






