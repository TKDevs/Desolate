#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

class TextureManager
{
public:
	TextureManager() {

	}
	void addTexture(std::string textureID, std::string fileLocation)
	{
		sf::Texture tex;
		tex.loadFromFile(fileLocation);
		this->Textures[textureID] = tex;
		return;
	}
	void removeTexture(std::string textureID)
	{
		Textures.erase(textureID);
	}
	sf::Texture& getTexture(std::string textureID)
	{
		return Textures.at(textureID);
	}
private:
	std::map<std::string, sf::Texture> Textures;
};

#endif