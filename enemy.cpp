#include "enemy.h"



base_enemy::base_enemy(AnimationManager a, float x, float y, float dX, float dY, float H, float W, bool dir) :Entity(a,x,y,dX,dY,H,W), alive(true), State(walk),timer(0){}


Mushroom::Mushroom(AnimationManager a, int x, int y, bool dir) :base_enemy(a, x, y, 45, 0, 39, 40, 0){}


void base_enemy::draw_enemy(sf::RenderWindow& window, std::pair<float, float> offset) {
	anim.draw(window, x, y, offset);
}

void base_enemy::set_enemy(std::string name) {
	anim.set(name);
}


void Mushroom::update(float time, Map*map) {
	if (State == walk) { anim.set("walk"); }
	if (State == dead || dx == 0) { 
		anim.set("dead"); 
	}

	std::vector<std::string> TileMap = map->get_map();
	x += dx * time;
	
	for (std::size_t i = y / 64; i < (y + H) / 64; ++i) {
		for (std::size_t j = x / 64; j < (x + W) / 64; ++j) {
			if (TileMap[i][j] == 'B' || TileMap[i + 1][j] == ' ') {
				dx *= -1;
				dy = 0;
				timer = 0;
			}
		}
	}

	
	timer += time;
	if (timer > 10) { dx *= -1; timer = 0; }
	
	anim.tick(time, 0);
}

sf::FloatRect base_enemy::getRect() {
	return sf::FloatRect(x, y, W, H);
}

void base_enemy::kill() {
	if (dx != 0) {
		y += 20;
	}
	alive = false;
	dx = 0;
	State = dead;
}


Thwomp::Thwomp(AnimationManager a, int x, int y, bool dir):base_enemy(a, x, y, 0, -56, 67, 23, 0) {
	waiting = true;
	State = walk;
}

void Thwomp::update(float time,Map* map) {

	if (!waiting) {
		y += dy * time;
		
		timer += time;
		if (timer > 3) {
			waiting = true;
			timer = 0;
		}
	}

	std::vector<std::string> TileMap = map->get_map();
	for (std::size_t i = y / 64; i < (y + H) / 64; ++i) {
		for (std::size_t j = x / 64; j < (x + W) / 64; ++j) {
			if (TileMap[i][j] == 'B') {
				if (!waiting) {
					waiting = true;
				}
				
			}
		}
	}

		
	if (waiting) {
		timer += time;
		if (timer > 5) {
			waiting = false;
			timer = 0;
			dy *= -1;
		}
	}

	anim.tick(time, 0);
}





void Mushroom::player_collisions(Character& character, float time) {
	if (character.getRect().intersects(getRect())) {
		if (alive) {
			if (character.get_Yspeed() > 0 && character.get_character_state()) {
				kill();
				character.change_speed(character.get_Xspeed(), -256);

			}
			else {
				character.Hit(time);
			}
		}
	}
}

void Thwomp::player_collisions(Character& character, float time) {
	if (character.getRect().intersects(getRect())) {
		if (alive) {
			character.Hit(time);
		}
	}
}


