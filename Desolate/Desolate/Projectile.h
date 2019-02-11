#ifndef PROJECTILE_H
#define PROJECTILEH

#include <iostream>
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "Entity.h"

struct BulletSpecs {
	float bulletRotation;
	float bulletSpeed;
	float bulletDamage;
	float bulletDecayTime;
	std::string bulletSpriteName;
};

class Projectile : public Entity {
public:
	Projectile(sf::RenderWindow* window, TextureManager* tm, sf::Vector2f startpos, BulletSpecs specs) : Entity(window, tm) {
		mProjectileSpecs = specs;

		mWindow = window;
		mTextureManager = tm;
		mSprite.setPosition(startpos);
		mSprite.setRotation(mProjectileSpecs.bulletRotation);
		mSprite.setTexture(mTextureManager->getTexture(mProjectileSpecs.bulletSpriteName));
		mSprite.scale(2.0f, 2.0f);
		mIsDecayed = false;
	}

	void update(float deltaTime) {
		if (mProjectileClock.getElapsedTime().asSeconds() > mProjectileSpecs.bulletDecayTime) {
			mIsDecayed = true;
		}
		else {
			sf::Vector2f bulletMovement(static_cast<float>(cos(3.14 *  mSprite.getRotation() / 180) * mProjectileSpecs.bulletSpeed) * deltaTime, static_cast<float>(sin(3.14 * mSprite.getRotation() / 180) * mProjectileSpecs.bulletSpeed) * deltaTime);
			mSprite.move(-bulletMovement);
		}
	}

	void render() {
		if (!mIsDecayed)
			mWindow->draw(mSprite);
	}

	sf::Sprite* getSprite() {
		return &mSprite;
	}

	bool isDecayed() {
		return mIsDecayed;
	}
private:
	sf::RenderWindow*   mWindow;
	TextureManager*		mTextureManager;
	sf::Clock			mProjectileClock;
	BulletSpecs			mProjectileSpecs;
	bool    mIsDecayed;
};

#endif