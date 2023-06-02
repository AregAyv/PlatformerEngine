#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Character.h"
#include "enemy.h"

class Character;

class Map {
	//map size
	int H;
	int W;
	//map
	std::vector<std::string> TileMap;
	//offset to map move with player
	float offsetX{};
	float offsetY{};

  
public:
	Map();
	void draw_map(sf::RenderWindow& window);
	void change_offset(float x, float y);
	//helping functions
	std::vector<std::string> &get_map();
	std::pair<float, float> Get_offset();
	
};