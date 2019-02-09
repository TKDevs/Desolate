#ifndef ENTITY_H
#define ENTITY_H

class Entity {
public:
	Entity(sf::RenderWindow* window, TextureManager* tm): mwindow(window), mtm(tm){
		mrotation = 0.0f;
	}
	virtual void render() {
		mwindow->draw(msprite);
	}
	virtual void update() {}
	sf::Vector2f getPosition() {
		return msprite.getPosition();
	}

protected:
	float mmovement_speed;
	float mrotation;
	TextureManager* mtm;
	sf::RenderWindow* mwindow;
	sf::Sprite msprite;
};

#endif