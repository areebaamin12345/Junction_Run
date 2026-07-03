#pragma once
#include "player.h"
#include "characterSelection.h"

class LoginPage
{
public:
	RenderWindow* window;
	map<string, Texture*> textures;
	map<string, Sprite*> sprites;
	Event e;
	Text nameText;
	Text passText;
	Font font;
	string UserEmail;
	string userPassword;
	string maskPassword;
	Clock clock;
	RectangleShape cursor;
	Player playa;
	bool Loginbutton = false;
	bool PassEmail = false;
	bool nameBox = false;
	bool cursorVisible = false;
	bool passBox = false;

	LoginPage() :window(), e()
	{
	}

	LoginPage(RenderWindow* window)
	{
		this->window = window;
		initTexture();
		initSprite();
		initVariable();
		initText();
	}

	void initTexture()
	{
		textures["backgroundTexture"] = new Texture();
		textures["backgroundTexture"]->loadFromFile("Background.png");
		textures["EmailTexture"] = new Texture();
		textures["EmailTexture"]->loadFromFile("email text.png");

		textures["passTexture"] = new Texture();
		textures["passTexture"]->loadFromFile("password text.png");

		textures["nameSpace"] = new Texture;
		textures["nameSpace"]->loadFromFile("b1.png");
		textures["loginSpace"] = new Texture;
		textures["loginSpace"]->loadFromFile("b2.png");
		textures["loginButtonTexture"] = new Texture;
		textures["loginButtonTexture"]->loadFromFile("Submit.png");
	}

	void initSprite()
	{
		sprites["backgroundSprite"] = new Sprite(*textures["backgroundTexture"]);

		sprites["EmailSprite"] = new Sprite(*textures["EmailTexture"]);
		sprites["EmailSprite"]->setScale(1, 1);
		sprites["EmailSprite"]->setPosition(window->getSize().x / 2.0f - 260.0f, window->getSize().y / 2.0f - 10.0f);

		sprites["passSprite"] = new Sprite(*textures["passTexture"]);
		sprites["passSprite"]->setScale(1, 1);
		sprites["passSprite"]->setPosition(window->getSize().x / 2.0f - 344.0f, window->getSize().y / 2.0f + 66.0f);

		sprites["nameSprite"] = new Sprite(*textures["nameSpace"]);
		sprites["nameSprite"]->setScale(1, 1);
		sprites["nameSprite"]->setOrigin(textures["nameSpace"]->getSize().x / 2.0f, textures["nameSpace"]->getSize().y / 2.0f);
		sprites["nameSprite"]->setPosition(window->getSize().x / 2.0f + 30.0f, window->getSize().y / 2.0f);

		sprites["loginSprite"] = new Sprite(*textures["loginSpace"]);
		sprites["loginSprite"]->setScale(1, 1);
		sprites["loginSprite"]->setOrigin(textures["loginSpace"]->getSize().x / 2.0f, textures["loginSpace"]->getSize().y / 2.0f);
		sprites["loginSprite"]->setPosition(window->getSize().x / 2.0f + 30.0f, window->getSize().y / 2.0f + 80.0f);

		sprites["loginButtonSprite"] = new Sprite(*textures["loginButtonTexture"]);
		sprites["loginButtonSprite"]->setScale(1, 1);
		sprites["loginButtonSprite"]->setOrigin(textures["loginButtonTexture"]->getSize().x / 2.0f, textures["loginButtonTexture"]->getSize().y / 2.0f);
		sprites["loginButtonSprite"]->setPosition(window->getSize().x / 2.0f, window->getSize().y / 2.0f + 130.0f);

		cursor.setSize(sf::Vector2f(5.f, 20.f));
		cursor.setFillColor(Color::White);
		cursor.setPosition(sprites["nameSprite"]->getGlobalBounds().left + 10.0f, sprites["nameSprite"]->getGlobalBounds().top + 15.0f);
	}

	void initVariable()
	{
		nameBox = true;
		passBox = false;
		cursorVisible = true;
	}

	void initText()
	{
		font.loadFromFile("Arial.ttf");

		nameText.setFont(font);
		nameText.setCharacterSize(25);
		nameText.setFillColor(Color::White);
		nameText.setPosition(sprites["nameSprite"]->getGlobalBounds().left + 6, sprites["nameSprite"]->getGlobalBounds().top + 12);

		passText.setFont(font);
		passText.setCharacterSize(25);
		passText.setFillColor(Color::White);
		passText.setPosition(sprites["loginSprite"]->getGlobalBounds().left + 6, sprites["loginSprite"]->getGlobalBounds().top + 15);
	}

