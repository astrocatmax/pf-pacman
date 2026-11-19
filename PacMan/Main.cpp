#include<SFML/Graphics.hpp>
#include<iostream>
#include<fstream>
#include<string>

using namespace sf;
using namespace std;

Texture BOB_T("Textures/BOB.png");
Sprite BOB(BOB_T);
//BOB.setOrigin({ 15,15 });

Texture Fish_T("Textures/fish.png");
Sprite fish(Fish_T);
//fish.setOrigin({ 15,15 });


Texture Tuna_T("Textures/tuna.png");
Sprite tuna(Tuna_T);
//tuna.setOrigin({ 15,15 });

Texture Vacuum_T("Textures/vacuum.png");
Sprite vacuum(Vacuum_T);
//vacuum.setOrigin({ 15,15 });


Texture Wall_T("Textures/wall.png");
Sprite wall(Wall_T);
//wall.setOrigin({ 15,15 });

RenderWindow window(VideoMode({ 570, 680 }), "Menu");


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

		char line[1000];

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
				else if (data[i][j] == 'P')
				{
					BOB.setPosition(pos);
					window.draw(BOB);
				}
				else if (data[i][j] == 'G')
				{
					vacuum.setPosition(pos);
					window.draw(vacuum);
				}
			}
		}

	}
};

Map map;

void handleInput()
{
	while (optional event = window.pollEvent())
	{
		if (event->is<Event::Closed>())
			window.close();
	}
}

void updateGame()
{

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

	window.setFramerateLimit(60);

	while (window.isOpen())
	{		
		handleInput();
		updateGame();
		drawGame();	
	}
}
