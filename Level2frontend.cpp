#pragma once
#include "Level2 Backend.h"
#include "SFML/Graphics.hpp"
#include "characterSelection.h"
#include <ctime>
#include <cstdlib>
#include <vector>
#include <Windows.h>

using namespace std;
using namespace sf;

class level2 {
	ClassOfLane Lane1, Lane2, Lane3;
	RenderWindow* window;
	Sprite* character;
	Player* player;
	Event e;

	//Time timeInSeconds = sf::seconds(2.5f);
	Sprite* BackgroundSprite;
	Sprite RightLaneSprite;
	Sprite MidLaneSprite;
	Sprite LeftLaneSprite;
	Sprite* YouLoseSprite;
	Sprite* InstructionSprite;
	Texture InstructionTexture;
	Sprite* BackButtonSprite;
	Texture BackButtonTexture;
	Texture LossTexture;
	Texture BackgroundTexture;
	Texture RightTileTexture;
	Texture LeftTileTexture;
	Texture MidTileTexture;
	Texture SmallObstacleTexture;
	Texture WallObstacleTexture;
	Texture runningTexture1;
	Texture runningTexture2;
	Texture bg1;
	Texture bg2;
	Texture leftlane2;
	Texture rightlane2;
	Texture midlane2;
	float obstacleSpeed = 0.50f;
	//map<int, Sprite* > TileSprites;
	map<int, Texture*> MainMenutextures;
	map<int, Sprite*> MainMenuprites;
	//map<int, Sprite* > ObstacleSprites;
	vector<Sprite> ObstacleSprites;
	vector<int> ObstacleLocations;
	int TrackObstaclePos = 0;
	int index = 1;
	int NumOfObstacles = 0;
	bool left = false, right = false, mid = true;
	bool FirstJumpCHpasUpdate = true;
	bool Loss = false;
	bool mainMenuPressed = false;
	bool autoMoveStarted = false;
	bool ShowInstrcution = false;
	bool IsGamePaused = false;

	Clock runClock; // Keep track of the time since the last texture change
	Clock gameClock;
	Clock GanduClock;

	int score = 0;
	Clock scoreClock; // Clock to keep track of score increment intervals
	const int scoreRate = 1;
	const float runAnimationInterval = 0.1f;

	Text scoreText;
	Font gameFont;
public:
	level2(RenderWindow* window, Sprite* character, Player* player) :window(window), character(character), player(player)
	{
		srand(static_cast<unsigned int>(time(0)));
		Lane1.FunctionalitySimple(Lane1, Lane2, Lane3);
		initTexture();
		LoadingTileSprite();
		//cout << "\nobstacle terminated";
	}

	void initTexture()
	{
		//BackgroundTexture = new Texture();
		BackgroundTexture.loadFromFile("BACKGROUND LEVEL3.png");
		bg1.loadFromFile("lv3 bg1.png");
		bg2.loadFromFile("lv3 bg2.png");

		/////////////////////////
		//Loading Tile Textures//
		/////////////////////////
		RightTileTexture.loadFromFile("right lane.png");
		LeftTileTexture.loadFromFile("left lane.png");
		MidTileTexture.loadFromFile("mid lane.png");
		rightlane2.loadFromFile("right lane 2.png");
		leftlane2.loadFromFile("left lane 2.png");
		midlane2.loadFromFile("mid lane 2.png");

		if (player->getcharacterChoice() == 1)
		{
			runningTexture1.loadFromFile("qurt run 1.png");
			runningTexture2.loadFromFile("qurt run 2.png");
		}

		if (player->getcharacterChoice() == 2)
		{
			runningTexture1.loadFromFile("areeba run 1.png");
			runningTexture2.loadFromFile("areeba run 2.png");
		}

		if (player->getcharacterChoice() == 3)
		{
			runningTexture1.loadFromFile("saad run 1.png");
			runningTexture2.loadFromFile("saad run 2.png");
		}

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

		/////////////////////////////
		//Loading Obstacle Textures//
		/////////////////////////////
		SmallObstacleTexture.loadFromFile("small obstacle.png");
		WallObstacleTexture.loadFromFile("mid lane big obstacle.png");

		LossTexture.loadFromFile("YOULOST.png");
		InstructionTexture.loadFromFile("level 1 instructions.png");
		BackButtonTexture.loadFromFile("BACK BUTTON.png");
	}

