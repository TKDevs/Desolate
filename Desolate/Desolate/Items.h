#ifndef ITEMS_H
#define ITEMS_H

#include "TextureManager"
#include "Entity.h"
#include "ItemLoader"


class Item {
public:
	Item(sf::RenderWindow* window, TextureManager* tM) {
		window_ = window;
		tM_ = tM;
	}

protected:
	TextureManager*		tM_;
	sf::RenderWindow*	window_;
	sf::Sprite			sprite_;
	float	weight_;
	Recipe	recipe_;
	Entity	owner_;
	Rarity  rarity_;
};

#endif

