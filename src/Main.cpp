#include "Entities/entity.h"
#include "Entities/luni.h"
#include "Levels/level1.h"
#include "Levels/leveltemplate.h"
#include "Platform/Platform.hpp"
#include "Terrain/gametile.h"
#include "settings.h"

int main()
{
	util::Platform platform;

#if defined(_DEBUG)
	std::cout << "Hello World!" << std::endl;
#endif

	sf::RenderWindow window;
	// in Windows at least, this must be called before creating the window
	float screenScalingFactor = platform.getScreenScalingFactor(window.getSystemHandle());
	// Use the screenScalingFactor
	window.create(sf::VideoMode(settings::screen_width * screenScalingFactor,
					  settings::screen_height * screenScalingFactor),
		"platform");

	platform.setIcon(window.getSystemHandle());

	objects::Luni mc;
	sf::Texture luniTexture;
	if (!luniTexture.loadFromFile("content/luni.png"))
	{
		std::cerr << "can't get main character texture" << std::endl;
		return 0;
	}
	mc.set_texture(luniTexture);
	Level1 lvl1;
	lvl1.loadlevel(lvl1.filename);
	window.setFramerateLimit(60);
	std::vector<sf::Sprite*> objects;
	objects = lvl1.getSolidTiles();
	sf::Event event;

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				mc.horizontal_sm(event.key.code, true);
				mc.vertical_sm(event.key.code, true);
			}
			if (event.type == sf::Event::KeyReleased)
			{
				mc.horizontal_sm(event.key.code, false);
				mc.vertical_sm(event.key.code, false);
			}
		}

		//updates
		mc.update(objects);
		//std::cout << mc.getvel().x << " " << mc.getvel().y << std::endl;

		//draw to screen
		window.clear(settings::bg_col);

		lvl1.drawLevel(&window);
		window.draw(*mc.get_sprite());
		window.display();
	}

	return 0;
}
