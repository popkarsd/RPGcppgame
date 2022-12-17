#include "leveltemplate.h"
#include "settings.h"
#include <fstream>

void Leveltemplate::drawLevel(sf::RenderWindow* window)
{
	for (auto& tile : terrainTiles)
	{

		window->draw(*(tile.getSprite()));
	}
}

std::vector<sf::Sprite*> Leveltemplate::getSolidTiles()
{
	std::vector<sf::Sprite*> tilesref;
	for (auto& tile : terrainTiles)
	{
		if (tile.passable())
		{
			continue;
		}
		tilesref.push_back(tile.getSprite());
	}
	return tilesref;
}

void Leveltemplate::loadlevel(std::string filename)
{
	//load
	//problem is terrainvec resizes, changing memory address
	//also another problem a;lskjdf
	std::ifstream File(filename);
	if (!File)
	{
		std::cerr << "can't open level file" << std::endl;
	}
	for (unsigned y = 0; y < 25; ++y)
	{
		for (unsigned x = 0; x < 38; ++x)
		{
			File >> Data[x][y];

			if (Data[x][y] == 1)
			{

				terrainTiles.push_back(gametile::Gametile("content/dirt.png", sf::Vector2f(x, y), false, false));
			}
		}
	}
}