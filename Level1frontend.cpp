#pragma once
#include "saadlevel1backend.h";
#include "Level 2 FrontEnd.h"
#include "player.h"

using namespace sf;
using namespace std;

class level1
{
	Event e;
	Music music;
	RenderWindow* window;
	Sprite* character;
	Player* player;
	Lane L;
	int count = 0;
	int inputCount = 0;
	//Music music;
	map<string, Texture*> textures;
	map<string, Sprite*> sprites;
	map<int, Texture*> MainMenutextures;
	map<int, Sprite*> MainMenuprites;
	Sprite* BackButtonSprite;
	Texture BackButtonTexture;
	Sprite* InstructionSprite;
	Texture InstructionTexture;
	vector<Vector2f> leftLaneTiles;
	vector<Vector2f> rightLaneTiles;
	bool FirstJump = true;
	bool FirstJumpCHpasUpdate = true;
	bool LaneFlag = true;
	bool mainMenuPressed = false;
	bool lostMessage = false;
	bool ShowInstrcution = false;

public:
	level1(RenderWindow* window, Sprite* character, Player* player)
		:window(window), character(character), player(player)
	{
		initTexture();
		initSprite();
	}

	void initSprite()
	{
		sprites["backgroundSprite"] = new Sprite(*textures["backgroundTexture"]);

		BackButtonSprite = new Sprite(BackButtonTexture);
		BackButtonSprite->setScale(0.5, 0.5);
		BackButtonSprite->setPosition(550, 670);

		InstructionSprite = new Sprite(InstructionTexture);
		InstructionSprite->setScale(0.75, 0.75);
		InstructionSprite->setPosition(300, 100);

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
		MainMenuprites[6]->setPosition(10 /*- (i * 10)*/, 600);

		//left tile
		sprites["leftTile1Sprite"] = new Sprite(*textures["leftTile1Texture"]);
		sprites["leftTile1Sprite"]->setScale(1, 1);
		sprites["leftTile1Sprite"]->setPosition(455, 620);
		leftLaneTiles.push_back(Vector2f(455, 620));

		sprites["leftTile2Sprite"] = new Sprite(*textures["leftTile2Texture"]);
		sprites["leftTile2Sprite"]->setScale(1, 1);
		sprites["leftTile2Sprite"]->setPosition(492, 544);
		leftLaneTiles.push_back(Vector2f(492, 544));

		sprites["leftTile3Sprite"] = new Sprite(*textures["leftTile3Texture"]);
		sprites["leftTile3Sprite"]->setScale(1, 1);
		sprites["leftTile3Sprite"]->setPosition(522, 482);
		leftLaneTiles.push_back(Vector2f(522, 482));

		sprites["leftTile4Sprite"] = new Sprite(*textures["leftTile4Texture"]);
		sprites["leftTile4Sprite"]->setScale(1, 1);
		sprites["leftTile4Sprite"]->setPosition(542, 432);
		leftLaneTiles.push_back(Vector2f(542, 432));

		//right tile
		sprites["rightTile1Sprite"] = new Sprite(*textures["rightTile1Texture"]);
		sprites["rightTile1Sprite"]->setScale(1, 1);
		sprites["rightTile1Sprite"]->setPosition(638, 620);
		rightLaneTiles.push_back(Vector2f(638, 620));

		sprites["rightTile2Sprite"] = new Sprite(*textures["rightTile2Texture"]);
		sprites["rightTile2Sprite"]->setScale(1, 1);
		sprites["rightTile2Sprite"]->setPosition(630, 544);
		rightLaneTiles.push_back(Vector2f(630, 544));

		sprites["rightTile3Sprite"] = new Sprite(*textures["rightTile3Texture"]);
		sprites["rightTile3Sprite"]->setScale(1, 1);
		sprites["rightTile3Sprite"]->setPosition(622, 482);
		rightLaneTiles.push_back(Vector2f(622, 482));

		sprites["rightTile4Sprite"] = new Sprite(*textures["rightTile4Texture"]);
		sprites["rightTile4Sprite"]->setScale(1, 1);
		sprites["rightTile4Sprite"]->setPosition(616.0f, 432.0f);
		rightLaneTiles.push_back(Vector2f(616, 632));

		//win loss
		sprites["YouLoseSprite"] = new Sprite(*textures["YouLoseTexture"]);
		sprites["YouLoseSprite"]->setScale(1, 1);
		sprites["YouLoseSprite"]->setPosition((window->getSize().x / 2.0f) - 300.0f, (window->getSize().y / 2.0f) - 50.0f);

		sprites["ReplaySprite"] = new Sprite(*textures["replayTexture"]);
		sprites["ReplaySprite"]->setScale(1, 1);
		sprites["ReplaySprite"]->setPosition((sprites["YouLoseSprite"]->getPosition().x / 2.0f) + 400, (sprites["YouLoseSprite"]->getPosition().y / 2.0f) + 300);

		sprites["YouWinSprite"] = new Sprite(*textures["YouWinTexture"]);
		sprites["YouWinSprite"]->setScale(1, 1);
		sprites["YouWinSprite"]->setPosition((window->getSize().x / 2.0f) - 300.0f, (window->getSize().y / 2.0f) - 50.0f);

		sprites["ContinueSprite"] = new Sprite(*textures["ContinueTexture"]);
		sprites["ContinueSprite"]->setScale(1, 1);
		sprites["ContinueSprite"]->setPosition((sprites["YouWinSprite"]->getPosition().x / 2.0f) + 400, (sprites["YouWinSprite"]->getPosition().y / 2.0f) + 300);

		//setting character initial position
		character->setScale(0.4f, 0.4f);
		character->setPosition(window->getSize().x / 2 - 30.0f, window->getSize().y / 2 + 200.0f);
	}

