#pragma once
#include "Level 2 FrontEnd.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "player.h"
#include "level1 Front End.h"
//#include "MainMenuHeaderFile.h"

using namespace sf;

class CharacterSelection
{
	int choice;
	Event e;
	RenderWindow* window;
	Player* player; // Pointer to Player
	Sprite* InstructionSprite;
	Texture InstructionTexture;
	Sprite* BackButtonSprite;
	Texture BackButtonTexture;
	map<int, Texture*> MainMenutextures;
	map<int, Sprite*> MainMenuprites;
	map<string, Texture*> textures;
	map<string, Sprite*> sprites;
	bool mainMenuPressed = false;
	bool ShowInstrcution = false;

public:
	CharacterSelection(RenderWindow* window, Player* player) :window(window), player(player)
	{
		initTexture();
		initSprite();
	}

	void initSprite()
	{
		sprites["backgroundSprite"] = new Sprite(*textures["backgroundTexture"]);

		InstructionSprite = new Sprite(InstructionTexture);
		InstructionSprite->setScale(0.75, 0.75);
		InstructionSprite->setPosition(300, 100);

		BackButtonSprite = new Sprite(BackButtonTexture);
		BackButtonSprite->setScale(0.5, 0.5);
		BackButtonSprite->setPosition(550, 670);

		MainMenuprites[1] = new Sprite(*MainMenutextures[1]);
		MainMenuprites[1]->setScale(1, 1);
		MainMenuprites[1]->setPosition(0, 0);

		MainMenuprites[2] = new Sprite(*MainMenutextures[2]);
		MainMenuprites[2]->setScale(1, 1);
		MainMenuprites[2]->setPosition(10, 50);

		for (int i = 3; i < 6; i++)
		{
			MainMenuprites[i] = new Sprite(*MainMenutextures[i]);
			MainMenuprites[i]->setScale(1, 1);
			MainMenuprites[i]->setPosition(10 /*- (i * 10)*/, 0 + (i * 50));
		}

		MainMenuprites[6] = new Sprite(*MainMenutextures[6]);
		MainMenuprites[6]->setScale(1, 1);
		MainMenuprites[6]->setPosition(10, 600);

		sprites["characterchoicetextSprite"] = new Sprite(*textures["characterchoicetextTexture"]);
		sprites["characterchoicetextSprite"]->setScale(1, 1);
		sprites["characterchoicetextSprite"]->setPosition(window->getSize().x / 2.0f - 340.0f, window->getSize().y / 2.0f - 100.0f);

		sprites["qurtChSprite"] = new Sprite(*textures["qurtChTexture"]);
		sprites["qurtChSprite"]->setScale(1, 1);
		sprites["qurtChSprite"]->setPosition(window->getSize().x / 2.0f - 350.0f, window->getSize().y / 2.0f);

		sprites["areebaChSprite"] = new Sprite(*textures["areebaChTexture"]);
		sprites["areebaChSprite"]->setScale(1, 1);
		sprites["areebaChSprite"]->setPosition(window->getSize().x / 2.0f - 80.0f, window->getSize().y / 2.0f);

		sprites["saadChSprite"] = new Sprite(*textures["saadChTexture"]);
		sprites["saadChSprite"]->setScale(1, 1);
		sprites["saadChSprite"]->setPosition(window->getSize().x / 2.0f + 280.0f, window->getSize().y / 2.0f);
	}

