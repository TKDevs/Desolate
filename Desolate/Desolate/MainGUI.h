#ifndef MAINGUI_H
#define MAINGUI_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "GUI.h"
#include "Player.h"
#include "TextureManager.h"

// TODO: Delete all the new data created in the heap in the constructor (Preferred in GUI.h)

class MainGUI : public GUI {
public:
	MainGUI(sf::RenderWindow* window, TextureManager* tM, Player* player) : GUI(window, tM) {
		player_ = player;
		box_selected_ = 0;

		healthy_ = sf::Color(13, 142, 8);
		warning_ = sf::Color(214, 198, 55);
		danger_ = sf::Color(160, 23, 11);
		fatal_ = sf::Color(0, 0, 0);

		hunger_meter_ = new sf::Sprite(tM_->getTexture("GUIHunger"));
		hunger_meter_->setScale(sf::Vector2f(2.0f, 2.0f));
		hunger_meter_->setPosition(sf::Vector2f(player_->getPosition().x + 310, player_->getPosition().y - 445));

		thrist_meter_ = new sf::Sprite(tM_->getTexture("GUIThirst"));
		thrist_meter_->setScale(sf::Vector2f(2.0f, 2.0f));
		thrist_meter_->setPosition(sf::Vector2f(player_->getPosition().x + 385, player_->getPosition().y - 445));

		health_meter_ = new sf::Sprite(tM_->getTexture("GUIHealth"));
		health_meter_->setScale(sf::Vector2f(2.0f, 2.0f));
		health_meter_->setPosition(sf::Vector2f(player_->getPosition().x + 460, player_->getPosition().y - 445));

		rest_meter = new sf::Sprite(tM_->getTexture("GUIRest"));
		rest_meter->setScale(sf::Vector2f(2.0f, 2.0f));
		rest_meter->setPosition(sf::Vector2f(player_->getPosition().x + 535, player_->getPosition().y - 445));

		backboarder_ = new sf::RectangleShape(sf::Vector2f(560, 120));
		backboarder_->setPosition(sf::Vector2f(player_->getPosition().x - 280.0f, player_->getPosition().y + 355));
		backboarder_->setFillColor(sf::Color(10, 10, 10, 200));

		hunger_level_ = new sf::CircleShape(30.0f);
		hunger_level_->setFillColor(healthy_);

		thirst_level_ = new sf::CircleShape(30.0f);
		thirst_level_->setFillColor(healthy_);

		health_level_ = new sf::CircleShape(30.0f);
		health_level_->setFillColor(healthy_);

		rest_level = new sf::CircleShape(30.0f);
		rest_level->setFillColor(healthy_);

		box0_ = new sf::RectangleShape(sf::Vector2f(100, 100));
		box0_->setPosition(sf::Vector2f(sf::Vector2f(backboarder_->getPosition().x + 10, backboarder_->getPosition().y + 10)));
		box0_->setFillColor(sf::Color(10, 10, 10, 230));
		box0_->setOutlineColor(sf::Color::White);

		box1_ = new sf::RectangleShape(sf::Vector2f(100, 100));
		box1_->setPosition(sf::Vector2f(sf::Vector2f(backboarder_->getPosition().x + 120, backboarder_->getPosition().y + 10)));
		box1_->setFillColor(sf::Color(10, 10, 10, 230));
		box1_->setOutlineColor(sf::Color::White);

		box2_ = new sf::RectangleShape(sf::Vector2f(100, 100));
		box2_->setPosition(sf::Vector2f(sf::Vector2f(backboarder_->getPosition().x + 230, backboarder_->getPosition().y + 10)));
		box2_->setFillColor(sf::Color(10, 10, 10, 230));
		box2_->setOutlineColor(sf::Color::White);

		box3_ = new sf::RectangleShape(sf::Vector2f(100, 100));
		box3_->setPosition(sf::Vector2f(sf::Vector2f(backboarder_->getPosition().x + 340, backboarder_->getPosition().y + 10)));
		box3_->setFillColor(sf::Color(10, 10, 10, 230));
		box3_->setOutlineColor(sf::Color::White);

		box4_ = new sf::RectangleShape(sf::Vector2f(100, 100));
		box4_->setPosition(sf::Vector2f(sf::Vector2f(backboarder_->getPosition().x + 450, backboarder_->getPosition().y + 10)));
		box4_->setFillColor(sf::Color(10, 10, 10, 230));
		box4_->setOutlineColor(sf::Color::White);

		GUI_elements_.push_back(hunger_level_);
		GUI_elements_.push_back(thirst_level_);
		GUI_elements_.push_back(health_level_);
		GUI_elements_.push_back(rest_level);

		GUI_elements_.push_back(hunger_meter_);
		GUI_elements_.push_back(thrist_meter_);
		GUI_elements_.push_back(health_meter_);
		GUI_elements_.push_back(rest_meter);

		GUI_elements_.push_back(backboarder_);
		GUI_elements_.push_back(box0_);
		GUI_elements_.push_back(box1_);
		GUI_elements_.push_back(box2_);
		GUI_elements_.push_back(box3_);
		GUI_elements_.push_back(box4_);
	}

