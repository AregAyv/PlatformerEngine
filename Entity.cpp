#include "Entity.h"
//class from who we are going to inheritance "base_enemy and base_object"
Entity::Entity(AnimationManager a, float x, float y, float dX, float dY, float H, float W):anim(a), x(x),y(y), dx(dX), dy(dY), H(H), W(W), direction(1) {}

void Entity::draw(sf::RenderWindow& window, std::pair<float, float> offset) {
	anim.draw(window, x, y, offset);
}



void Entity::set(std::string name) {
	anim.set(name);
}

void Entity::tick(float time) {
	anim.tick(time, direction);
}

sf::FloatRect Entity::getRect() {
	return sf::FloatRect(x, y, W, H);
}