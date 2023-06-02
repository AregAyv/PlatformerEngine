#include "Game.h"

void RunGame() {
	// Create Window
	sf::RenderWindow window(sf::VideoMode(1000, 1000), "World");

	// creat character
	sf::Texture char_texture;
	char_texture.loadFromFile("sprites/smb_mario_sheet.png");
	AnimationManager anim;
	anim.create("stay", char_texture, 520, 0, 33, 39, 1, 5, 0);
	anim.create("walk", char_texture, 593, 0, 40, 39, 5, 0.1, 77);
	anim.create("jump", char_texture, 0, 38, 33, 39, 1, 5, 0);
	Character character(anim);

	//set all enemys and objects textures
	sf::Texture enemy_texture;
	enemy_texture.loadFromFile("sprites/smb_enemies_sheet.png");
	AnimationManager enemy_anim;
	enemy_anim.create("walk", enemy_texture, 0, 10, 48, 50, 2, 1, 88);
	enemy_anim.create("dead", enemy_texture, 178, 22, 48, 25, 1, 1, 0);


	sf::Texture Thwomp_txt;
	Thwomp_txt.loadFromFile("sprites/Thwomp.png");
	AnimationManager Thwomp_anim;
	Thwomp_anim.create("walk", Thwomp_txt, 8, 231, 56, 67, 4, 1, 58);


	sf::Texture jppad;
	jppad.loadFromFile("sprites/jumppad.png");
	AnimationManager jp_anim;
	jp_anim.create(" ", jppad, 0, 0, 84, 62, 1, 0, 0);
	sf::Texture platform_tex;
	platform_tex.loadFromFile("sprites/platform.png");
	AnimationManager pl_anim;
	pl_anim.create(" ", platform_tex, 34, 40, 101, 27, 1, 0, 0);
	sf::Texture coin_txt;
	coin_txt.loadFromFile("sprites/coin_texture.png");
	AnimationManager coin_anim;
	coin_anim.create(" ", coin_txt, 0, 0, 48, 55, 1, 1, 1);


	//list of pointers to enemys or objects
	std::list<Entity*> entity;
	entity.push_back(new Mushroom(enemy_anim, 300, 600, 0));
	entity.push_back(new Mushroom(enemy_anim, 3500, 600, 0));
	entity.push_back(new Mushroom(enemy_anim, 4500, 600, 0));
	entity.push_back(new Mushroom(enemy_anim, 5500, 600, 0));
	entity.push_back(new Thwomp(Thwomp_anim, 3000, 572, 0));
	entity.push_back(new jumppad(jp_anim, 300, 600, 84, 62));
	entity.push_back(new jumppad(jp_anim, 720, 600, 84, 62));
	entity.push_back(new jumppad(jp_anim, 3120, 600, 84, 62));
	entity.push_back(new moving_platform(pl_anim, 1000, 500, 101, 27, 50, 0));
	entity.push_back(new Coins(coin_anim, 300, 450, 48, 55));

	Map map;

	sf::Clock clock;


	// Main cycle 
	while (window.isOpen()) {
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();



		//processes events
		sf::Event event;
		while (window.pollEvent(event))
		{
			
			//The user clicked on the "cross" and wants to close the window ?
			if (event.type == sf::Event::Closed) {
				// then close window
				window.close();
			}

		}

		//set default anmation stay
		character.set_character("stay");

		//player movement
		character.read_keys();
		character.update(time, &map);

		for (auto& it : entity) {
			it->update(time, &map);

		}

		for (auto& it : entity) {
			it->player_collisions(character, time);
		}

		window.clear();


		// draw every creature and object
		map.draw_map(window);

		for (auto& it : entity) {
			it->draw(window, map.Get_offset());
		}


		character.draw_character(window, map.Get_offset());
		 
		//Window rendering
		window.display();
	}
}