#pragma once
using namespace std;

class Tile {
public:
	int data = 0;
	Tile* next;
	Tile* prev;
	Tile* right;
	Tile* left;
	Tile(int data)
	{
		this->data = data;
		next = nullptr;
		right = nullptr;
		left = nullptr;
		prev = nullptr;
	}
	~Tile() {}
};

class ClassOfLane {
	int NumberOfMovement = 1;
	int Tiles = 1;
	int Lane = 1;
	int Points = 0;
	Tile* head;
	Tile* tail;

	bool ContiueMakingTiles = false;
public:
	ClassOfLane()
	{
		head = nullptr;
		tail = nullptr;
	}

	void AddTileLinear(int Data)
	{
		Tile* NewTile = new Tile(Data);
		if (head == nullptr && tail == nullptr)
		{
			head = NewTile;
			tail = NewTile;
		}
		else
		{
			tail->next = NewTile;
			NewTile->prev = tail;
			tail = NewTile;
		}
	}

	void SetLane(int lane)
	{
		Lane = lane;
	}

	int CurrentLane()
	{
		return Lane;
	}

	int CurrentTile()
	{
		Tile* TrackTile = head;
		//while()
		return Tiles;
	}

	void Makelink(ClassOfLane &l1, ClassOfLane &l2, ClassOfLane &l3/*,int startpos*/)
	{
		Tile* lane1Head = l1.head;
		Tile* lane2Head = l2.head;
		Tile* lane3Head = l3.head;

		while (lane1Head != nullptr && lane2Head != nullptr && lane3Head != nullptr)
		{
			lane1Head->right = lane2Head;

			lane2Head->right = lane3Head;
			lane2Head->left = lane1Head;

			lane3Head->left = lane2Head;

			lane1Head = lane1Head->next;
			lane2Head = lane2Head->next;
			lane3Head = lane3Head->next;
		}
	}

	int Move(ClassOfLane &l1, ClassOfLane &l2, ClassOfLane &l3, bool Left, bool mid)
	{
		int step = 1;
		Tile* l1Head = l1.head;
		Tile* l2Head = l2.head;
		Tile* l3Head = l3.head;

		//tile it contains data of the cuurent position of character
		while (step != Tiles && l1Head != nullptr)
		{
			l1Head = l1Head->next;
			l2Head = l2Head->next;
			l3Head = l3Head->next;
			step++;
		}

		if (l1Head != nullptr && l2Head->next != nullptr && l3Head != nullptr)
		{
			//if lane is left move ahead and update value of tiles
			if (Left && l1Head->next->data != -1)
			{
				l1Head = l1Head->next;
				Tiles = l1Head->data;
				cout << "\n\tmoved in left lane at " << Tiles;
				Points += l1Head->data;
				Lane = 0;
			}

			//if lane is mid move ahead and update value of tiles
			else if (mid && l2Head->next->data != -1)
			{
				l2Head = l2Head->next;

				Tiles = l2Head->data;

				Tiles = Tiles - 9;
				cout << "\n\tmoved in mid lane at " << Tiles;
				Points += l2Head->data;
				Lane = 1;
			}
			//if lane is right move ahead and update value of tiles
			else if (!Left && !mid && l3Head->next->data != -1) {

				l3Head = l3Head->next;
				Tiles = l3Head->data;
				Tiles = Tiles - 18;

				cout << "\n\tmoved in right lane at " << Tiles;
				Points += l3Head->data;
				Lane = 2;
			}

			else
			{
				Tiles = Tiles + 1;
				//PlaySound(TEXT("bomb.wav"), NULL, SND_SYNC);
				cout << "\nSTOP You stepped on wrong point!\n";
				//game lost
				return 100;
			}
			//game is continued
			//cout << "\n Lane is " << Lane;
			return 0;
		}

		else /*if(Points>=500)*/ {
			cout << "\n\n\t****Congratulations you won with 500 points!****\n";

			return 1;
		}


	}