	void initTexture()
	{
		BackButtonTexture.loadFromFile("BACK BUTTON.png");
		InstructionTexture.loadFromFile("level 1 instructions.png");

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

		//left tiles
		textures["leftTile1Texture"] = new Texture();
		textures["leftTile1Texture"]->loadFromFile("tl1.png");

		textures["leftTile2Texture"] = new Texture();
		textures["leftTile2Texture"]->loadFromFile("tl2.png");

		textures["leftTile3Texture"] = new Texture();
		textures["leftTile3Texture"]->loadFromFile("tl3.png");

		textures["leftTile4Texture"] = new Texture();
		textures["leftTile4Texture"]->loadFromFile("tl4.png");

		//right tiles
		textures["rightTile1Texture"] = new Texture();
		textures["rightTile1Texture"]->loadFromFile("tr1.png");

		textures["rightTile2Texture"] = new Texture();
		textures["rightTile2Texture"]->loadFromFile("tr2.png");

		textures["rightTile3Texture"] = new Texture();
		textures["rightTile3Texture"]->loadFromFile("tr3.png");

		textures["rightTile4Texture"] = new Texture();
		textures["rightTile4Texture"]->loadFromFile("tr4.png");

		//win loss
		textures["YouLoseTexture"] = new Texture();
		textures["YouLoseTexture"]->loadFromFile("YOULOST.png");

		textures["replayTexture"] = new Texture();
		textures["replayTexture"]->loadFromFile("replay button.png");

		textures["YouWinTexture"] = new Texture();
		textures["YouWinTexture"]->loadFromFile("YOUWON.png");

		textures["ContinueTexture"] = new Texture();
		textures["ContinueTexture"]->loadFromFile("CONTINUW BUTTON.png");
	}

