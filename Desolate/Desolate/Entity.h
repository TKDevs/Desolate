#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include "TextureManager.h"

class Entity {
public:
	Entity(sf::RenderWindow* window, TextureManager* tm) {
		mWindow = window;
		mTextureManager = tm;
		mEntityID++;
		std::cout << "Entity Initialized with ID: " << mEntityID << std::endl;
	}

	virtual void update(float deltaTime) {

	}

	virtual void render() {
		mWindow->draw(mSprite);
	}

	// Get / Set Functions

	sf::Vector2f getPosition() {
		return mSprite.getPosition();
	}

	int getID() {
		return mEntityID;
	}

protected:
	TextureManager*		mTextureManager;
	sf::RenderWindow*	mWindow;
	sf::Sprite			mSprite;
	static int mEntityID;
};
int Entity::mEntityID = 0;

#endif