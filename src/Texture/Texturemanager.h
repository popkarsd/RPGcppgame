#pragma once
#include "settings.h"
#include <algorithm>
#include <filesystem>
#include <map>

namespace texture

{
class Texturemanager
{
protected:
	std::map<std::string, sf::Texture*> textures;
	std::string textureFolderPath;

public:
	Texturemanager(); //adds all textures in "content" folder
	~Texturemanager();
	int getSize();
	void addTexture(); //adds a specific textuer
	sf::Texture* getTexture(std::string);
	void deleteTexture();
};

}