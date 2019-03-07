#ifndef SCENE_H
#define SCENE_H
//test
#include <iostream>
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "Entity.h"
#include "Player.h"
#include "Zombie.h"


class Scene {
public:
	Scene(sf::RenderWindow* window, TextureManager* tM) {
		window_ = window;
		texture_manager_ = tM;
	}

	void input(sf::Event event) {
		for (int i = 0; i < player_list_.size(); ++i) {
			player_list_[i]->changeDirection(event);
		}
	}

	void update(float dT) {
		for (int i = 0; i < player_list_.size(); ++i) {
			player_list_[i]->update(dT);
		}
		for (int i = 0; i < zombie_list_.size(); ++i) {
			zombie_list_[i]->update(dT);
		}
	}

	void render() {
		window_->draw(scene_background_);
		for (int i = 0; i < player_list_.size(); ++i) {
			player_list_[i]->render();
		}
		for (int i = 0; i < zombie_list_.size(); ++i) {
			zombie_list_[i]->render();
		}
	}

	void setSceneBackground(sf::Sprite background) {
		scene_background_ = background;
	}
	void addPlayer(std::string name) {
		player_list_.push_back(new Player(window_, texture_manager_, name));
	}
	void addZombie(ZOMBIETYPE type) {
		zombie_list_.push_back(new Zombie(window_, texture_manager_, player_list_[0], type));
	}
	void addZombie(ZOMBIETYPE type, sf::Vector2f pos) {
		zombie_list_.push_back(new Zombie(window_, texture_manager_, player_list_[0], type, pos));
	}
	
	Player* getPlayer(std::string name) {
		for (int i = 0; i < player_list_.size(); ++i) {
			if (player_list_[i]->getName() == name) {
				return player_list_[i];
			}
		}
		return NULL;
	}
private:
	sf::RenderWindow* window_;
	TextureManager* texture_manager_;

	sf::Sprite scene_background_;

	std::vector<Player*> player_list_;
	std::vector<Zombie*> zombie_list_;
};

#endif