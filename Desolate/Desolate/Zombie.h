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
			zombie_speed_ = 200.0f + variance;
			zombie_damage_ = 10.0f;
			zombie_atkspd_ = 1.0f;
			detect_range_ = 500.0f;
			sprite_.setTexture(tM->getTexture("Zombie01"));
			break;
		case SCOUT:
			zombie_speed_ = 275.0f + variance;
			zombie_damage_ = 5.0f;
			zombie_atkspd_ = 1.0f;
			detect_range_ = 600.0f;
			sprite_.setTexture(tM->getTexture("Zombie04"));
			break;

		case TANK:
			zombie_speed_ = 100.0f + variance;
			zombie_damage_ = 20.0f;
			zombie_atkspd_ = 1.0f;
			detect_range_ = 300.0f;
			sprite_.setTexture(tM->getTexture("Zombie02"));
			break;
		}
		player_ = player;
		sprite_rotation_ = 0.0f;
		sprite_.setRotation(0.0f);
		sprite_.setOrigin(12.0f, 12.0f);
		sprite_.setScale(sf::Vector2f(3.0f, 3.0f));
		sprite_.setPosition(sf::Vector2f(75.0f, 75.0f));
		last_seen_player_ = sprite_.getPosition();
	}

	void update(float dT) {
		if (getDistance(player_->getPosition(), sprite_.getPosition()) <= detect_range_) {
			moveTo(player_->getPosition(), dT);
			last_seen_player_ = player_->getPosition();
		}
		else {
			moveTo(last_seen_player_, dT);
		}
	}
protected:
	float getDistance(sf::Vector2f pos1, sf::Vector2f pos2) {
		return sqrt((pos1.x - pos2.x) * (pos1.x - pos2.x) + (pos1.y - pos2.y) * (pos1.y - pos2.y));
	}

	void moveTo(sf::Vector2f targetPos, float dT) {
		sprite_rotation_ = (atan2(sprite_.getPosition().y - targetPos.y, sprite_.getPosition().x - targetPos.x) * 180.0f / 3.14f);
		sprite_.setRotation(sprite_rotation_ - 90.0f);
		float movementX = static_cast<float>(cos(3.14 * sprite_rotation_ / 180) * zombie_speed_ * dT);
		float movementY = static_cast<float>(sin(3.14 * sprite_rotation_ / 180) * zombie_speed_ * dT);
		if (getDistance(sprite_.getPosition(), targetPos) >= 45.0f) {
			sprite_.move(-movementX, -movementY);
		}
		else {
			sprite_.move(0.0f, 0.0f);
		}
	}

	// Zombie Specifications
	float zombie_speed_;
	float zombie_damage_;
	float zombie_atkspd_;
	float sprite_rotation_;
	float detect_range_;
	Player* player_;
	sf::Vector2f last_seen_player_;
};

#endif