	void render()
	{
		window->clear();
		window->draw(*sprites["backgroundSprite"]);
		if (ShowInstrcution)
		{
			window->draw(*InstructionSprite);
			window->draw(*BackButtonSprite);
		}
		else
		{
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

			if (ShowInstrcution) {
				window->draw(*InstructionSprite);
				window->draw(*BackButtonSprite);
			}

			window->draw(*sprites["leftTile1Sprite"]);
			window->draw(*sprites["leftTile2Sprite"]);
			window->draw(*sprites["leftTile3Sprite"]);
			window->draw(*sprites["leftTile4Sprite"]);
			window->draw(*sprites["rightTile1Sprite"]);
			window->draw(*sprites["rightTile2Sprite"]);
			window->draw(*sprites["rightTile3Sprite"]);
			window->draw(*sprites["rightTile4Sprite"]);
			window->draw(*character);

			if (count > 4)
			{
				//you win sprite display
				window->clear();
				window->draw(*sprites["backgroundSprite"]);
				window->draw(*sprites["YouWinSprite"]);
				window->draw(*sprites["ContinueSprite"]);
				window->display();
				if (music.openFromFile("tees.wav"))
					music.play();
				while (music.getStatus() == sf::Music::Playing)
				{
				}
			}

			if (lostMessage)
			{
				//you lose sprite
				window->clear();
				window->draw(*sprites["backgroundSprite"]);
				window->draw(*sprites["YouLoseSprite"]);
				window->draw(*sprites["ReplaySprite"]);
				window->display();
				if (music.openFromFile("MOYEMOYE.wav"))
					music.play();
				while (music.getStatus() == sf::Music::Playing)
				{
				}
			}
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
			inputCount++;
			if (e.type == Event::Closed)
			{
				window->close();
			}
			handleKeyboardEvents();
			handleMouseEvents();
		}
	}

	//sprite is our character lane is our lane key is the key pressed
	//key=0->left->false
	//ket=1->right->true
	//key=2->up
	void UpdateCharacterPos(Sprite* character, bool lane, int key, int row)
	{
		//to make row start from 0
		--row;
		if (FirstJumpCHpasUpdate)
		{
			FirstJumpCHpasUpdate = false;
			// Handle initial jump positions based on lane
			if (lane) // right lane
			{
				cout << "\nright lane row 1";
				character->setPosition(rightLaneTiles[row].x + 30, rightLaneTiles[row].y - 86);
			}
			else // left lane
			{
				cout << "\nleft lane row 1";
				character->setPosition(leftLaneTiles[row].x + 40, leftLaneTiles[row].y - 86);
			}
		}
		else
		{
			if (row == 1)
				// Handle character movement based on lane and key
			{
				if (lane) // RIGHT lane
				{
					cout << "\nRIGHT LANE row 2";
					character->setPosition(rightLaneTiles[row].x + 20, rightLaneTiles[row].y - 91);
				}
				else // LEFT lane
				{
					cout << "\n LEFT LANE row 2";
					character->setPosition(leftLaneTiles[row].x + 25, leftLaneTiles[row].y - 99);
				}
			}
			else if (row == 2)
			{
				if (lane) // right lane
				{
					cout << "\nright LANE row 3";
					character->setPosition(rightLaneTiles[row].x + 5, rightLaneTiles[row].y - 110);
				}
				else // left lane
				{
					cout << "\nleft LANE row 3";
					character->setPosition(leftLaneTiles[row].x + 9, leftLaneTiles[row].y - 110);
				}
			}
			else if (row == 3)
			{
				if (lane) // right lane
				{
					cout << "\nright LANE row 4";
					character->setPosition(rightLaneTiles[row].x - 3, rightLaneTiles[row].y - 320);
				}
				else // left lane
				{
					cout << "\nleft lane row 4";
					character->setPosition(leftLaneTiles[row].x + 2, leftLaneTiles[row].y - 120);
				}
			}
		}
	}

