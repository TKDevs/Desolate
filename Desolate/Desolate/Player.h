#ifndef PLAYER_H
#define PLAYER_H

#include <deque>
#include "Entity.h"
#include "TextureManager.h"
#include "Projectile.h"

class Player : public Entity {
public:
	struct VitalsPackage {
		float hunger = 100,
			thirst = 100,
			health = 100,
			rest = 100;
		float hungerLossRate = 0.1f,
			thirstLossRate = 0.1f,
			healthLossRate = 0.0f,
			restLossRate = 0.1f;
	};

	Player(sf::RenderWindow* window, TextureManager* tM, std::string name) : Entity(window, tM) {
		name_ = name;
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
		sprite_.setPosition(sf::Vector2f(1000, 950));
		sprite_.setRotation(sprite_rotation_);
	}

	void update(float dT) {
		if (vitals_clock_.getElapsedTime().asSeconds() >= 1.0f) {
			vitals_.hunger -= vitals_.hungerLossRate;
			vitals_.thirst -= vitals_.thirstLossRate;
			vitals_.rest -= vitals_.restLossRate;
			vitals_clock_.restart();
		}
		if (sprinting_) {
			sprite_speed_ = sprinting_speed_;
			vitals_.hungerLossRate = 0.2f;
			vitals_.thirstLossRate = 0.2f;
			vitals_.restLossRate = 0.2f;
		}
		else {
			sprite_speed_ = normal_speed_;
			vitals_.hungerLossRate = 0.1f;
			vitals_.thirstLossRate = 0.1f;
			vitals_.restLossRate = 0.1f;
		}
		sf::Vector2f movement; float slowdown = 1.30f;
		if (move_up_)
			movement.y -= sprite_speed_ * dT;
		if (move_down_)
			movement.y += sprite_speed_ * dT;
		if (move_left_)
			movement.x -= sprite_speed_ * dT;
		if (move_right_)
			movement.x += sprite_speed_ * dT;
		if (move_up_ && move_left_) {
			movement.x = -sprite_speed_ * dT / slowdown;
			movement.y = -sprite_speed_ * dT / slowdown;
		}
		if (move_up_ && move_right_) {
			movement.x = sprite_speed_ * dT / slowdown;
			movement.y = -sprite_speed_ * dT / slowdown;
		}
		if (move_down_ && move_left_) {
			movement.x = -sprite_speed_ * dT / slowdown;
			movement.y = sprite_speed_ * dT / slowdown;
		}
		if (move_down_ && move_right_) {
			movement.x = sprite_speed_ * dT / slowdown;
			movement.y = sprite_speed_ * dT / slowdown;
		}
		sprite_.move(movement);
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

	VitalsPackage getVitals() {
		return vitals_;
	}

	std::string getName() {
		return name_;
	}
private:
	bool move_up_, move_down_, move_left_, move_right_, sprinting_, shot_gun_;
	float sprinting_speed_, normal_speed_, sprite_speed_, sprite_rotation_;

	std::string name_;

	sf::Clock vitals_clock_;
	VitalsPackage vitals_;
};

#endif