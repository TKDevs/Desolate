#ifndef GUI_H
#define GUI_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "TextureManager.h"

class GUI {
public:
	GUI(sf::RenderWindow* window, TextureManager* tM) {
		window_ = window;
		tM_ = tM;
		std::cout << "GUI Initialized" << std::endl;
	}

	virtual ~GUI() {
		for (int i = 0; i < GUI_elements_.size(); ++i) {
			delete GUI_elements_[i];
		}
	}

	virtual void input(sf::Event* event) {

	}

	virtual void update(float dT) {

	}

	virtual void render() {
		for (int i = 0; i < GUI_elements_.size(); ++i) {
			window_->draw(*GUI_elements_[i]);
		}
	}
protected:
	sf::RenderWindow* window_;
	TextureManager* tM_;

	std::vector<sf::Drawable*> GUI_elements_;
};

#endif