	void handleKeyboardEvents()
	{
		if (e.type == Event::KeyPressed)
		{
			// Assuming you have a method to get the current tile and lane
			if (e.key.code == Keyboard::Left && count < 4)
			{
				if (FirstJump)
				{
					count++;
					//cout << "LEFT BUTTON PRESSED" << endl;
					FirstJump = false;
					LaneFlag = false;
					L.setLane(LaneFlag);
					//cout << "\n1st jump it is";
					//mov char to 1st tile of left lane on front end
					UpdateCharacterPos(character, LaneFlag, 0, count);
				}
				else if (L.getLane())
				{
					count++;
					// Move to the next tile on the left lane
					// You need to write the logic for this part
					//cout << "\n\nYOU ARE IN LEFT LANE";
					LaneFlag = false;
					UpdateCharacterPos(character, LaneFlag, 0, count);
					L.MoveDiagonal(false);
				}
				else {
					//sath deewar ky sath takranay ki animation
					L.MoveDiagonal(false);
				}

				if (!FirstJump && count < 4)
				{
					if (L.checkLoss())
					{
						// Game over logic
						cout << "\nYOU LOST" << endl;
						lostMessage = true;
					}
				}
			}
			else if (e.key.code == Keyboard::Right && count < 4)
			{
				if (FirstJump)
				{
					count++;
					cout << "\n\tRight button is pressed";
					cout << "\n1st jump it is";
					FirstJump = false;
					LaneFlag = true;
					UpdateCharacterPos(character, LaneFlag, 1, count);
					L.setLane(LaneFlag);
				}
				else if (!L.getLane())
				{
					count++;
					cout << "\n\nYOU now ARE IN right LANE";
					L.MoveDiagonal(true);
					LaneFlag = true;
					UpdateCharacterPos(character, LaneFlag, 1, count);
				}
				else {
					//sath deewar ky sath takranay ki animation
					L.MoveDiagonal(true);
				}
				if (!FirstJump && count < 4)
				{
					if (L.checkLoss())
					{
						// Game over logic
						cout << "\nYOU LOST" << endl;
						lostMessage = true;
					}
				}
			}
			else if (e.key.code == Keyboard::Up)
				if (FirstJump) {
					//Show message you need to select a lane first
					cout << "chose lane first" << endl;
				}
				else
				{
					count++;
					cout << "\nUP button pressed" << endl;
					L.MoveUp();
					UpdateCharacterPos(character, LaneFlag, 2, count);
				}
			if (!FirstJump && count < 4)
			{
				if (L.checkLoss())
				{
					// Game over logic
					character->rotate(0.60f);
					cout << "\nYOU LOST" << endl;
					lostMessage = true;
				}
			}
		}
	}

	void handleMouseEvents() {
		if (e.type == Event::MouseButtonPressed && e.key.code == Mouse::Left)
		{
			Vector2f mousePos = Vector2f(Mouse::getPosition(*window));
			if (MainMenuprites[5]->getGlobalBounds().contains(mousePos)) {
				window->close();
			}
			else if (MainMenuprites[4]->getGlobalBounds().contains(mousePos))
			{
				ShowInstrcution = true;
				mainMenuPressed = false;
			}
			else if (BackButtonSprite->getGlobalBounds().contains(mousePos))
			{
				ShowInstrcution = false;
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
			else if (sprites["ReplaySprite"]->getGlobalBounds().contains(mousePos) && count < 4)
			{
				cout << "\nReplaySprite pressed";
				//to reset varaibles at their initial position
				ReSetLane();
			}
			else if (sprites["ContinueSprite"]->getGlobalBounds().contains(mousePos))
			{
				cout << "\ncontinue sprite pressed";
				level2 l2(window, character, player);
				l2.runPage();
			}
		}
	}

	void ReSetLane()
	{
		count = 0;
		FirstJump = true;
		FirstJumpCHpasUpdate = true;
		LaneFlag = true;
		lostMessage = false;
		character->setScale(0.4f, 0.4f);
		character->setPosition(window->getSize().x / 2 - 30.0f, window->getSize().y / 2 + 200.0f);
	}

	~level1()
	{
		for (auto& pair : sprites)
		{
			delete pair.second;
		}
		for (auto& pair : textures)
		{
			delete pair.second;
		}
	}
};