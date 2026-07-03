#pragma once
#include "LoginPage.h"

class SignUpPage
{
	LoginPage LP;
	RenderWindow* window;
	Event e;

	bool PassEmailFlag = false;
	bool nameBox = false;
	bool cursorVisible = false;
	bool passBox = false;
	bool LoginButton = false;

public:
	SignUpPage(RenderWindow *window)
	{
		this->window = window;
		LP.initTexture();
		LP.initSprite();
		LP.initVariable();
		LP.initText();
	}

	void handleMouseEvents()
	{
		if (e.type == Event::MouseButtonPressed && e.key.code == Mouse::Left)
		{
			Vector2f mousePos = Vector2f(Mouse::getPosition(*window));

			if (LP.sprites["nameSprite"]->getGlobalBounds().contains(mousePos))
			{
				nameBox = true;
				passBox = false;
			}

			if (LP.sprites["loginSprite"]->getGlobalBounds().contains(mousePos))
			{
				nameBox = false;
				passBox = true;
			}

			if (LP.sprites["loginButtonSprite"]->getGlobalBounds().contains(mousePos))
			{
				LoginButton = true;
				if (!Email_check(LP.UserEmail) || !Password_Check(LP.userPassword))
				{
					PassEmailFlag = true;
				}
				else
				{
					PassEmailFlag = false;
					CharacterSelection selectCharacter(window, &LP.playa);
					selectCharacter.runPage();
				}
			}
		}
	}

	void render()
	{
		window->clear();
		window->draw(*LP.sprites["backgroundSprite"]);
		window->draw(*LP.sprites["nameSprite"]);
		window->draw(*LP.sprites["loginSprite"]);
		window->draw(*LP.sprites["loginButtonSprite"]);
		window->draw(*LP.sprites["EmailSprite"]);
		window->draw(*LP.sprites["passSprite"]);
		window->draw(LP.nameText);
		window->draw(LP.passText);
		Updatecursor();
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

	void Updatecursor()
	{
		if (nameBox)
		{
			LP.cursor.setPosition(LP.nameText.findCharacterPos(LP.UserEmail.size()).x + 5, LP.nameText.findCharacterPos(LP.UserEmail.size()).y);
		}

		if (passBox)
		{
			if (LP.maskPassword.empty())
			{
				LP.cursor.setPosition(LP.sprites["loginSprite"]->getGlobalBounds().left + 10, LP.sprites["loginSprite"]->getGlobalBounds().top + 17);
			}
			else
			{
				LP.cursor.setPosition(LP.passText.findCharacterPos(LP.maskPassword.size()).x + 5, LP.passText.findCharacterPos(LP.maskPassword.size()).y);
			}
		}

		if (LP.cursorVisible)
		{
			window->draw(LP.cursor);
		}

		if (LP.clock.getElapsedTime().asMilliseconds() > 500)
		{
			LP.cursorVisible = !LP.cursorVisible;
			LP.clock.restart();
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

	bool Email_check(string str)
	{
		for (char c : str)
		{
			if (c == '@')
			{
				for (char c : str)
				{
					if (c == '.')
					{
						return true;
					}
				}
			}
		}
		return false;
	}

	bool Password_Check(string pass)
	{
		for (char c : pass)
		{
			if (c >= 65 && c <= 90)
			{
				for (char c : pass)
				{
					if (c >= 97 && c <= 122)
					{
						for (char c : pass)
						{
							if (c >= 33 && c <= 47 || (c == 64))
							{
								return true;
							}
						}
					}
				}
			}
		}
		return false;
	}

	void handleTextEvents()
	{
		if (e.type == Event::TextEntered)
		{
			if (e.text.unicode < 128 && e.text.unicode != 8 && e.text.unicode != 13)
			{
				if (nameBox && LP.nameText.getGlobalBounds().width < (LP.sprites["nameSprite"]->getGlobalBounds().width - 47))
				{
					LP.UserEmail += char(e.text.unicode);
					LP.nameText.setString(LP.UserEmail);
					LP.playa.setUsername(LP.UserEmail);
				}

				if (passBox && LP.passText.getGlobalBounds().width < (LP.sprites["loginSprite"]->getGlobalBounds().width - 50))
				{
					LP.userPassword += char(e.text.unicode);
					LP.maskPassword += '*';
					LP.passText.setString(LP.maskPassword);
					LP.playa.setPassword(LP.userPassword);
				}
			}
			else if (e.text.unicode == 13)
			{
				nameBox = false;
				passBox = false;
			}
			if (e.text.unicode == 8)
			{
				if (nameBox && !LP.UserEmail.empty())
				{
					LP.UserEmail.pop_back();
					LP.nameText.setString(LP.UserEmail);
				}
				if (passBox && !LP.maskPassword.empty() && !LP.userPassword.empty())
				{
					LP.maskPassword.pop_back();
					LP.userPassword.pop_back();
					LP.passText.setString(LP.maskPassword);
				}
			}
			else if (PassEmailFlag && LoginButton && !LP.userPassword.empty() && !LP.maskPassword.empty())
			{
				LP.UserEmail.clear();
				LP.userPassword.clear();
				LP.maskPassword.clear();
				LP.nameText.setString(LP.UserEmail);
				LP.passText.setString(LP.maskPassword);
				LoginButton = false;
			}
		}
	}

	~SignUpPage()
	{
		// Destructor to release resources
	}
};