	void LoadingTileSprite()
	{
		//background sprite
		BackgroundSprite = new Sprite();
		BackgroundSprite->setTexture(bg1);

		InstructionSprite = new Sprite(InstructionTexture);
		InstructionSprite->setScale(0.75, 0.75);
		InstructionSprite->setPosition(300, 100);

		BackButtonSprite = new Sprite(BackButtonTexture);
		BackButtonSprite->setScale(0.5, 0.5);
		BackButtonSprite->setPosition(550, 670);

		cout << "\n background loaded";

		RightLaneSprite.setTexture(RightTileTexture);
		MidLaneSprite.setTexture(MidTileTexture);
		LeftLaneSprite.setTexture(LeftTileTexture);

		RightLaneSprite.setPosition(900.0f - 105, 700.0f - 700.0f);
		MidLaneSprite.setPosition(900.0f - 350, 700.0f - 700.0f);
		LeftLaneSprite.setPosition(900.0f - 600, 700.0f - 700.0f);

		cout << "\n left tile loaded";

		// if character is set at mid tile
		character->setPosition(500.0f + 110.0f, 700-100.0f );
		character->setScale(0.5, 0.3f);

		// if character is set at left most tile 
		//character->setPosition(100.0f+100, 700-200.0f);
		// if character is set at right most tile  
		//character->setPosition(900.0f+100, 700-200.0f);

		//main menu sprites
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

		gameFont.loadFromFile("Arial.ttf");
		scoreText.setFont(gameFont);
		scoreText.setCharacterSize(24); // Or another appropriate size
		scoreText.setFillColor(Color::White); // Set the color
		scoreText.setPosition(1100, 10); // You might want to change the position

	}

	void LoadingObstacleSprite()
	{
		// ... [Initialization code]
		// Constants defining the size of tiles and the desired spacing
		int track = rand() % 3; // Randomly select one of the three tracks (0, 1, or 2)


		if (track == 0)
		{
			Sprite ObstacleSprite(SmallObstacleTexture);
			ObstacleSprite.setScale(0.75, 0.75);
			ObstacleSprite.setPosition(360.0f, 0.0f);
			ObstacleSprites.push_back(ObstacleSprite);
		}
		else if (track == 1)
		{
			Sprite ObstacleSprite(SmallObstacleTexture);
			ObstacleSprite.setScale(0.75, 0.75);
			ObstacleSprite.setPosition(612.0f, 0.0f);
			ObstacleSprites.push_back(ObstacleSprite);
		}
		else
		{
			Sprite ObstacleSprite(SmallObstacleTexture);
			ObstacleSprite.setScale(0.75, 0.75);
			ObstacleSprite.setPosition(855.0f, 0.0f);
			ObstacleSprites.push_back(ObstacleSprite);
		}

		YouLoseSprite = new Sprite(LossTexture);
		YouLoseSprite->setScale(1, 1);
		YouLoseSprite->setPosition((window->getSize().x / 2.0f) - 300.0f, (window->getSize().y / 2.0f) - 50.0f);


	}

	void render()
	{
		window->clear();
		window->draw(*BackgroundSprite);
		if (ShowInstrcution)
		{
			window->draw(*InstructionSprite);
			window->draw(*BackButtonSprite);
		}
		else
		{
			if (Loss)
			{
				window->clear();
				window->draw(*YouLoseSprite);
				sf::Music music;
				if (music.openFromFile("loose.wav")) {
					music.play();
					while (music.getStatus() == sf::Music::Playing) {
					}
				}
				window->display();
			}
			else
			{
				scoreText.setString("Score: " + std::to_string(score));
				window->draw(scoreText);
				window->draw(RightLaneSprite);
				window->draw(MidLaneSprite);
				window->draw(LeftLaneSprite);

				for (auto& i : ObstacleSprites)
				{
					window->draw(i);
				}
				window->draw(*character);
			}

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

		}
		window->display();
	}

	void runPage()
	{ while (window->isOpen())
		{
			processEvent();
			updateGame();
			render();
		}
		// to delete the lanes
	}

	void updateGame()
	{
		if (!IsGamePaused)
		{
			// Update the score based on time
			if (scoreClock.getElapsedTime().asMilliseconds() >= 300) { // If one second has passed
				score += scoreRate; // Increment the score
				scoreClock.restart(); // Restart the clock to count the next interval
			}

			// Check if 5 seconds have passed and start auto-moving obstacles
			if (gameClock.getElapsedTime().asSeconds() >= 2.0f && !autoMoveStarted)
			{
				autoMoveStarted = true;
				// Additional setup if needed when auto-move starts
			}

			if (autoMoveStarted)
			{
				// Code to automatically move the obstacles towards the character
				//moveObstacles();
				runCharacter();
				if (GanduClock.getElapsedTime().asMilliseconds() > 1000)
				{
					LoadingObstacleSprite();
					GanduClock.restart();
				}

				for (int i = 0; i < ObstacleSprites.size();i++)
				{
					ObstacleSprites[i].move(0, 10);
					if (ObstacleSprites[i].getPosition().y > 800)
					{
						ObstacleSprites.erase(ObstacleSprites.begin() + i);
						i--;
					}
				}
				//runBackground();
			}

			for (auto& i : ObstacleSprites)
			{
				if (i.getGlobalBounds().intersects(character->getGlobalBounds()))
				{
					Loss = true;
				}
			}
		}

		//... Any other game updates
	}

