#ifndef PLAYER_H
#define PLAYER_H

#include <deque>
#include "Entity.h"
#include "TextureManager.h"
#include "Projectile.h"

class Player : public Entity {
public:
	Player(sf::RenderWindow* window, TextureManager* tM) : Entity(window, tM) {
		mMoveUp = false;
		mMoveDown = false;
		mMoveLeft = false;
		mMoveRight = false;
		mSprintingSpeed = 350.0f;
		mNormalSpeed = 250.0f;
		mSpriteSpeed = mNormalSpeed;
		mSpriteRotation = 0.0f;

		mSprite.setTexture(tM->getTexture("Human01"));
		mSprite.setOrigin(12.0f, 12.0f);
		mSprite.setScale(sf::Vector2f(3.0f, 3.0f));
		mSprite.setPosition(sf::Vector2f(640, 480));
		mSprite.setRotation(mSpriteRotation);
	}

	void update(float deltaTime) {
		(mSprinting) ? mSpriteSpeed = mSprintingSpeed : mSpriteSpeed = mNormalSpeed;
		if (mMoveUp)
			mSprite.move(sf::Vector2f(0.0f, -mSpriteSpeed * deltaTime));
		if (mMoveDown)
			mSprite.move(sf::Vector2f(0.0f, mSpriteSpeed * deltaTime));
		if (mMoveLeft)
			mSprite.move(sf::Vector2f(-mSpriteSpeed * deltaTime, 0.0f));
		if (mMoveRight)
			mSprite.move(sf::Vector2f(mSpriteSpeed * deltaTime, 0.0f));
		mSpriteRotation = (atan2(mSprite.getPosition().y - mWindow->mapPixelToCoords(sf::Mouse::getPosition(*mWindow)).y, (mSprite.getPosition().x - mWindow->mapPixelToCoords(sf::Mouse::getPosition(*mWindow)).x)) * 180.0f / 3.14f);
		mSprite.setRotation(mSpriteRotation - 90.0f);
	}

	void changeDirection(sf::Event event) {
		if (event.type == sf::Event::KeyPressed) {
			switch (event.key.code) {
			case sf::Keyboard::W:
				mMoveUp = true;
				break;
			case sf::Keyboard::A:
				mMoveLeft = true;
				break;
			case sf::Keyboard::S:
				mMoveDown = true;
				break;
			case sf::Keyboard::D:
				mMoveRight = true;
				break;
			case sf::Keyboard::LShift:
				mSprinting = true;
				break;
			default:
				break;
			}
		}

		if (event.type == sf::Event::KeyReleased) {
			switch (event.key.code) {
			case sf::Keyboard::W:
				mMoveUp = false;
				break;
			case sf::Keyboard::A:
				mMoveLeft = false;
				break;
			case sf::Keyboard::S:
				mMoveDown = false;
				break;
			case sf::Keyboard::D:
				mMoveRight = false;
				break;
			case sf::Keyboard::LShift:
				mSprinting = false;
				break;
			default:
				break;
			}
		}
	}
private:
	bool mMoveUp, mMoveDown, mMoveLeft, mMoveRight, mSprinting, mShotGun;
	float mSprintingSpeed, mNormalSpeed, mSpriteSpeed, mSpriteRotation;
};

#endif