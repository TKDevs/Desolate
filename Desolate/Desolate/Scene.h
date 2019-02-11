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
	Scene(sf::RenderWindow* window, TextureManager* tm) {
		mWindow = window;
		mTextureManager = tm;
	}

	void update(float deltaTime) {
		for (int i = 0; i < mPlayerList.size(); ++i) {
			mPlayerList[i]->update(deltaTime);
		}
		for (int i = 0; i < mZombieList.size(); ++i) {
			mZombieList[i]->update(deltaTime);
		}
	}

	void render() {
		mWindow->draw(mSceneBackground);
		for (int i = 0; i < mPlayerList.size(); ++i) {
			mPlayerList[i]->render();
		}
		for (int i = 0; i < mZombieList.size(); ++i) {
			mZombieList[i]->render();
		}
	}

	void setSceneBackground(std::string name) {
		mSceneBackground.setTexture(mTextureManager->getTexture(name));
	}

	void addPlayer(Player* player) {
		mPlayerList.push_back(player);
	}

	void addZombie(Zombie* zombie) {
		mZombieList.push_back(zombie);
	}

	void removePlayer(Player* player) {
		for (int i = 0; i < mPlayerList.size(); ++i) {
			if (player->getID() == mPlayerList[i]->getID()) {
				delete player;
				delete mPlayerList[i];
				mPlayerList.erase(mPlayerList.begin() + i);
			}
		}
	}

	void removeZombie(Zombie* zombie) {
		for (int i = 0; i < mZombieList.size(); ++i) {
			if (zombie->getID() == mZombieList[i]->getID()) {
				delete zombie;
				delete mZombieList[i];
				mZombieList.erase(mZombieList.begin() + i);
			}
		}
	}
private:
	sf::RenderWindow* mWindow;
	TextureManager* mTextureManager;

	sf::Sprite mSceneBackground;

	std::vector<Player*> mPlayerList;
	std::vector<Zombie*> mZombieList;
};

#endif