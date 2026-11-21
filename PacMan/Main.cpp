#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>
#include<fstream>
#include<string>

using namespace sf;
using namespace std;

//constants
const int Player_Speed = 8;
const int menu = 0, playing = 1, game_over = 2;
//constants

//global variables
int score_total = 0, food_counter = 0, live_counter = 3;
int state = menu;
//global variable


Font font("Fonts/Roboto/Roboto.ttf");
Text score(font);



Texture BOB_R("Textures/BOB.png");
Texture BOB_D("Textures/BOB_down.png");
Texture BOB_U("Textures/BOB_up.png");
Texture BOB_L("Textures/BOB_left.png");

Sprite bob(BOB_R);
int bobRowStrt, bobColStrt, bobRow, bobCol, keyDir;

Texture Fish_T("Textures/fish.png");
Sprite fish(Fish_T);


Texture Tuna_T("Textures/tuna.png");
Sprite tuna(Tuna_T);

Texture Vacuum_T("Textures/vacuum.png");
Sprite vacuum(Vacuum_T);
int vacRowStrt[4], vacColStrt[4], vacRow[4], vacCol[4], vacDir[4];

Texture Wall_T("Textures/wall.png");
Sprite wall(Wall_T);

RenderWindow window(VideoMode({ 570, 680 }), "PAC-MAN");


struct Map {
	char data[100][100];
	int rows, cols;

	int load(string name)
	{
		//initializing variables
		score_total = 0; 
		food_counter = 0; 
		live_counter = 3;

		//loading the map
		ifstream IN(name);

		if (!IN.is_open())
			return 0;

		IN >> rows >> cols;
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				IN >> data[i][j];
				if (data[i][j] == '.' || data[i][j] == 'o') {
					food_counter ++;
				}
			}
		}
		IN.close();


		// Finding initial player and enemy positions
		int vacNo = 0; //vacuum Number
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				if (data[i][j] == 'P')
				{
					bobRowStrt = i;
					bobColStrt = j;

					bobCol = bobColStrt;
					bobRow = bobRowStrt;

					data[i][j] = '-';
				}
				else if (data[i][j] == 'G')
				{
					vacRowStrt[vacNo] = i;
					vacColStrt[vacNo] = j;

					vacRow[vacNo] = vacRowStrt[vacNo];
					vacCol[vacNo] = vacColStrt[vacNo];

					data[i][j] = '-';
					vacNo++;
				}
			}
		}

		return 1;
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
		score.setString("SCORE:" + to_string(score_total));
		window.draw(score);


	}
};

Map map;


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
	if (bobFrame > Player_Speed)
	{
		if (map.data[bobRow][bobCol] == '.') {
			map.data[bobRow][bobCol] = '-';
			score_total += 10;
			food_counter--;

		}
		if (map.data[bobRow][bobCol] == 'o') {
			map.data[bobRow][bobCol] = '-';
			score_total += 50;
			food_counter--;
		}

		if (keyDir == 1 && bobFrame > Player_Speed && map.data[bobRow - 1][bobCol] != '#') //Up
		{
			bob.setTexture(BOB_U);
			bobRow--;
			bobFrame = 1;
		}
		else if (keyDir == 2 && bobFrame > Player_Speed && map.data[bobRow + 1][bobCol] != '#') //Down
		{

			bob.setTexture(BOB_D);
			bobRow++;
			bobFrame = 1;
		}
		else if (keyDir == 3 && bobFrame > Player_Speed && map.data[bobRow][bobCol - 1] != '#') //Left
		{
			bob.setTexture(BOB_L);
			bobCol--;
			bobFrame = 1;
		}
		else if (keyDir == 4 && bobFrame > Player_Speed && map.data[bobRow][bobCol + 1] != '#') //Right
		{
			bob.setTexture(BOB_R);
			bobCol++;
			bobFrame = 1;
		}
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
	score.setCharacterSize(30); //size in pixel
	score.setFillColor(Color::White);
	score.setStyle(Text::Bold | Text::Italic);

	if (!map.load("map.txt"))
	{
		cout << "Map not Found";
		return 0;
	}
	cout << food_counter;

	window.setFramerateLimit(60);

	while (window.isOpen())
	{
		handleInput();
		updateGame();
		drawGame();
	}
}