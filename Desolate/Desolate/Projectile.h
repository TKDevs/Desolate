#ifndef PROJECTILE_H
#define PROJECTILEH

#include <iostream>
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "Entity.h"

struct BulletSpecs {
	float bullet_rotation;
	float bullet_speed;
	float bullet_damage;
	float bullet_decay_time;
	std::string bullet_sprite_name;
};

class Projectile : public Entity {
public:
	Projectile(sf::RenderWindow* window, TextureManager* tM, sf::Vector2f startpos, BulletSpecs specs) : Entity(window, tM) {
		projectile_specs_ = specs;

		window_ = window;
		texture_manager_ = tM;
		sprite_.setPosition(startpos);
		sprite_.setRotation(projectile_specs_.bullet_rotation);
		sprite_.setTexture(texture_manager_->getTexture(projectile_specs_.bullet_sprite_name));
		sprite_.scale(2.0f, 2.0f);
		is_decayed_ = false;
	}

	void update(float dT) {
		if (projectile_clock_.getElapsedTime().asSeconds() > projectile_specs_.bullet_decay_time) {
			is_decayed_ = true;
		}
		else {
			sf::Vector2f bulletMovement(static_cast<float>(cos(3.14 *  sprite_.getRotation() / 180) * projectile_specs_.bullet_speed) * dT, static_cast<float>(sin(3.14 * sprite_.getRotation() / 180) * projectile_specs_.bullet_speed) * dT);
			sprite_.move(-bulletMovement);
		}
	}

	void render() {
		if (!is_decayed_)
			window_->draw(sprite_);
	}

	sf::Sprite* getSprite() {
		return &sprite_;
	}

	bool isDecayed() {
		return is_decayed_;
	}
private:
	sf::RenderWindow*   window_;
	TextureManager*		texture_manager_;
	sf::Clock			projectile_clock_;
	BulletSpecs			projectile_specs_;
	bool    is_decayed_;
};

#endif