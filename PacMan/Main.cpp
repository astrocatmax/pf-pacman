#include<SFML/Graphics.hpp>
#include<iostream>
#include<fstream>
#include<string>

using namespace sf;
using namespace std;

struct Map {
	char map[100][100];
	int rows, cols;

	int loadMap(string name)
	{
		ifstream IN(name);

		if (!IN.is_open())
			return -1;
		

		IN >> rows >> cols;

		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				IN >> map[i][j];

		IN.close();
		return 0; 



	}
};

int main()
{
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
