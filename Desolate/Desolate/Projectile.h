#ifndef PROJECTILE_H
#define PROJECTILEH

class Projectile {
public:

		/*Projectile Class Needs atleast:
			- Window pointer
			- TextureManager pointer
			- Texture Name
			- Start Position
			- Start Rotation
			- Start Speed
			- Start Damage
			- Start Decay Time
	*/

	Projectile(sf::RenderWindow* window, TextureManager* textureManager, std::string bulletSprite, sf::Vector2f startPos, float rotation, float speed, float damage, float decayTime) {
		mWindow = window;
		mTextureManager = textureManager;
		mSprite.setPosition(startPos);
		mSprite.setRotation(rotation);
		mSprite.setTexture(mTextureManager->getTexture(bulletSprite));
		mSprite.scale(2.0f, 2.0f);
		mProjectileSpeed = speed;
		mProjectileDamage = damage;
		mProjectileDecayTime = decayTime;
		mIsDecayed = false;
	}

	void update(float deltaTime) {
		if (mProjectileClock.getElapsedTime().asSeconds() > mProjectileDecayTime) {
			mIsDecayed = true;
		}
		else {
			sf::Vector2f bulletMovement(static_cast<float>(cos(3.14 *  mSprite.getRotation() / 180) * mProjectileSpeed) * deltaTime, static_cast<float>(sin(3.14 * mSprite.getRotation() / 180) * mProjectileSpeed) * deltaTime);
			mSprite.move(-bulletMovement);
		}
	}

	void render() {
		if (!mIsDecayed)
			mWindow->draw(mSprite);
	}

	sf::Sprite* getSprite() {
		return &mSprite;
	}
	bool isDecayed() {
		return mIsDecayed;
	}
private:
	sf::RenderWindow*   mWindow;
	TextureManager*		mTextureManager;
	sf::Sprite			mSprite;
	sf::Clock			mProjectileClock;

	float   mProjectileSpeed,
			mProjectileDamage,
			mProjectileDecayTime;
	bool    mIsDecayed;
};

#endif