#include "map.h"
#include <fstream>

Map::Map() {

	std::ifstream file;
	file.open("Map.txt");

	std::string Line{};
	if (file.is_open()) {
		while (! file.eof() ) {
			getline(file, Line);
			TileMap.push_back(Line);

		}
		file.close();
	}
	else {
		exit(-1);
	}


	H = TileMap.size();
	W = TileMap[0].size();
}
	

void Map::draw_map(sf::RenderWindow& window) {
	
	sf::RectangleShape rectangle(sf::Vector2f(64, 64));
	

	for (int i = 0; i < H ; ++i) {
		for (int j = 0; j < W ; ++j) {
			if (TileMap[i][j] == 'B') { rectangle.setFillColor(sf::Color::White); }
			
			if (TileMap[i][j] == 'G') { rectangle.setFillColor(sf::Color::Green); }
			
			if (TileMap[i][j] == ' ') { continue; }

			rectangle.setPosition(j * 64 - offsetX, i * 64 - offsetY);
			window.draw(rectangle);
		}
	}
	
}
	
std::vector<std::string> &Map::get_map() {
	return TileMap;
}

std::pair<float, float> Map::Get_offset() {
	return { offsetX, offsetY };
}

void Map::change_offset(float x, float y) {
	offsetX = x - 1000 / 2;
	offsetY = y - 1000 / 2;
}