#ifndef PAWN_H
#define PAWN_H

#include <iostream>
#include <ctime>
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include <random>

enum PawnState {
	IDLE,
	MOVING,
	ATTACKING
};

class Pawn {
public:
	Pawn(sf::RenderWindow* window, TextureManager* textureManager) : mwindow(window), mtexture_manager(textureManager) {
		random_reaction = (rand() % 5 + 1) / 10.0f;
		mmovement_speed = 160.0f;
		msprite_rotation = 0.0f;
		m_is_selected = false;
		msprite.setPosition(1280 / 2, 960 / 2);
		msprite.setRotation(msprite_rotation);
		msprite.setOrigin(12.0f, 12.0f);
		msprite.setScale(2.0f, 2.0f);
		msprite.setTexture(mtexture_manager->getTexture("Human01"));
		mpawn_state = IDLE;
	}
	void update(float dT) {
		switch (mpawn_state) {
		case IDLE:
			roam(dT);
			break;
		case MOVING:
			moveTo(mTarget, dT, 30.0f);
			break;
		}
	}
	void render() {
		mwindow->draw(msprite);
	}

	PawnState mpawn_state;
	sf::Vector2f mTarget;
private:
	float getDistance(sf::Vector2f pos1, sf::Vector2f pos2) {
		return sqrt((pos1.x - pos2.x) * (pos1.x - pos2.x) + (pos1.y - pos2.y) * (pos1.y - pos2.y));
	}
	void moveTo(sf::Vector2f target, float dT, float buffer) {
		if (getDistance(msprite.getPosition(), target) >= buffer) {
			msprite_rotation = -atan2(msprite.getPosition().x - target.x, msprite.getPosition().y - target.y) * 180 / 3.14;
			msprite.setRotation(msprite_rotation);
			sf::Vector2f movement;
			movement.x = -static_cast<float>(cos(3.14 * (msprite_rotation + 90.0f) / 180) * mmovement_speed * dT);
			movement.y = -static_cast<float>(sin(3.14 * (msprite_rotation + 90.0f) / 180) * mmovement_speed * dT);
			msprite.move(movement);
		}
		else {
			mpawn_state = IDLE;
		}
	}
	void roam(float dT) {
		if (AIActionClock.getElapsedTime().asSeconds() >= 1.0f + random_reaction) {
			random_action = rand() % 10 + 1;
			if (random_action >= 8) {
				msprite_rotation = rand() % 360 + 1;
			}
			AIActionClock.restart();
		}
		if (random_action >= 8) {
			msprite.setRotation(msprite_rotation);
			sf::Vector2f movement(-static_cast<float>(cos(3.14 * (msprite_rotation + 90.0f) / 180) * mmovement_speed * dT), -static_cast<float>(sin(3.14 * (msprite_rotation + 90.0f) / 180) * mmovement_speed * dT));
			msprite.move(movement);
		}
		else {
			msprite.move(0.0f, 0.0f);
		}
	}

	bool m_is_selected;

	sf::Clock AIClock;
	sf::Clock AIActionClock;

	sf::Sprite msprite;

	sf::RenderWindow* mwindow;
	TextureManager* mtexture_manager;

	float mmovement_speed, msprite_rotation;
	float random_action, random_reaction;
};
#endif