	void input(sf::Event* event) {
		if (event->type == sf::Event::KeyPressed) {
			switch (event->key.code) {
			case sf::Keyboard::Num1:
				box_selected_ = 0;
				break;
			case sf::Keyboard::Num2:
				box_selected_ = 1;
				break;
			case sf::Keyboard::Num3:
				box_selected_ = 2;
				break;
			case sf::Keyboard::Num4:
				box_selected_ = 3;
				break;
			case sf::Keyboard::Num5:
				box_selected_ = 4;
				break;
			case sf::Keyboard::Escape:
				window_->close();
				break;
			}
		}
	}

	void update(float deltaTime) {
		hunger_level_->setPosition(hunger_meter_->getPosition().x + 2, hunger_meter_->getPosition().y + 2);
		thirst_level_->setPosition(thrist_meter_->getPosition().x + 2, thrist_meter_->getPosition().y + 2);
		health_level_->setPosition(health_meter_->getPosition().x + 2, health_meter_->getPosition().y + 2);
		rest_level->setPosition(rest_meter->getPosition().x + 2, rest_meter->getPosition().y + 2);

		hunger_meter_->setPosition(sf::Vector2f(player_->getPosition().x + 330.0f, player_->getPosition().y - 445.0f));
		thrist_meter_->setPosition(sf::Vector2f(player_->getPosition().x + 405.0f, player_->getPosition().y - 445.0f));
		health_meter_->setPosition(sf::Vector2f(player_->getPosition().x + 480.0f, player_->getPosition().y - 445.0f));
		rest_meter->setPosition(sf::Vector2f(player_->getPosition().x + 555.0f, player_->getPosition().y - 445.0f));

		backboarder_->setPosition(sf::Vector2f(player_->getPosition().x - 280.0f, player_->getPosition().y + 355.0f));
		box0_->setPosition(sf::Vector2f(sf::Vector2f(backboarder_->getPosition().x + 10, backboarder_->getPosition().y + 10)));
		box1_->setPosition(sf::Vector2f(sf::Vector2f(backboarder_->getPosition().x + 120, backboarder_->getPosition().y + 10)));
		box2_->setPosition(sf::Vector2f(sf::Vector2f(backboarder_->getPosition().x + 230, backboarder_->getPosition().y + 10)));
		box3_->setPosition(sf::Vector2f(sf::Vector2f(backboarder_->getPosition().x + 340, backboarder_->getPosition().y + 10)));
		box4_->setPosition(sf::Vector2f(sf::Vector2f(backboarder_->getPosition().x + 450, backboarder_->getPosition().y + 10)));

		if (player_->getVitals().hunger < 50.0f)
			hunger_level_->setFillColor(warning_);
		if (player_->getVitals().hunger < 10.0f)
			hunger_level_->setFillColor(danger_);
		if (player_->getVitals().hunger < 0.0f)
			hunger_level_->setFillColor(fatal_);

		if (player_->getVitals().thirst < 50.0f)
			hunger_level_->setFillColor(warning_);
		if (player_->getVitals().thirst < 10.0f)
			hunger_level_->setFillColor(danger_);
		if (player_->getVitals().thirst < 0.0f)
			hunger_level_->setFillColor(fatal_);

		if (player_->getVitals().health < 50.0f)
			hunger_level_->setFillColor(warning_);
		if (player_->getVitals().health < 10.0f)
			hunger_level_->setFillColor(danger_);
		if (player_->getVitals().health < 0.0f)
			hunger_level_->setFillColor(fatal_);

		if (player_->getVitals().rest < 50.0f)
			hunger_level_->setFillColor(warning_);
		if (player_->getVitals().rest < 10.0f)
			hunger_level_->setFillColor(danger_);
		if (player_->getVitals().rest < 0.0f)
			hunger_level_->setFillColor(fatal_);

		switch (box_selected_) {
		case 0:
			box0_->setOutlineThickness(1.0f);
			box1_->setOutlineThickness(0.0f);
			box2_->setOutlineThickness(0.0f);
			box3_->setOutlineThickness(0.0f);
			box4_->setOutlineThickness(0.0f);
			break;
		case 1:
			box0_->setOutlineThickness(0.0f);
			box1_->setOutlineThickness(1.0f);
			box2_->setOutlineThickness(0.0f);
			box3_->setOutlineThickness(0.0f);
			box4_->setOutlineThickness(0.0f);
			break;
		case 2:
			box0_->setOutlineThickness(0.0f);
			box1_->setOutlineThickness(0.0f);
			box2_->setOutlineThickness(1.0f);
			box3_->setOutlineThickness(0.0f);
			box4_->setOutlineThickness(0.0f);
			break;
		case 3:
			box0_->setOutlineThickness(0.0f);
			box1_->setOutlineThickness(0.0f);
			box2_->setOutlineThickness(0.0f);
			box3_->setOutlineThickness(1.0f);
			box4_->setOutlineThickness(0.0f);
			break;
		case 4:
			box0_->setOutlineThickness(0.0f);
			box1_->setOutlineThickness(0.0f);
			box2_->setOutlineThickness(0.0f);
			box3_->setOutlineThickness(0.0f);
			box4_->setOutlineThickness(1.0f);
			break;
		}
	}
private:
	sf::Sprite *hunger_meter_, *thrist_meter_, *health_meter_, *rest_meter;
	sf::RectangleShape *backboarder_, *box0_, *box1_, *box2_, *box3_, *box4_;
	sf::CircleShape *hunger_level_, *thirst_level_, *health_level_, *rest_level;
	sf::Color healthy_, warning_, danger_, fatal_;
	int box_selected_;
	Player* player_;
};

#endif