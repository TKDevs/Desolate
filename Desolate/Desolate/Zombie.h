#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Player.h"

enum ZOMBIETYPE {
	NORMAL,
	SCOUT,
	TANK
};

class Zombie : public Entity {
public:
	Zombie(sf::RenderWindow* window, TextureManager* tM, Player* player, ZOMBIETYPE type) : Entity(window, tM) {
		int variance = rand() % 10 + 1;
		switch (type) {
		case NORMAL:
			mZombieSpeed = 200.0f + variance;
			mZombieDamage = 10.0f;
			mZombieAtkSpd = 1.0f;
			mDetectRange = 500.0f;
			mSprite.setTexture(tM->getTexture("Zombie01"));
			break;
		case SCOUT:
			mZombieSpeed = 275.0f + variance;
			mZombieDamage = 5.0f;
			mZombieAtkSpd = 1.0f;
			mDetectRange = 600.0f;
			mSprite.setTexture(tM->getTexture("Zombie04"));
			break;

		case TANK:
			mZombieSpeed = 100.0f + variance;
			mZombieDamage = 20.0f;
			mZombieAtkSpd = 1.0f;
			mDetectRange = 300.0f;
			mSprite.setTexture(tM->getTexture("Zombie02"));
			break;
		}
		mPlayer = player;
		mSpriteRotation = 0.0f;
		mSprite.setRotation(0.0f);
		mSprite.setOrigin(12.0f, 12.0f);
		mSprite.setScale(sf::Vector2f(3.0f, 3.0f));
		mSprite.setPosition(sf::Vector2f(75.0f, 75.0f));
		mLastSeenPlayer = mSprite.getPosition();
	}

	void update(float deltaTime) {
		if (getDistance(mPlayer->getPosition(), mSprite.getPosition()) <= mDetectRange) {
			moveTo(mPlayer->getPosition(), deltaTime);
			mLastSeenPlayer = mPlayer->getPosition();
		}
		else {
			moveTo(mLastSeenPlayer, deltaTime);
		}
	}
protected:
	float getDistance(sf::Vector2f pos1, sf::Vector2f pos2) {
		return sqrt((pos1.x - pos2.x) * (pos1.x - pos2.x) + (pos1.y - pos2.y) * (pos1.y - pos2.y));
	}

	void moveTo(sf::Vector2f targetPos, float deltaTime) {
		mSpriteRotation = (atan2(mSprite.getPosition().y - targetPos.y, mSprite.getPosition().x - targetPos.x) * 180.0f / 3.14f);
		mSprite.setRotation(mSpriteRotation - 90.0f);
		float movementX = static_cast<float>(cos(3.14 * mSpriteRotation / 180) * mZombieSpeed * deltaTime);
		float movementY = static_cast<float>(sin(3.14 * mSpriteRotation / 180) * mZombieSpeed * deltaTime);
		if (getDistance(mSprite.getPosition(), targetPos) >= 45.0f) {
			mSprite.move(-movementX, -movementY);
		}
		else {
			mSprite.move(0.0f, 0.0f);
		}
	}

	// Zombie Specifications
	float mZombieSpeed;
	float mZombieDamage;
	float mZombieAtkSpd;
	float mSpriteRotation;
	float mDetectRange;
	Player* mPlayer;
	sf::Vector2f mLastSeenPlayer;
};

#endif