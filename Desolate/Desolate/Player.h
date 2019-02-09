#ifndef PLAYER_H
#define PLAYER_H

#include <deque>

#include "Projectile.h"
#include "Entity.h"

class Player : public Entity {
public:
	Player(sf::RenderWindow* window, TextureManager* tM) : Entity(window, tM){
		mmove_up = false, mmove_down = false, mmove_left = false, mmove_right = false;
		mmovement_speed = 250.0f;
		msprinting_speed = 450.0f;
		msprite_speed = mmovement_speed;

		msprite.setTexture(mtm->getTexture("Human01"));
		msprite.setOrigin(12.0f, 12.0f);
		msprite.setScale(sf::Vector2f(4.0f, 4.0f));
		msprite.setPosition(sf::Vector2f(640, 480));
		msprite.setRotation(mrotation);
	}

	void update(float deltaTime) {
		// Movement Code:
		(msprinting) ? msprite_speed = msprinting_speed : msprite_speed = mmovement_speed;

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
		mrotation = (atan2(msprite.getPosition().y - sf::Mouse::getPosition(*mwindow).y, (msprite.getPosition().x - sf::Mouse::getPosition(*mwindow).x)) * 180.0f / 3.14f);
		msprite.setRotation(mrotation - 90.0f);
		// End of Sprite Rotation Code

		// Start of Bullet Mechanic
		if (mbullets.size() != 0 && mbullets[0].isDecayed()) {
			std::cout << "Bullets: " << mbullets.size() << std::endl;
			mbullets.pop_front();
		}
		
		if (mgun_shot) {
			mbullets.push_back(Projectile(mwindow, mtm, "Bullet01", msprite.getPosition(), mrotation, 1700.0f, 30.0f, 2.5f));
			mgun_shot = false;
		}

		for (int i = 0; i < mbullets.size(); ++i) {
			mbullets[i].update(deltaTime);
		}
	}

	void render() {
		for (int i = 0; i < mbullets.size(); ++i) {
			mbullets[i].render();
		}
		mwindow->draw(msprite);
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

	// Bullet Mechanic Variables

	bool mgun_shot;

	std::deque<Projectile> mbullets;
private:
	float msprinting_speed, msprite_speed;
};

#endif