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

int main()
{
	Map map;
	if (map.loadMap("map.txt"))
	{
		cout << "Map not Found";
		return 0;
	}
	Texture BOB_T("Textures/BOB.png");
	Sprite BOB(BOB_T);

	Texture Fish_T("Textures/fish.png");
	Sprite fish(Fish_T);
	fish.setOrigin({ 15,15 });
	fish.setPosition({ 165,260 });


	Texture Tuna_T("Textures/tuna.png");
	Sprite tuna(Tuna_T);
	tuna.setOrigin({ 15,15 });
	tuna.setPosition({ 365,260 });

	Texture Vacuum_T("Textures/vacuum.png");
	Sprite vacuum(Vacuum_T);
	vacuum.setOrigin({ 15,15 });
	vacuum.setPosition({ 65,260 });


	Texture Wall_T("Textures/wall.png");
	Sprite wall(Wall_T);
	wall.setOrigin({ 15,15 });
	wall.setPosition({ 465,260 });



	RenderWindow window(VideoMode({ 570, 560 }), "Menu");
	window.setFramerateLimit(60);

	while (window.isOpen())
	{
		while (optional event = window.pollEvent())
		{
			if (event->is<Event::Closed>())
				window.close();
		}

		window.clear();

		BOB.rotate(degrees(3));
		fish.rotate(degrees(3));
		tuna.rotate(degrees(3));
		wall.rotate(degrees(3));
		vacuum.rotate(degrees(3));


		window.draw(fish);
		window.draw(tuna);
		window.draw(wall);
		window.draw(vacuum);
		window.draw(BOB);
		window.display();



	}
}
