#pragma once
#include "Terrain/gametile.h"
#include "settings.h"

class Leveltemplate
{
protected:
	std::vector<gametile::Gametile> terrainTiles;
	int Data[38][25];
	//std::vector< enemies::Enemies* > enemiesVect;

	//how to create the actual level?
	//screen size is 1216 by 800, so divide by 32 we get 38 by 25

public:
	void loadlevel(std::string filename);
	void drawLevel(sf::RenderWindow* window);
	std::vector<sf::Sprite*> getSolidTiles();
};