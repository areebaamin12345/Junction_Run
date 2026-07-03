#pragma once
#include "SignUp.h"
#include "LoginPage.h"

class LoginSignup
{
public:
	LoginPage* LP;
	SignUpPage* SingUpObj;
	RenderWindow *window;
	map<string, Texture*> texture;
	map<string, Sprite*> sprite;
	Event e;

	LoginSignup(RenderWindow* window)
	{
		this->window = window;
		initTexture();
		initSprite();
	}

	void initTexture()
	{
		texture["backgroundTexture"] = new Texture();
		texture["backgroundTexture"]->loadFromFile("Background.png");
		texture["LoginTexture"] = new Texture();
		texture["LoginTexture"]->loadFromFile("LOGINBUTTON.png");

		texture["SignUPTexture"] = new Texture();
		texture["SignUPTexture"]->loadFromFile("SIGNUPBUTTON.png");
	}

	void initSprite()
	{
		sf::Vector2u windowSize = window->getSize();
		sprite["backgroundSprite"] = new Sprite(*texture["backgroundTexture"]);
		sprite["LoginSprite"] = new Sprite(*texture["LoginTexture"]);
		sprite["LoginSprite"]->setScale(1, 1);
		sprite["LoginSprite"]->setPosition(window->getSize().x / 2.0f - 110.0f, window->getSize().y / 2.0f - 30.0f);
		sprite["SignUPSprite"] = new Sprite(*texture["SignUPTexture"]);
		sprite["SignUPSprite"]->setScale(1, 1);
		sprite["SignUPSprite"]->setPosition(window->getSize().x / 2.0f - 110.0f, window->getSize().y / 2.0f + 40.0f);
	}

	void handleMouseEvents()
	{
		if (e.type == Event::MouseButtonPressed && e.key.code == Mouse::Left)
		{
			Vector2f mousePos = Vector2f(Mouse::getPosition(*window));

			if (sprite["LoginSprite"]->getGlobalBounds().contains(mousePos))
			{
				LP = new LoginPage(window);
				LP->runPage();
			}

			if (sprite["SignUPSprite"]->getGlobalBounds().contains(mousePos))
			{
				SingUpObj = new SignUpPage(window);
				SingUpObj->runPage();
			}
		}
	}

	void processEvent()
	{
		while (window->pollEvent(e))
		{
			if (e.type == Event::Closed)
			{
				window->close();
			}
			handleMouseEvents();
		}
	}

	void Render()
	{
		window->clear();
		window->draw(*sprite["backgroundSprite"]);
		window->draw(*sprite["SignUPSprite"]);
		window->draw(*sprite["LoginSprite"]);
		window->display();
	}

	void runPage()
	{
		while (window->isOpen())
		{
			processEvent();
			Render();
		}
	}

	~LoginSignup()
	{
		// Destructor to release resources

		// Delete sprites
		for (auto& pair : sprite)
		{
			delete pair.second;
		}
		// Clear the map after deleting the objects
		sprite.clear();

		// Delete textures
		for (auto& pair : texture)
		{
			delete pair.second;
		}
		// Clear the map after deleting the objects
		texture.clear();
	}
};