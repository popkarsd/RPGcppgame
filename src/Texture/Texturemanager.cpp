#include "Texturemanager.h"

using namespace texture;

Texturemanager::Texturemanager()
{
	textureFolderPath = settings::textureFolderPath;
	for (auto const& fp : std::filesystem::directory_iterator(textureFolderPath))
	{
		if (fp.path().extension() == ".png")
		{
			//load png as texture
			sf::Texture* tmp = new sf::Texture();
			if (!tmp->loadFromFile(fp.path()))
			{
				std::cerr << "Unable to load texture " << fp.path().filename() << std::endl;
			}
			else
			{
				std::cerr << "Loaded " << fp.path().filename() << std::endl;
			}
			textures[fp.path().filename()] = tmp;
		}
	}
}
Texturemanager::~Texturemanager()
{
	for (auto& e : textures)
	{
		delete e.second;
		std::cerr << "deleted texture " << e.first << std::endl;
	}
}
int Texturemanager::getSize()
{
	return textures.size();
}
sf::Texture* Texturemanager::getTexture(std::string name)
{
	//change std::string to stringview - instead of heap use stack
	if (textures[name] == nullptr)
	{
		std::cerr << "texture " << name << "is unable to be reached" << std::endl;
		return nullptr;
	}
	return textures[name];
}