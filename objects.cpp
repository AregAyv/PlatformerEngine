#include "objects.h"

base_object::base_object(AnimationManager a, float x, float y, float h, float w) :Entity(a,x,y,0,0,h,w) {}

void base_object::draw(sf::RenderWindow& window, std::pair<float, float> offset) {
	anim.draw(window, x, y, offset);
}

sf::FloatRect base_object::getRect() {
	return sf::FloatRect(x, y, W, H);
}

jumppad::jumppad(AnimationManager a, float x, float y, float w, float h) :base_object(a, x, y, h, w){}

moving_platform::moving_platform(AnimationManager a, float x, float y, float w, float h, float dx, float dy) :base_object(a, x, y, h, w), dx(dx), dy(dy),timer(0) {}

void jumppad::update(float time, Map* map) {
	anim.tick(time, 0);
}

void moving_platform::moving_platform::update(float time, Map* map) {

	
		x += dx * time;
		y += dy * time;

		timer += time;
		if (timer > 4) {
			dx *= -1;
			dy *= -1;
			timer = 0;
		}
		anim.tick(time, 0);
	}

float moving_platform::get_speedX() {
	return dx;
}


void jumppad::player_collisions(Character& character, float time) {
	if (character.getRect().intersects(getRect())) {
		if (character.get_Yspeed() != 0) {
			character.change_speed(character.get_Xspeed(), -300);
		}
		else { character.change_speed(0, 0); }
	}
}


void moving_platform::player_collisions(Character& character, float time) {
	
		if (character.getRect().intersects(getRect())) {
			if(character.get_Yspeed() > 0) {
				if (character.get_coords().second + 39 < y + H) {
					character.change_speed(character.get_Xspeed() , 0);
					character.change_coords(character.get_coords().first , y - 39 );
					
				}
				
			}
		}
	
}


Coins::Coins(AnimationManager a, float x, float y, float w, float h):base_object(a, x, y, h, w), taken(false){}

void Coins::update(float time, Map* map) {
	anim.tick(time, 0);
}

void Coins::player_collisions(Character& character, float time) {
	if (character.getRect().intersects(getRect())) {
		if (!taken) {
			taken = true;
		}
	}
}

void Coins::draw(sf::RenderWindow& window, std::pair<float, float> offset) {
	if (!taken) {
		anim.draw(window, x, y, offset);
	}
}