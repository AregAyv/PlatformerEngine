#include "Character.h"

int ground = 420;
	
	Character::Character(AnimationManager& a):anim(a), x(100), y(600), dx(0),dy(0), W(33), H(39), direction(1),alive(true) {
		State = stay;
	}
	
	void Character::draw_character(sf::RenderWindow& window, std::pair<float, float> offset)
	{
		anim.draw(window, x, y, offset);

		
	}

	void Character::set_character(std::string name) {
		anim.set(name);
	}

	void Character::tick_character(float time) {
		anim.tick(time, direction);
	}
	
	
	void Character::read_keys() {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { key["D"] = true; }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { key["W"] = true; }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { key["A"] = true; }
	}

	

	void Character::Key_check() {
		

		if (key["A"]) {
			dx = -100;
			direction = 1;
			if (State == stay) {
				State = walk;
			}
		}
		if (key["D"]) {
			dx = 100;
			direction = 0;
			if (State == stay ) {
				State = walk;
			}
		}

		if (key["W"] ) {
			if (onGround) {
				dy = -192;

				if (State == stay || State == walk) {
					State = jump;
				}
			}
		}

		if (!(key["D"] || key["A"])) {
			dx = 0;

			if (State == walk) {
				State = stay;
			}
		}

		if (!key["W"]) {
			if (onGround) {
				State = stay;
			}
		}
	
	}

	

	void Character::Collision(std::vector<std::string> TileMap, int dir) {
		
		for (int i = y / 64; i < (y + H) / 64; ++i) {
			for (int j = x / 64; j < (x + W) / 64; ++j) {

				if (TileMap[i][j] == 'B') {
					if (dx > 0 && dir == 0) { x = j * 64 - W; }
					if (dx < 0 && dir == 0) { x = j * 64 + 64; }

					if (dy > 0 && dir == 1) {
						y = i * 64 - H;
						onGround = true;
						dy = 0;


					}
					if (dy < 0 && dir == 1) {
						y = i * 64 + 64;
						dy = 0;
					}
				}
			}
		}

	}

	void Character::update(float time, Map* map) {
		

		if (y > 900) {
			alive = false;
		}

		if (alive) {
			Key_check();
		}
		if (State == walk) { anim.set("walk"); }
		if (State == stay) { anim.set("stay"); }
		if (State == jump) { anim.set("jump"); }

		x += dx * time;
		if (alive) {
			Collision(map->get_map(), 0);
		}

		

		if (!onGround) {
			dy = dy + 200 * time;
		}


		y += dy * time;
		onGround = false;
		
		if (alive) {
			Collision(map->get_map(), 1);
		}

		
		dx = 0;

		anim.tick(time, direction);
		key["W"] = key["A"] = key["D"] = false;

		map->change_offset(x, y);
	}
	
	sf::FloatRect Character::getRect() {
		return sf::FloatRect(x, y, W, H);
	}
	
	float Character::get_Xspeed() {
		return dx;
	}

	float Character::get_Yspeed() {
		return dy;
	}

	bool Character::get_character_state() {
		return alive;
	}

	void Character::change_speed(float x, float y) {
		dx = x;
		dy = y;
		if (dy == 0) {
			onGround = true;
		}
	}

	void Character::change_coords(float dx, float dy) {
		x = dx ;
		y = dy;
		
	}
	std::pair<float, float> Character::get_coords() {
		return {x, y};
	}
	void Character::Hit(float time) {
		if (alive) {
			dx = 0;
			State = jump;
			y += -10 + 100 * time;
			
			
			alive = false;
		}
			
	}