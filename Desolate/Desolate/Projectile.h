/*#ifndef PROJECTILE_H
#define PROJECTILEH

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#include "Player.h"
#include "TextureManager.h"

class Projectile {
public:
	/*
		Projectile Class Needs atleast:
			- Window pointer
			- TextureManager pointer
			- Texture Name
			- Start Position
			- Start Rotation
			- Start Speed
			- Start Damage
			- Start Decay Time
	/

	Projectile(sf::RenderWindow window, TextureManager* textureManager, sf::Vector2f startPos, float rotation, float speed, float damage, float decayTime) {
		mWindow = window;
		mTextureManager = textureManager;
		mSprite.setPosition(startPos);
		mSprite.setRotation(rotation_);

	}

	void update() {

	}

	void render() {

	}

	sf::Sprite* getSprite() {
		return &mSprite;
	}
private:
	sf::RenderWindow*    mWindow;
	TextureManager*        mTextureManager;
	sf::Sprite            mSprite;

	float    mProjectileSpeed,
			mProjectileDamage,
			mProjectileDecayTime;
	bool    mIsDecayed;
};

#endif*/