	void runCharacter()
	{
		if (runClock.getElapsedTime().asSeconds() >= runAnimationInterval) {
			// Reset the clock for the next frame
			runClock.restart();

			// Get the current texture of the character
			const Texture* currentTexture = character->getTexture();
			const Texture* currentBGTexture = BackgroundSprite->getTexture();
			const Texture* currentLLT = LeftLaneSprite.getTexture();
			const Texture* currentMLT = MidLaneSprite.getTexture();
			const Texture* currentRLT = RightLaneSprite.getTexture();
			// Switch the texture based on the current texture
			if (currentTexture == &runningTexture1) {
				character->setTexture(runningTexture2);
			}
			else {
				character->setTexture(runningTexture1);
			}

			if (currentBGTexture == &bg1)
			{
				BackgroundSprite->setTexture(bg2);
			}
			else {
				BackgroundSprite->setTexture(bg1);
			}

			if (currentLLT == &LeftTileTexture)
			{
				LeftLaneSprite.setTexture(leftlane2);
			}
			else
			{
				LeftLaneSprite.setTexture(LeftTileTexture);
			}

			if (currentMLT == &MidTileTexture)
			{
				MidLaneSprite.setTexture(midlane2);
			}
			else
			{
				MidLaneSprite.setTexture(MidTileTexture);
			}

			if (currentRLT == &RightTileTexture)
			{
				RightLaneSprite.setTexture(rightlane2);
			}
			else
			{
				RightLaneSprite.setTexture(RightTileTexture);
			}
		}
	}

	void processEvent()
	{
		while (window->pollEvent(e))
		{ if (e.type == Event::Closed)
			{ window->close();
			}
			handlemouseevents();
			handleKeyboardEvents();
		}
	}

	void UpdateCharPos()
	{
		// if character is set at mid tile
		if (mid)
		{
			//cout << "\ntrue mid";
			character->setPosition(500.0f + 115, 700 - 100.0f);
		}
		// if character is set at left most tile
		if (left)
		{
			//cout << "\ntrue left";
			character->setPosition(100.0f + 255, 700 - 100.0f);
		}
		// if character is set at right most tile
		if (right)
		{
			//cout << "\ntrue right";
			character->setPosition(900.0f-50 , 700 - 100.0f);
		}
	}

	void handlemouseevents()
	{
		if (e.type == Event::MouseButtonPressed && e.key.code == Mouse::Left)
		{
			Vector2f mousePos = Vector2f(Mouse::getPosition(*window));
			if (MainMenuprites[2]->getGlobalBounds().contains(mousePos)) {
				if (mainMenuPressed)
				{
					mainMenuPressed = false;
					IsGamePaused = false;
				}
				else {
					mainMenuPressed = true;
					IsGamePaused = true;
				}
			}
			else if (MainMenuprites[4]->getGlobalBounds().contains(mousePos)) {
				ShowInstrcution = true;
				mainMenuPressed = false;
			}
			else if (BackButtonSprite->getGlobalBounds().contains(mousePos))
			{
				ShowInstrcution = false;
			}

			if (MainMenuprites[5]->getGlobalBounds().contains(mousePos)) {
				window->close();
			}
		}
	}

	void handleKeyboardEvents()
	{
		if (e.type == Event::KeyPressed)
		{
			if (e.key.code == Keyboard::Left)
			{
				//1 indicates mid lane and 2 indicates left most lane
				if (Lane1.CurrentLane() == 1 || Lane1.CurrentLane() == 2)
				{
					if (Lane1.CurrentLane() == 1)
					{
						// Move to the tile on the left lane
						left = true;
						right = false;
						mid = false;
						Lane1.SetLane(0);
						UpdateCharPos();
					}
					else if (Lane1.CurrentLane() == 2)
					{
						// Move to the tile on the left lane
						mid = true; left = false;
						right = false;
						Lane1.SetLane(1);
						UpdateCharPos();
					}
					//move accepts only left and mid
				}
				else {
					//sath deewar ky sath takranay ki animation
				}
			}
			else if (e.key.code == Keyboard::Right)
			{
				if (Lane1.CurrentLane() == 0)
				{
					mid = true; left = false;
					right = false;
					Lane1.SetLane(1);
					//Lane1.Move(Lane1, Lane2, Lane3, left, mid);
					UpdateCharPos();
				}
				else if (Lane1.CurrentLane() == 1)
				{
					right = true;
					left = false;
					mid = false;
					Lane1.SetLane(2);
					//Lane1.Move(Lane1, Lane2, Lane3, left, mid);
					UpdateCharPos();
				}
				//}
				else {
					//sath deewar ky sath takranay ki animation
				}
			}
		}
	}

	//~level2() {
	//	// ...
	//	// Delete TileSprites
	//	for (auto& pair : TileSprites)
	//	{
	//		delete pair.second;
	//	}
	//	for (auto& pair : ObstacleSprites)
	//	{
	//		delete pair.second;
	//	}
	//	delete BackgroundSprite;
	//	delete &ObstacleLocations;
	//	delete &Lane1;
	//	delete &Lane2;
	//	
	//}
	delete &Lane3;
};