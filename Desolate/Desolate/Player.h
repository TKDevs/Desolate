#ifndef PLAYER_H
#define PLAYER_H

#include <deque>
#include "Entity.h"
#include "TextureManager.h"
#include "Projectile.h"

class Player : public Entity {
public:
	Player(sf::RenderWindow* window, TextureManager* tM) : Entity(window, tM) {
		move_up_ = false;
		move_down_ = false;
		move_left_ = false;
		move_right_ = false;
		sprinting_speed_ = 350.0f;
		normal_speed_ = 250.0f;
		sprite_speed_ = normal_speed_;
		sprite_rotation_ = 0.0f;

		sprite_.setTexture(tM->getTexture("Human01"));
		sprite_.setOrigin(12.0f, 12.0f);
		sprite_.setScale(sf::Vector2f(3.0f, 3.0f));
		sprite_.setPosition(sf::Vector2f(640, 480));
		sprite_.setRotation(sprite_rotation_);
	}

	void update(float dT) {
		(sprinting_) ? sprite_speed_ = sprinting_speed_ : sprite_speed_ = normal_speed_;
		if (move_up_)
			sprite_.move(sf::Vector2f(0.0f, -sprite_speed_ * dT));
		if (move_down_)
			sprite_.move(sf::Vector2f(0.0f, sprite_speed_ * dT));
		if (move_left_)
			sprite_.move(sf::Vector2f(-sprite_speed_ * dT, 0.0f));
		if (move_right_)
			sprite_.move(sf::Vector2f(sprite_speed_ * dT, 0.0f));
		sprite_rotation_ = (atan2(sprite_.getPosition().y - window_->mapPixelToCoords(sf::Mouse::getPosition(*window_)).y, (sprite_.getPosition().x - window_->mapPixelToCoords(sf::Mouse::getPosition(*window_)).x)) * 180.0f / 3.14f);
		sprite_.setRotation(sprite_rotation_ - 90.0f);
	}

	void changeDirection(sf::Event event) {
		if (event.type == sf::Event::KeyPressed) {
			switch (event.key.code) {
			case sf::Keyboard::W:
				move_up_ = true;
				break;
			case sf::Keyboard::A:
				move_left_ = true;
				break;
			case sf::Keyboard::S:
				move_down_ = true;
				break;
			case sf::Keyboard::D:
				move_right_ = true;
				break;
			case sf::Keyboard::LShift:
				sprinting_ = true;
				break;
			default:
				break;
			}
		}

		if (event.type == sf::Event::KeyReleased) {
			switch (event.key.code) {
			case sf::Keyboard::W:
				move_up_ = false;
				break;
			case sf::Keyboard::A:
				move_left_ = false;
				break;
			case sf::Keyboard::S:
				move_down_ = false;
				break;
			case sf::Keyboard::D:
				move_right_ = false;
				break;
			case sf::Keyboard::LShift:
				sprinting_ = false;
				break;
			default:
				break;
			}
		}
	}
private:
	bool move_up_, move_down_, move_left_, move_right_, sprinting_, shot_gun_;
	float sprinting_speed_, normal_speed_, sprite_speed_, sprite_rotation_;
};

#endif