	int Jump(ClassOfLane &l1, ClassOfLane &l3, bool Left, bool right) {
		int step = 1;
		Tile* l1Head = l1.head;
		Tile* l3Head = l3.head;
		while (step != Tiles && l1Head != nullptr)
		{
			l1Head = l1Head->next;
			l3Head = l3Head->next;
			step++;
		}

		if (l1Head != nullptr && l3Head->next != nullptr)
		{
			//either stepped on garbage value or jummped in middle lane
			if (l1Head->next->next != nullptr && l3Head->next->next != nullptr)
			{
				if ((Left && l1Head->next->next->data == -1) || (right && l3Head->next->next->data == -1))
				{
					Tiles = Tiles + 1;
					//PlaySound(TEXT("bomb.wav"), NULL, SND_SYNC);
					cout << "\nSTOP You stepped on wrong point!\n";
					//game lost
					return 100;
				}
				//if lane is left move two postions ahead
				//update value of tiles
				else if (Left)
				{
					if (l1Head->next->data == -1)
					{
						//as jumped over an obstacle
						Points++;
					}
					//just iterate to put correct values in Tiles variable
					l1Head = l1Head->next;
					l1Head = l1Head->next;

					Tiles = l1Head->data;
					cout << "\n\njumped in left lane at " << Tiles;
					Points += l1Head->data;

				}
				//if lane is right move two postions ahead
				//also update value of tiles
				else if (right)
				{
					if (l3Head->next->data == -1)
					{
						//as jumped over an obstacle
						Points++;
					}
					l3Head = l3Head->next;
					l3Head = l3Head->next;
					Tiles = l3Head->data;
					Tiles = Tiles - 18;

					cout << "\n\njumped in right lane at " << Tiles;
					Points += l3Head->data;

				}
				//jumped in mid lane
				else {
					Tiles = Tiles + 1;
					//PlaySound(TEXT("bomb.wav"), NULL, SND_SYNC);
					cout << "\nCant jump is mid lane!\n";
					//game lost
					return 100;
				}
				//game is continued
			}
			//cout << "\n Lane is " << Lane;
			return 0;
		}
		else {
			cout << "\n\n\t****Congratulations you won!****\n";
			//cout << "\n\nyoure at pos " << l3Head->prev->data;
			//PlaySound(TEXT("SuccessWav.wav"), NULL, SND_SYNC);
			// 1 indicates victory
			//cout << "\n Lane is " << Lane;
			return 1;
		}

	}
	//void Functionality(ClassOfLane Lane1, ClassOfLane Lane2, ClassOfLane Lane3)
	//{
	//	//using lane1 because lane1 has starting value in every iteration
	//	if (Lane1.tail->data>9) {
	//		//start lane 1 from +10 if a linkedlist is already made
	//		ContiueMakingTiles = true;
	//	}
	//	// 3 loops to initialize diff values in each lane
	//	//NumberOfMovement is initially initialised with 1
	//	// 1 1<1+10 
	//	for (int i = NumberOfMovement; i < NumberOfMovement +10; i++)
	//	{
	//		Lane1.AddTileLinear(i);
	//	}
	//	//NumberOfMovement = 1+10
	//	NumberOfMovement += 10;
	//	// 11 11<11+10
	//	for (int i = NumberOfMovement; i < NumberOfMovement + 10; i++)
	//	{
	//		Lane2.AddTileLinear(i);
	//	}
	//	NumberOfMovement += 10;
	//	// 21 21<31
	//	for (int i = NumberOfMovement; i < NumberOfMovement + 10; i++)
	//	{
	//		Lane3.AddTileLinear(i);
	//	}
	//	//NumberOfMovement =31
	//	NumberOfMovement += 10;

	//	// all values are set now link them and set obstacles
	//	Lane1.InputObstacle(Lane1, Lane2, Lane3, Lane1.tail->data);
	//	
	//	Lane1.Makelink(Lane1, Lane2, Lane3, Lane1.tail->data);
	//	
	//	return;
	//}

	void FunctionalitySimple(ClassOfLane &Lane1, ClassOfLane &Lane2, ClassOfLane &Lane3)
	{

		for (int i = 1; i <10; i++)
		{
			Lane1.AddTileLinear(i);
		}

		for (int i = 10; i <19; i++)
		{
			Lane2.AddTileLinear(i);
		}

		for (int i = 19; i < 28; i++)
		{
			Lane3.AddTileLinear(i);
		}

		//Lane1.InputObstacle(Lane1, Lane2, Lane3, Lane1.head->data);

		Lane1.Makelink(Lane1, Lane2, Lane3);
		return;
	}

	void InputObstacle(ClassOfLane &l1, ClassOfLane &l2, ClassOfLane l3/*, int StartPos*/)
	{
		int counter = 1;
		Tile* L1 = l1.head;
		Tile* L2 = l2.head;
		Tile* L3 = l3.head;
		//if (ContiueMakingTiles)
		//{
		//	//just to bring our L1, L2, l3 on straing point appened linked list
		//	while (counter != StartPos)
		//	{
		//		L1 = L1->next;
		//		L2 = L2->next;
		//		L3 = L3->next;
		//		counter++;
		//	}
		//}
		while (L1 != nullptr && L2 != nullptr && L3!= nullptr)
		{
			//condition for lane 1
			if (L1->data % 3 == 0 && L1->next!= nullptr)
			{
				L1->data = -1;
			}
			//condition for lane 2
			if (L2->data % 2 == 0 && L2->data%3==0)
			{
				L2->data = -1;
			}
			//condition for lane 3
			if (L3->data % 2 == 0)
			{
				L3->data = -1;
			}
			if (L1->data == -1 && L2->data == -1 && L3->data==-1)
			{
				L2->data = L2->prev->data + 1;
			}
			L1 = L1->next;
			L2 = L2->next;
			L3 = L3->next;
		}
	}

	void SetObstacle(int Pos, ClassOfLane& Lane)
	{
		Tile* SearchNode = Lane.head;
		//cout << Pos;
		while (SearchNode != nullptr)
		{
			if (SearchNode->data == Pos)
			{
				SearchNode->data = -1;
				return;
			}
			SearchNode = SearchNode->next;
		}
		return;
	}

	void display()
	{
		Tile* DisplayTile = head;
		cout << endl;
		while (DisplayTile != nullptr)
		{
			cout << DisplayTile->data << " ";
			DisplayTile = DisplayTile->next;
		}
	}
	~ClassOfLane() {

	}

};