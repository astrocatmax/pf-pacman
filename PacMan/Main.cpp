#include<SFML/Graphics.hpp>
#include<iostream>
#include<fstream>
#include<string>

using namespace sf;
using namespace std;

struct Map {
	char data[100][100];
	int rows, cols;

	int loadMap(string name)
	{
		ifstream IN(name);

		if (!IN.is_open())
			return -1;

		IN >> rows >> cols;
		IN.ignore(1000, '\n');

		char line[1000];

		for (int i = 0; i < rows; i++)
		{
			IN.getline(line, 1000);
			for (int j = 0; j < cols; j++)
				data[i][j] = line[j];
		}

		IN.close();
		return 0;
	}
};

void handleInput()
{

}

void updateGame()
{

}

void drawGame()
{
	
}

int main()
{
	Map map;
	if (map.loadMap("map.txt") == -1)
	{
		cout << "Map not Found";
		return 0;
	}

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
	window.setFramerateLimit(60);

	float tile = 30.f;
	float HUD = 50.f;

	while (window.isOpen())
	{
		while (optional event = window.pollEvent())
		{
			if (event->is<Event::Closed>())
				window.close();
		}

		window.clear();
		
		for(int i = 0;i < map.rows;i++)
			for (int j = 0; j < map.cols;j++)
			{
				if (map.data[i][j] == '#')
				{
					wall.setPosition({ j * tile, i * tile + HUD});
					window.draw(wall);
				}
				else if (map.data[i][j] == '.')
				{
					fish.setPosition({ j * tile, i * tile + HUD });
					window.draw(fish);
				}
				else if (map.data[i][j] == 'o')
				{
					tuna.setPosition({ j * tile, i * tile + HUD });
					window.draw(tuna);
				}
				else if (map.data[i][j] == 'P')
				{
					BOB.setPosition({ j * tile, i * tile + HUD });
					window.draw(BOB);
				}
				else if (map.data[i][j] == 'G')
				{
					vacuum.setPosition({ j * tile, i * tile + HUD });
					window.draw(vacuum);
				}
			}

		window.display();
	}
}
