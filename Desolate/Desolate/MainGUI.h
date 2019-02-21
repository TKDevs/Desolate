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
	MainGUI(sf::RenderWindow* window, TextureManager* tm, Player* player) : GUI(window, tm) {
		mPlayer = player;
		mBoxSelected = 0;

		mHealthy = sf::Color(13, 142, 8);
		mWarning = sf::Color(214, 198, 55);
		mDanger = sf::Color(160, 23, 11);
		mFatal = sf::Color(0, 0, 0);

		mHungerMeter = new sf::Sprite(mTextureManager->getTexture("GUIHunger"));
		mHungerMeter->setScale(sf::Vector2f(2.0f, 2.0f));
		mHungerMeter->setPosition(sf::Vector2f(mPlayer->getPosition().x + 310, mPlayer->getPosition().y - 445));

		mThirstMeter = new sf::Sprite(mTextureManager->getTexture("GUIThirst"));
		mThirstMeter->setScale(sf::Vector2f(2.0f, 2.0f));
		mThirstMeter->setPosition(sf::Vector2f(mPlayer->getPosition().x + 385, mPlayer->getPosition().y - 445));

		mHealthMeter = new sf::Sprite(mTextureManager->getTexture("GUIHealth"));
		mHealthMeter->setScale(sf::Vector2f(2.0f, 2.0f));
		mHealthMeter->setPosition(sf::Vector2f(mPlayer->getPosition().x + 460, mPlayer->getPosition().y - 445));

		mRestMeter = new sf::Sprite(mTextureManager->getTexture("GUIRest"));
		mRestMeter->setScale(sf::Vector2f(2.0f, 2.0f));
		mRestMeter->setPosition(sf::Vector2f(mPlayer->getPosition().x + 535, mPlayer->getPosition().y - 445));

		mBackBorder = new sf::RectangleShape(sf::Vector2f(560, 120));
		mBackBorder->setPosition(sf::Vector2f(mPlayer->getPosition().x - 280.0f, mPlayer->getPosition().y + 355));
		mBackBorder->setFillColor(sf::Color(10, 10, 10, 200));

		mHungerLevel = new sf::CircleShape(30.0f);
		mHungerLevel->setFillColor(mHealthy);

		mThirstLevel = new sf::CircleShape(30.0f);
		mThirstLevel->setFillColor(mHealthy);

		mHealthLevel = new sf::CircleShape(30.0f);
		mHealthLevel->setFillColor(mHealthy);

		mRestLevel = new sf::CircleShape(30.0f);
		mRestLevel->setFillColor(mHealthy);

		mBox0 = new sf::RectangleShape(sf::Vector2f(100, 100));
		mBox0->setPosition(sf::Vector2f(sf::Vector2f(mBackBorder->getPosition().x + 10, mBackBorder->getPosition().y + 10)));
		mBox0->setFillColor(sf::Color(10, 10, 10, 230));
		mBox0->setOutlineColor(sf::Color::White);

		mBox1 = new sf::RectangleShape(sf::Vector2f(100, 100));
		mBox1->setPosition(sf::Vector2f(sf::Vector2f(mBackBorder->getPosition().x + 120, mBackBorder->getPosition().y + 10)));
		mBox1->setFillColor(sf::Color(10, 10, 10, 230));
		mBox1->setOutlineColor(sf::Color::White);

		mBox2 = new sf::RectangleShape(sf::Vector2f(100, 100));
		mBox2->setPosition(sf::Vector2f(sf::Vector2f(mBackBorder->getPosition().x + 230, mBackBorder->getPosition().y + 10)));
		mBox2->setFillColor(sf::Color(10, 10, 10, 230));
		mBox2->setOutlineColor(sf::Color::White);

		mBox3 = new sf::RectangleShape(sf::Vector2f(100, 100));
		mBox3->setPosition(sf::Vector2f(sf::Vector2f(mBackBorder->getPosition().x + 340, mBackBorder->getPosition().y + 10)));
		mBox3->setFillColor(sf::Color(10, 10, 10, 230));
		mBox3->setOutlineColor(sf::Color::White);

		mBox4 = new sf::RectangleShape(sf::Vector2f(100, 100));
		mBox4->setPosition(sf::Vector2f(sf::Vector2f(mBackBorder->getPosition().x + 450, mBackBorder->getPosition().y + 10)));
		mBox4->setFillColor(sf::Color(10, 10, 10, 230));
		mBox4->setOutlineColor(sf::Color::White);

		mGUIElements.push_back(mHungerLevel);
		mGUIElements.push_back(mThirstLevel);
		mGUIElements.push_back(mHealthLevel);
		mGUIElements.push_back(mRestLevel);

		mGUIElements.push_back(mHungerMeter);
		mGUIElements.push_back(mThirstMeter);
		mGUIElements.push_back(mHealthMeter);
		mGUIElements.push_back(mRestMeter);

		mGUIElements.push_back(mBackBorder);
		mGUIElements.push_back(mBox0);
		mGUIElements.push_back(mBox1);
		mGUIElements.push_back(mBox2);
		mGUIElements.push_back(mBox3);
		mGUIElements.push_back(mBox4);
	}

	void input(sf::Event* event) {
		if (event->type == sf::Event::KeyPressed) {
			switch (event->key.code) {
			case sf::Keyboard::Num1:
				mBoxSelected = 0;
				break;
			case sf::Keyboard::Num2:
				mBoxSelected = 1;
				break;
			case sf::Keyboard::Num3:
				mBoxSelected = 2;
				break;
			case sf::Keyboard::Num4:
				mBoxSelected = 3;
				break;
			case sf::Keyboard::Num5:
				mBoxSelected = 4;
				break;
			case sf::Keyboard::Escape:
				mWindow->close();
				break;
			}
		}
	}

	void update(float deltaTime) {
		mHungerLevel->setPosition(mHungerMeter->getPosition().x + 2, mHungerMeter->getPosition().y + 2);
		mThirstLevel->setPosition(mThirstMeter->getPosition().x + 2, mThirstMeter->getPosition().y + 2);
		mHealthLevel->setPosition(mHealthMeter->getPosition().x + 2, mHealthMeter->getPosition().y + 2);
		mRestLevel->setPosition(mRestMeter->getPosition().x + 2, mRestMeter->getPosition().y + 2);

		mHungerMeter->setPosition(sf::Vector2f(mPlayer->getPosition().x + 330.0f, mPlayer->getPosition().y - 445.0f));
		mThirstMeter->setPosition(sf::Vector2f(mPlayer->getPosition().x + 405.0f, mPlayer->getPosition().y - 445.0f));
		mHealthMeter->setPosition(sf::Vector2f(mPlayer->getPosition().x + 480.0f, mPlayer->getPosition().y - 445.0f));
		mRestMeter->setPosition(sf::Vector2f(mPlayer->getPosition().x + 555.0f, mPlayer->getPosition().y - 445.0f));

		mBackBorder->setPosition(sf::Vector2f(mPlayer->getPosition().x - 280.0f, mPlayer->getPosition().y + 355.0f));
		mBox0->setPosition(sf::Vector2f(sf::Vector2f(mBackBorder->getPosition().x + 10, mBackBorder->getPosition().y + 10)));
		mBox1->setPosition(sf::Vector2f(sf::Vector2f(mBackBorder->getPosition().x + 120, mBackBorder->getPosition().y + 10)));
		mBox2->setPosition(sf::Vector2f(sf::Vector2f(mBackBorder->getPosition().x + 230, mBackBorder->getPosition().y + 10)));
		mBox3->setPosition(sf::Vector2f(sf::Vector2f(mBackBorder->getPosition().x + 340, mBackBorder->getPosition().y + 10)));
		mBox4->setPosition(sf::Vector2f(sf::Vector2f(mBackBorder->getPosition().x + 450, mBackBorder->getPosition().y + 10)));

		if (mPlayer->getVitals().hunger < 50.0f)
			mHungerLevel->setFillColor(mWarning);
		if (mPlayer->getVitals().hunger < 10.0f)
			mHungerLevel->setFillColor(mDanger);
		if (mPlayer->getVitals().hunger < 0.0f)
			mHungerLevel->setFillColor(mFatal);

		if (mPlayer->getVitals().thirst < 50.0f)
			mHungerLevel->setFillColor(mWarning);
		if (mPlayer->getVitals().thirst < 10.0f)
			mHungerLevel->setFillColor(mDanger);
		if (mPlayer->getVitals().thirst < 0.0f)
			mHungerLevel->setFillColor(mFatal);

		if (mPlayer->getVitals().health < 50.0f)
			mHungerLevel->setFillColor(mWarning);
		if (mPlayer->getVitals().health < 10.0f)
			mHungerLevel->setFillColor(mDanger);
		if (mPlayer->getVitals().health < 0.0f)
			mHungerLevel->setFillColor(mFatal);

		if (mPlayer->getVitals().rest < 50.0f)
			mHungerLevel->setFillColor(mWarning);
		if (mPlayer->getVitals().rest < 10.0f)
			mHungerLevel->setFillColor(mDanger);
		if (mPlayer->getVitals().rest < 0.0f)
			mHungerLevel->setFillColor(mFatal);

		switch (mBoxSelected) {
		case 0:
			mBox0->setOutlineThickness(1.0f);
			mBox1->setOutlineThickness(0.0f);
			mBox2->setOutlineThickness(0.0f);
			mBox3->setOutlineThickness(0.0f);
			mBox4->setOutlineThickness(0.0f);
			break;
		case 1:
			mBox0->setOutlineThickness(0.0f);
			mBox1->setOutlineThickness(1.0f);
			mBox2->setOutlineThickness(0.0f);
			mBox3->setOutlineThickness(0.0f);
			mBox4->setOutlineThickness(0.0f);
			break;
		case 2:
			mBox0->setOutlineThickness(0.0f);
			mBox1->setOutlineThickness(0.0f);
			mBox2->setOutlineThickness(1.0f);
			mBox3->setOutlineThickness(0.0f);
			mBox4->setOutlineThickness(0.0f);
			break;
		case 3:
			mBox0->setOutlineThickness(0.0f);
			mBox1->setOutlineThickness(0.0f);
			mBox2->setOutlineThickness(0.0f);
			mBox3->setOutlineThickness(1.0f);
			mBox4->setOutlineThickness(0.0f);
			break;
		case 4:
			mBox0->setOutlineThickness(0.0f);
			mBox1->setOutlineThickness(0.0f);
			mBox2->setOutlineThickness(0.0f);
			mBox3->setOutlineThickness(0.0f);
			mBox4->setOutlineThickness(1.0f);
			break;
		}
	}
private:
	sf::Sprite *mHungerMeter, *mThirstMeter, *mHealthMeter, *mRestMeter;
	sf::RectangleShape *mBackBorder, *mBox0, *mBox1, *mBox2, *mBox3, *mBox4;
	sf::CircleShape *mHungerLevel, *mThirstLevel, *mHealthLevel, *mRestLevel;
	sf::Color mHealthy, mWarning, mDanger, mFatal;
	int mBoxSelected;
	Player* mPlayer;
};

#endif