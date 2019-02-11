#ifndef SCENE_H
#define SCENE_H

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

	void setSceneBackground(std::string name) {
		scene_background_.setTexture(texture_manager_->getTexture(name));
	}

	void addPlayer(Player* player) {
		player_list_.push_back(player);
	}

	void addZombie(Zombie* zombie) {
		zombie_list_.push_back(zombie);
	}

	void removePlayer(Player* player) {
		for (int i = 0; i < player_list_.size(); ++i) {
			if (player->getID() == player_list_[i]->getID()) {
				delete player;
				delete player_list_[i];
				player_list_.erase(player_list_.begin() + i);
			}
		}
	}

	void removeZombie(Zombie* zombie) {
		for (int i = 0; i < zombie_list_.size(); ++i) {
			if (zombie->getID() == zombie_list_[i]->getID()) {
				delete zombie;
				delete zombie_list_[i];
				zombie_list_.erase(zombie_list_.begin() + i);
			}
		}
	}
private:
	sf::RenderWindow* window_;
	TextureManager* texture_manager_;

	sf::Sprite scene_background_;

	std::vector<Player*> player_list_;
	std::vector<Zombie*> zombie_list_;
};

#endif