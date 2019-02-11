#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include "TextureManager.h"

class Entity {
public:
	Entity(sf::RenderWindow* window, TextureManager* tM) {
		window_ = window;
		tM_ = tM;
		entity_ID_++;
		std::cout << "Entity Initialized with ID: " << entity_ID_ << std::endl;
	}

	virtual void update(float dT) {

	}

	virtual void render() {
		window_->draw(sprite_);
	}

	// Get / Set Functions

	sf::Vector2f getPosition() {
		return sprite_.getPosition();
	}

	int getID() {
		return entity_ID_;
	}

protected:
	TextureManager*		tM_;
	sf::RenderWindow*	window_;
	sf::Sprite			sprite_;
	static int entity_ID_;
};
int Entity::entity_ID_ = 0;

#endif