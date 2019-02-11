#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <iostream>
#include <SFML/Graphics.hpp>

class TextureManager {
public:
	TextureManager() {

	}
	void addTexture(std::string texture_ID, std::string file_location)
	{
		sf::Texture tex;
		tex.loadFromFile(file_location);
		this->textures_[texture_ID] = tex;
		return;
	}
	void removeTexture(std::string texture_ID)
	{
		textures_.erase(texture_ID);
	}
	sf::Texture& getTexture(std::string texture_ID)
	{
		return textures_.at(texture_ID);
	}
private:
	std::map<std::string, sf::Texture> textures_;
};

#endif