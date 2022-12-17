#pragma once
#include "Terrain/gametile.h"
#include "leveltemplate.h"
#include "settings.h"

class Level1 : public Leveltemplate
{
public:
	Level1();
	std::string filename = "content/LevelData/level1.txt";
};
