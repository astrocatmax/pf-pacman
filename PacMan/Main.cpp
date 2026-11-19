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
	map.loadMap("map.txt");
	Texture BOBText("Textures/BOB.png");
	sprite BOB(BOBText);


	RenderWindow window(VideoMode({570, 560}), "Menu");
	window.setFramerateLimit(60);
	
	while (window.isOpen())
	{
		while (optional event = window.pollEvent())
		{
			if (event->is<Event::Closed>())
				window.close();
		}

		window.clear();
		


		window.display();
	}
}
