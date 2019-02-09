#include <iostream>
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "Player.h"
#include "Zombie.h"
#include "Pawn.h"
#include "Entity.h"

//Agy testing shit

/*
	I am going to continue to work on the game from here

	I've decided to go for a more survival-style game instead of the arcade style originally intended.

	Updates:
		- I've modified how input works in this program. Instead of all the input being managed in the Player class,
		  I moved the input management to the main loop instead. This should prove to be a preferred alternative to what
		  I was doing previously.
		- I've began implementing pointers in places that should make the code run more efficiently.
		- I've added a deltaTime to the game.
			- Player movement is now based on the deltaTime variable. This should prove useful when implementing multiplayer
			  down the line.

	Changes I want to Occur:
		- I want to create a GUI class for this game. [NOT STARTED]
		- I want to create a Loot System [NOT STARTED]
		- I want to clean up Legacy Code for Desolate. [IN-PROGESS]
*/

void loadTextures(TextureManager& tM) {
	tM.addTexture("Human01", "Data/Human01.png");
	tM.addTexture("Zombie01", "Data/Zombie01.png");
	tM.addTexture("Bullet01", "Data/Bullet01.png");
}

int ZombieMain() {
	sf::RenderWindow gwindow(sf::VideoMode(1280, 960), "Desolate"); //gwindow = global window
	sf::Event gevent;
	sf::Clock delta_clock;

	TextureManager tM;

	loadTextures(tM);

	Player player(&gwindow, &tM);

	Zombie zombie(&gwindow, &player, &tM);

	sf::Clock clock;

	while (gwindow.isOpen()) {

		sf::Time dt = delta_clock.restart();

		while (gwindow.pollEvent(gevent)) {
			if (gevent.type == sf::Event::MouseButtonPressed) {
				if (gevent.mouseButton.button == sf::Mouse::Left)
					player.mgun_shot = true;
			}
			if (gevent.type == sf::Event::MouseButtonReleased) {
				if (gevent.mouseButton.button == sf::Mouse::Left)
					player.mgun_shot = false;
			}
			if (gevent.type == sf::Event::Closed) {
				gwindow.close();
			}
			if (gevent.type == sf::Event::KeyPressed) {
				player.changeDirection(gevent);
				switch (gevent.key.code) {
				case sf::Keyboard::Escape:
					gwindow.close();
					break;
				}
			}
			if (gevent.type == sf::Event::KeyReleased) {
				player.changeDirection(gevent);
			}
		}

		player.update(dt.asSeconds());
		zombie.update(dt.asSeconds());

		gwindow.clear(sf::Color(13, 39, 38, 255));
		player.render();
		zombie.render();
		gwindow.display();
	}

	return 0;
}

int RTSMain() {
	sf::RenderWindow gwindow(sf::VideoMode(1280, 960), "RTS Game");
	sf::Event gevent;
	sf::Clock delta_clock;

	TextureManager gTextureManager;
	loadTextures(gTextureManager);

	srand(time(NULL));

	std::vector<Pawn> pawns;

	for (int i = 0; i != 5; i++) {
		pawns.push_back(Pawn(&gwindow, &gTextureManager));
	}

	while (gwindow.isOpen()) {

		float deltaTime = delta_clock.restart().asSeconds();

		while (gwindow.pollEvent(gevent)) {
			if (gevent.type == sf::Event::Closed)
				gwindow.close();
			if (gevent.type == sf::Event::KeyPressed)
				if (gevent.key.code == sf::Keyboard::Escape)
					gwindow.close();
			if (gevent.type == sf::Event::MouseButtonPressed) {
				if (gevent.mouseButton.button == sf::Mouse::Left) {
					for (int i = 0; i != pawns.size(); i++) {
						pawns[i].mpawn_state = MOVING;
						pawns[i].mTarget = sf::Vector2f(sf::Mouse::getPosition(gwindow));
					}
				}
			}
		}

		for (int i = 0; i != pawns.size(); i++) {
			pawns[i].update(deltaTime);
		}


		gwindow.clear(sf::Color(50, 50, 50, 255));
		for (int i = 0; i != pawns.size(); i++) {
			pawns[i].render();
		}
		gwindow.display();
	}

	return 0;
}

int main() {
	ZombieMain();
	return 0;
}

//void auraEffect(Player* player) {
//	sf::CircleShape circle;
//	sf::CircleShape circle1;
//	sf::CircleShape circle2;
//
//	circle.setFillColor(sf::Color::Red);
//	circle.setRadius(5.0f);
//	circle.setOrigin(circle.getRadius() / 2.0f, circle.getRadius() / 2.0f);
//	circle.setPosition(sf::Vector2f(player.msprite.getPosition().x + sinf(clock.getElapsedTime().asSeconds() * 5.0f) * 100.0f, player.msprite.getPosition().y + cosf(clock.getElapsedTime().asSeconds() * 5.0f) * 100.0f));
//
//	circle1.setFillColor(sf::Color::Green);
//	circle1.setRadius(5.0f);
//	circle1.setOrigin(circle1.getRadius() / 2.0f, circle1.getRadius() / 2.0f);
//	circle1.setPosition(sf::Vector2f(player.msprite.getPosition().x + sinf(clock.getElapsedTime().asSeconds() * 5.0f + 90.0f) * 100.0f, player.msprite.getPosition().y + cosf(clock.getElapsedTime().asSeconds() * 7.0f + 90.0f) * 100.0f));
//
//	circle2.setFillColor(sf::Color::Blue);
//	circle2.setRadius(5.0f);
//	circle2.setOrigin(circle2.getRadius() / 2.0f, circle2.getRadius() / 2.0f);
//	circle2.setPosition(sf::Vector2f(player.msprite.getPosition().x + sinf(clock.getElapsedTime().asSeconds() * 5.0f + 180.0f) * 100.0f, player.msprite.getPosition().y + cosf(clock.getElapsedTime().asSeconds() * 3.0f + 180.0f) * 100.0f));
//
//	gwindow.draw(circle);
//	gwindow.draw(circle1);
//	gwindow.draw(circle2);
//}