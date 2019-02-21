#ifndef GUI_H
#define GUI_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "TextureManager.h"

class GUI {
public:
	GUI(sf::RenderWindow* window, TextureManager* tm) {
		mWindow = window;
		mTextureManager = tm;
		std::cout << "GUI Initialized" << std::endl;
	}

	virtual ~GUI() {
		for (int i = 0; i < mGUIElements.size(); ++i) {
			delete mGUIElements[i];
		}
	}

	virtual void input(sf::Event* event) {

	}

	virtual void update(float deltaTime) {

	}

	virtual void render() {
		for (int i = 0; i < mGUIElements.size(); ++i) {
			mWindow->draw(*mGUIElements[i]);
		}
	}
protected:
	sf::RenderWindow* mWindow;
	TextureManager* mTextureManager;

	std::vector<sf::Drawable*> mGUIElements;
};

#endif