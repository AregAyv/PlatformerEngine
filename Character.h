#pragma once
#include <SFML/Graphics.hpp>
#include "Animations.h"
#include "map.h"


class Map;
class Entity;

class Character {

	float x, y, dx, dy, W, H;
	AnimationManager anim;
	int direction;
	
	bool onGround;
	bool alive;
	
	enum { walk, stay,jump } State;
	std::map<std::string, bool> key;

public:

	Character (AnimationManager& a);
	void draw_character(sf::RenderWindow& window, std::pair<float, float> offset);
	//sets charaacters State
	void set_character(std::string name);
	
	void tick_character(float time);

	void read_keys();
	void Key_check();
	//player map collisions check
	void Collision(std::vector<std::string> TileMap, int dir);
	void update(float time, Map* map);
	
	//helping functions
	sf::FloatRect getRect();
	float get_Xspeed();
	float get_Yspeed();
	bool get_character_state();
	std::pair<float, float> get_coords();
	void change_speed(float x, float y);
	void change_coords(float dx, float dy);
	
	//if characters get hit
	void Hit(float time);
};