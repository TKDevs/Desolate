#ifndef PAWN_H
#define PAWN_H

enum PawnState {
	IDLE,
	MOVING,
	ATTACKING
};

class Pawn {
public:
	Pawn(sf::RenderWindow* window, TextureManager* tM) : window_(window), tM_(tM) {
		random_reaction = (rand() % 5 + 1) / 10.0f;
		movement_speed_ = 160.0f;
		sprite_rotation_ = 0.0f;
		is_selected_ = false;
		sprite_.setPosition(1280 / 2, 960 / 2);
		sprite_.setRotation(sprite_rotation_);
		sprite_.setOrigin(12.0f, 12.0f);
		sprite_.setScale(2.0f, 2.0f);
		sprite_.setTexture(tM_->getTexture("Human01"));
		mpawn_state = IDLE;
	}
	void update(float dT) {
		switch (mpawn_state) {
		case IDLE:
			roam(dT);
			break;
		case MOVING:
			moveTo(target_, dT, 30.0f);
			break;
		}
	}
	void render() {
		window_->draw(sprite_);
	}

	PawnState mpawn_state;
	sf::Vector2f target_;
private:
	float getDistance(sf::Vector2f pos1, sf::Vector2f pos2) {
		return sqrt((pos1.x - pos2.x) * (pos1.x - pos2.x) + (pos1.y - pos2.y) * (pos1.y - pos2.y));
	}
	void moveTo(sf::Vector2f target, float dT, float buffer) {
		if (getDistance(sprite_.getPosition(), target) >= buffer) {
			sprite_rotation_ = -atan2(sprite_.getPosition().x - target.x, sprite_.getPosition().y - target.y) * 180 / 3.14;
			sprite_.setRotation(sprite_rotation_);
			sf::Vector2f movement;
			movement.x = -static_cast<float>(cos(3.14 * (sprite_rotation_ + 90.0f) / 180) * movement_speed_ * dT);
			movement.y = -static_cast<float>(sin(3.14 * (sprite_rotation_ + 90.0f) / 180) * movement_speed_ * dT);
			sprite_.move(movement);
		}
		else {
			mpawn_state = IDLE;
		}
	}
	void roam(float dT) {
		if (AI_action_clock.getElapsedTime().asSeconds() >= 1.0f + random_reaction) {
			random_action = rand() % 10 + 1;
			if (random_action >= 8) {
				sprite_rotation_ = rand() % 360 + 1;
			}
			AI_action_clock.restart();
		}
		if (random_action >= 8) {
			sprite_.setRotation(sprite_rotation_);
			sf::Vector2f movement(-static_cast<float>(cos(3.14 * (sprite_rotation_ + 90.0f) / 180) * movement_speed_ * dT), -static_cast<float>(sin(3.14 * (sprite_rotation_ + 90.0f) / 180) * movement_speed_ * dT));
			sprite_.move(movement);
		}
		else {
			sprite_.move(0.0f, 0.0f);
		}
	}

	bool is_selected_;

	sf::Clock AI_clock;
	sf::Clock AI_action_clock;

	sf::Sprite sprite_;

	sf::RenderWindow* window_;
	TextureManager* tM_;

	float movement_speed_, sprite_rotation_;
	float random_action, random_reaction;
};
#endif