	void initTexture()
	{
		int i = 1;
		MainMenutextures[i] = new Texture();
		MainMenutextures[i]->loadFromFile("mainMenubg.png");
		++i;

		MainMenutextures[i] = new Texture();
		MainMenutextures[i]->loadFromFile("nav button.png");
		++i;

		MainMenutextures[i] = new Texture();
		MainMenutextures[i]->loadFromFile("main menu button.png");
		++i;

		MainMenutextures[i] = new Texture();
		MainMenutextures[i]->loadFromFile("How to play button.png");
		++i;

		MainMenutextures[i] = new Texture();
		MainMenutextures[i]->loadFromFile("Quit Button.png");
		++i;

		MainMenutextures[i] = new Texture();
		MainMenutextures[i]->loadFromFile("Note warning nav bar.png");

		textures["backgroundTexture"] = new Texture();
		textures["backgroundTexture"]->loadFromFile("Background.png");
		InstructionTexture.loadFromFile("Level 1 instructions.png");
		BackButtonTexture.loadFromFile("BACK BUTTON.png");

		textures["characterchoicetextTexture"] = new Texture();
		textures["characterchoicetextTexture"]->loadFromFile("choose character text.png");

		textures["qurtChTexture"] = new Texture();
		textures["qurtChTexture"]->loadFromFile("qurt.png");

		textures["areebaChTexture"] = new Texture();
		textures["areebaChTexture"]->loadFromFile("areeba.png");

		textures["saadChTexture"] = new Texture();
		textures["saadChTexture"]->loadFromFile("saad.png");
	}

	void render()
	{
		window->clear();
		window->draw(*sprites["backgroundSprite"]);
		if (mainMenuPressed)
		{
			for (int j = 1; j <= 6; j++)
			{
				window->draw(*MainMenuprites[j]);
			}
		}
		else
		{
			window->draw(*MainMenuprites[2]);
		}
		if (!ShowInstrcution)
		{
			window->draw(*sprites["characterchoicetextSprite"]);
			window->draw(*sprites["qurtChSprite"]);
			window->draw(*sprites["areebaChSprite"]);
			window->draw(*sprites["saadChSprite"]);
		}
		else
		{
			window->draw(*InstructionSprite);
			window->draw(*BackButtonSprite);
		}

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
		}
	}

	void handleMouseEvents()
	{
		if (e.type == Event::MouseButtonPressed && e.key.code == Mouse::Left)
		{
			Vector2f mousePos = Vector2f(Mouse::getPosition(*window));

			if (MainMenuprites[4]->getGlobalBounds().contains(mousePos)) {
				ShowInstrcution = true;
				mainMenuPressed = false;
			}
			else if (BackButtonSprite->getGlobalBounds().contains(mousePos))
			{
				ShowInstrcution = false;
			}
			else if (sprites["qurtChSprite"]->getGlobalBounds().contains(mousePos))
			{
				//send the selected character to player
				player->setcharacterChoice(1);
				player->SetUserData();
				//sending the character and window to level 1 class
				level1 l1(window, sprites["qurtChSprite"], player);

				l1.runPage();
			}
			else if (sprites["areebaChSprite"]->getGlobalBounds().contains(mousePos))
			{
				player->setcharacterChoice(2);
				player->SetUserData();
				level1 l1(window, sprites["areebaChSprite"], player);
				l1.runPage();
			}
			else if (sprites["saadChSprite"]->getGlobalBounds().contains(mousePos))
			{
				player->setcharacterChoice(3);
				player->SetUserData();
				level1 l1(window, sprites["saadChSprite"], player);
				l1.runPage();
			}
			else if (MainMenuprites[2]->getGlobalBounds().contains(mousePos)) {
				if (mainMenuPressed)
				{
					mainMenuPressed = false;
				}
				else {
					mainMenuPressed = true;
				}
			}
			else if (MainMenuprites[3]->getGlobalBounds().contains(mousePos))
			{
				//Navigation navObj(3, window, player);
			}
			else if (MainMenuprites[5]->getGlobalBounds().contains(mousePos)) {
				window->close();
			}
		}
	}

	~CharacterSelection()
	{
		// Destructor to release resources

		// Delete sprites
		for (auto& pair : sprites)
		{
			delete pair.second;
		}
		// Clear the map after deleting the objects
		sprites.clear();

		// Delete textures
		for (auto& pair : textures)
		{
			delete pair.second;
		}
		// Clear the map after deleting the objects
		textures.clear();
	}
};