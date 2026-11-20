#include<SFML/Graphics.hpp>
#include<iostream>
#include<fstream>
#include<string>

using namespace sf;
using namespace std;

//constants
const int Player_Speed = 8;
//constants


Texture BOB_T("Textures/BOB.png");
Sprite bob(BOB_T);
int bobRowStrt, bobColStrt, bobRow, bobCol;

Texture Fish_T("Textures/fish.png");
Sprite fish(Fish_T);


Texture Tuna_T("Textures/tuna.png");
Sprite tuna(Tuna_T);

Texture Vacuum_T("Textures/vacuum.png");
Sprite vacuum(Vacuum_T);
int vacRowStrt[4], vacColStrt[4], vacDir[4];

Texture Wall_T("Textures/wall.png");
Sprite wall(Wall_T);

RenderWindow window(VideoMode({ 570, 680 }), "PAC-MAN");


struct Map {
	char data[100][100];
	int rows, cols;

	int load(string name)
	{
		ifstream IN(name);

		if (!IN.is_open())
			return -1;

		IN >> rows >> cols;
		//IN.ignore(1000, '\n');

		//char line[1000];

		for (int i = 0; i < rows; i++)
		{
			//IN.getline(line, 1000);
			for (int j = 0; j < cols; j++)
			{
				//data[i][j] = line[j];
				IN >> data[i][j];
			}
		}

		IN.close();
		return 0;
	}

	void initialPos() // Finding initial player and enemy pos
	{
		int vacNo = 0; //vacuum Number
		for (int i = 0; i < rows; i++) 
		{
			for (int j = 0; j < cols; j++)
			{
				if (data[i][j] == 'P')
				{
					bobRowStrt = i;
					bobColStrt = j;
					data[i][j] = '-';
				}
				else if (data[i][j] == 'G')
				{
					vacRowStrt[vacNo] = i;
					vacColStrt[vacNo] = j;
					data[i][j] = '-';
					vacNo++;
				}
			}
		}
	}

	void display()
	{
		Vector2f pos;

		float y = 50; //actually the rows
		float x; //actually the columns
		for (int i = 0; i < rows; i++, y += 30)
		{
			x = 0;
			for (int j = 0; j < cols; j++, x += 30)
			{
				pos = { x, y };
				if (data[i][j] == '#')
				{
					wall.setPosition(pos);
					window.draw(wall);
				}
				else if (data[i][j] == '.')
				{
					fish.setPosition(pos);
					window.draw(fish);
				}
				else if (data[i][j] == 'o')
				{
					tuna.setPosition(pos);
					window.draw(tuna);
				}
			}
		}

		bob.setPosition({ bobCol * 30.f, bobRow * 30.f + 50.f });
		window.draw(bob);

		for (int i = 0; i < 4; i++)
		{
			if (i == 0)
				vacuum.setColor(Color::Red);
			else if (i == 1)
				vacuum.setColor(Color::Green);
			else if (i == 2)
				vacuum.setColor(Color::Magenta);
			else if (i == 3)
				vacuum.setColor(Color::Cyan);

			vacuum.setPosition({ vacColStrt[i] * 30.f, vacRowStrt[i] * 30.f + 50.f });
			window.draw(vacuum);
		}
	}
};

Map map;
int keyDir = 0;


void handleInput()
{
	while (optional event = window.pollEvent())
	{
		if (event->is<Event::Closed>())
			window.close();
		else if (const auto* key = event->getIf<Event::KeyPressed>())
		{
			if (key->code == Keyboard::Key::Up || key->code == Keyboard::Key::W)
			{
				if (map.data[bobRow - 1][bobCol] != '#')
					keyDir = 1;
			}
			else if (key->code == Keyboard::Key::Down || key->code == Keyboard::Key::S)
			{
				if (map.data[bobRow + 1][bobCol] != '#')
					keyDir = 2;
			}
			else if (key->code == Keyboard::Key::Left || key->code == Keyboard::Key::A)
			{
				if (map.data[bobRow][bobCol - 1] != '#')
					keyDir = 3;
			}
			else if (key->code == Keyboard::Key::Right || key->code == Keyboard::Key::D)
			{
				if (map.data[bobRow][bobCol + 1] != '#')
					keyDir = 4;
			}
			// ... Left, Right, W, A, S, D, P, Enter, Escape in the same way
		}
	}
}


int bobFrame = Player_Speed;

void updateGame()
{
	bobFrame++;
	if (keyDir == 1 && bobFrame > Player_Speed && map.data[bobRow - 1][bobCol] != '#')
	{
		bobRow--;
		bobFrame = 1;
	}
	else if (keyDir == 2 && bobFrame > Player_Speed && map.data[bobRow + 1][bobCol] != '#')
	{
		bobRow++;
		bobFrame = 1;
	}
	else if (keyDir == 3 && bobFrame > Player_Speed && map.data[bobRow][bobCol - 1] != '#')
	{
		bobCol--;
		bobFrame = 1;
	}
	else if (keyDir == 4 && bobFrame > Player_Speed && map.data[bobRow][bobCol + 1] != '#')
	{
		bobCol++;
		bobFrame = 1;
	}
}

void drawGame()
{
	window.clear();

	map.display();
	
	window.display();
}

int main()
{
	if (map.load("map.txt") == -1)
	{
		cout << "Map not Found";
		return 0;
	}

	map.initialPos();
	bobCol = bobColStrt;
	bobRow = bobRowStrt;

	window.setFramerateLimit(60);

	while (window.isOpen())
	{		
		handleInput();
		updateGame();
		drawGame();	
	}
}