	void handleMouseEvents()
	{
		if (e.type == Event::MouseButtonPressed && e.key.code == Mouse::Left)
		{
			Vector2f mousePos = Vector2f(Mouse::getPosition(*window));

			if (sprites["nameSprite"]->getGlobalBounds().contains(mousePos))
			{
				nameBox = true;
				passBox = false;
			}

			if (sprites["loginSprite"]->getGlobalBounds().contains(mousePos))
			{
				nameBox = false;
				passBox = true;
			}

			if (sprites["loginButtonSprite"]->getGlobalBounds().contains(mousePos))
			{
				Loginbutton = true;
				//check if email is found. If not take input again
				playa.SetUserData();
				if (!EmailAndPassVerification(UserEmail, userPassword))
				{
					PassEmail = true;
				}
				else
				{
					PassEmail = false;
					CharacterSelection selectCharacter(window, &playa);
					selectCharacter.runPage();
				}
			}
		}
	}

	void render()
	{
		window->clear();
		window->draw(*sprites["backgroundSprite"]);
		window->draw(*sprites["nameSprite"]);
		window->draw(*sprites["loginSprite"]);
		window->draw(*sprites["loginButtonSprite"]);
		window->draw(*sprites["EmailSprite"]);
		window->draw(*sprites["passSprite"]);
		window->draw(nameText);
		window->draw(passText);
		UpdateCursor();
		window->display();
	}

	void runPage()
	{
		while (window->isOpen())
		{
			processEvent();
			render();
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
			handleTextEvents();
		}
	}

	void UpdateCursor()
	{
		if (nameBox)
		{
			cursor.setPosition(nameText.findCharacterPos(UserEmail.size()).x + 5, nameText.findCharacterPos(UserEmail.size()).y);
		}

		if (passBox)
		{
			if (maskPassword.empty())
			{
				cursor.setPosition(sprites["loginSprite"]->getGlobalBounds().left + 10, sprites["loginSprite"]->getGlobalBounds().top + 17);
			}
			else
			{
				cursor.setPosition(passText.findCharacterPos(maskPassword.size()).x + 5, passText.findCharacterPos(maskPassword.size()).y);
			}
		}

		if (cursorVisible)
		{
			window->draw(cursor);
		}

		if (clock.getElapsedTime().asMilliseconds() > 500)
		{
			cursorVisible = !cursorVisible;
			clock.restart();
		}
	}

	bool EmailAndPassVerification(string EMAIL, string PASS)
	{
		if (EMAIL.empty() == false && PASS.empty() == false)
		{
			if (playa.SearchData(EMAIL, PASS))
			{
				cout << "true email";
				return true;
			}
		}
		else
		{
			cout << "false email";
			return false;
		}
		return false;
	}

	void handleTextEvents()
	{
		if (e.type == Event::TextEntered)
		{
			if (e.text.unicode < 128 && e.text.unicode != 8 && e.text.unicode != 13)
			{
				if (nameBox && nameText.getGlobalBounds().width < (sprites["nameSprite"]->getGlobalBounds().width - 47))
				{
					UserEmail += char(e.text.unicode);
					nameText.setString(UserEmail);
				}

				if (passBox && passText.getGlobalBounds().width < (sprites["loginSprite"]->getGlobalBounds().width - 50))
				{
					userPassword += char(e.text.unicode);
					maskPassword += '*';
					passText.setString(maskPassword);
				}
			}
			else if (e.text.unicode == 13)
			{
				nameBox = false;
				passBox = false;
			}
			if (e.text.unicode == 8)
			{
				if (nameBox && !UserEmail.empty())
				{
					UserEmail.pop_back();
					nameText.setString(UserEmail);
				}
				if (passBox && !maskPassword.empty() && !userPassword.empty())
				{
					maskPassword.pop_back();
					userPassword.pop_back();
					passText.setString(maskPassword);
				}
			}
			else if (PassEmail && Loginbutton && !userPassword.empty() && !maskPassword.empty())
			{
				UserEmail.clear();
				userPassword.clear();
				maskPassword.clear();
				nameText.setString(UserEmail);
				passText.setString(maskPassword);
				Loginbutton = false;
			}
		}
	}

	~LoginPage()
	{
		for (auto& pair : textures)
		{
			delete pair.second;
		}
		for (auto& pair : sprites)
		{
			delete pair.second;
		}
		delete window;
	}
};