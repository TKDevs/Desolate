#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <SFML/Graphics.hpp>

#include "TextureManager.h"

class Player {
public:
	Player(sf::RenderWindow* window, TextureManager* tM) : m_window(window), mTM(tM) {
		mmove_up = false, mmove_down = false, mmove_left = false, mmove_right = false;
		m_movement_speed = 250.0f;
		msprinting_speed = 450.0f;
		msprite_speed = m_movement_speed;
		mplayer_rotation = 0.0f;

		msprite.setTexture(mTM->getTexture("Human01"));
		msprite.setOrigin(12.0f, 12.0f);
		msprite.setScale(sf::Vector2f(4.0f, 4.0f));
		msprite.setPosition(sf::Vector2f(640, 480));
		msprite.setRotation(mplayer_rotation);
	}

	void update(float deltaTime) {
		// Movement Code:
		(msprinting) ? msprite_speed = msprinting_speed : msprite_speed = m_movement_speed;

		if (mmove_up)
			msprite.move(sf::Vector2f(0.0f, -msprite_speed * deltaTime));
		if (mmove_down)
			msprite.move(sf::Vector2f(0.0f, msprite_speed * deltaTime));
		if (mmove_left)
			msprite.move(sf::Vector2f(-msprite_speed * deltaTime, 0.0f));
		if (mmove_right)
			msprite.move(sf::Vector2f(msprite_speed * deltaTime, 0.0f));
		// End of Movement Code

		// Sprite Rotation Code:
		mplayer_rotation = (atan2(msprite.getPosition().y - sf::Mouse::getPosition(*m_window).y, (msprite.getPosition().x - sf::Mouse::getPosition(*m_window).x)) * 180.0f / 3.14f);
		msprite.setRotation(mplayer_rotation - 90.0f);
		// End of Sprite Rotation Code
	}

	void render() {
		m_window->draw(msprite);
	}

	void changeDirection(sf::Event event) {
		if (event.type == sf::Event::KeyPressed) {
			switch(event.key.code){
			case sf::Keyboard::W:
				mmove_up = true;
				break;
			case sf::Keyboard::A:
				mmove_left = true;
				break;
			case sf::Keyboard::S:
				mmove_down = true;
				break;
			case sf::Keyboard::D:
				mmove_right = true;
				break;
			case sf::Keyboard::LShift:
				msprinting = true;
				break;
			default:
				break;
			}
		}

		if (event.type == sf::Event::KeyReleased) {
			switch (event.key.code) {
			case sf::Keyboard::W:
				mmove_up = false;
				break;
			case sf::Keyboard::A:
				mmove_left = false;
				break;
			case sf::Keyboard::S:
				mmove_down = false;
				break;
			case sf::Keyboard::D:
				mmove_right = false;
				break;
			case sf::Keyboard::LShift:
				msprinting = false;
				break;
			default:
				break;
			}
		}
	}

	bool mmove_up, mmove_down, mmove_left, mmove_right, msprinting;

	sf::Sprite msprite;
private:

	float m_movement_speed, msprinting_speed, msprite_speed;

	float mplayer_rotation;

	sf::RenderWindow* m_window;
	TextureManager* mTM;
};

#endif