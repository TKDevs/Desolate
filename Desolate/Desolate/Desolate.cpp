#include <iostream>
#include <SFML/Graphics.hpp> 
#include "TextureManager.h"
#include "Entity.h"
#include "Player.h"
#include "Zombie.h"
#include "Scene.h"
#include "MainGUI.h"

/* short form
	dT = delta_time
	tM = texture_manager
*/

void loadTextures(TextureManager& tM) {
	tM.addTexture("Human01", "Data/Human01.png");
	tM.addTexture("Zombie01", "Data/Zombie01.png");
	tM.addTexture("Zombie02", "Data/Zombie02.png");
	tM.addTexture("Zombie03", "Data/Zombie03.png");
	tM.addTexture("Zombie04", "Data/Zombie04.png");
	tM.addTexture("Bullet01", "Data/Bullet01.png");
	tM.addTexture("Background01", "Data/background01.png");
	tM.addTexture("Hatchet", "Data/Hatchet.png");
	tM.addTexture("Machete", "Data/Machete.png");
	tM.addTexture("Bat", "Data/Bat.png");
	tM.addTexture("GUIHunger", "Data/GUIHunger.png");
	tM.addTexture("GUIThirst", "Data/GUIThirst.png");
	tM.addTexture("GUIRest", "Data/GUIRest.png");
	tM.addTexture("GUIHealth", "Data/GUIHealth.png");
}

void ZombieMain() {
	sf::RenderWindow gWindow(sf::VideoMode(1280, 960), "Derilict v1.0"); gWindow.setPosition(sf::Vector2i(200, 10));
	sf::Event gEvent;
	sf::Clock deltaClock;
	TextureManager gtM;
	loadTextures(gtM);

	Scene scene(&gWindow, &gtM);
	sf::Sprite background; background.setTexture(gtM.getTexture("Background01"));
	background.setScale(4.0f, 4.0f);
	scene.setSceneBackground(background);
	scene.addPlayer("George");
	scene.addZombie(NORMAL, sf::Vector2f(560, 80));
	scene.addZombie(SCOUT, sf::Vector2f(1450, 110));

	MainGUI gGameGUI(&gWindow, &gtM, scene.getPlayer("George"));

	while (gWindow.isOpen()) {
		sf::Time dT = deltaClock.restart();
		// Input Code
		while (gWindow.pollEvent(gEvent)) {
			if (gEvent.type == sf::Event::Closed)
				gWindow.close();
			scene.getPlayer("George")->changeDirection(gEvent);
			gGameGUI.input(&gEvent);
		}
		// Update Code
		scene.update(dT.asSeconds());
		gGameGUI.update(dT.asSeconds());
		sf::View view = gWindow.getView();
		view.setCenter(scene.getPlayer("George")->getPosition());
		gWindow.setView(view);
		// Render Code
		gWindow.clear(sf::Color(13, 39, 38, 255));
		scene.render();
		gGameGUI.render();
		gWindow.display();
	}

}

int main() {
	ZombieMain();
	return 0;
}