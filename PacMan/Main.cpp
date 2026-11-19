#include<SFML/Graphics.hpp>
#include<iostream>

using namespace sf;
using namespace std;


void rotLogo()
{
	RenderWindow MaWind(VideoMode({ 600, 600 }), "Title hehe");

	Texture MaText("logo.png");

	Sprite MaSprite(MaText);
	//MaSprite.setOrigin({ 225.f,225.f });
	//MaSprite.setScale({ 0.5f,0.5f });

	MaSprite.setPosition({ 0.f, 0.f });

	while (MaWind.isOpen())
	{
		while (optional event = MaWind.pollEvent())
		{
			if (event->is<Event::Closed>())
				MaWind.close();
		}

		MaWind.clear(Color::Magenta);

		MaWind.draw(MaSprite);

		MaWind.display();

		//MaSprite.scale({0.99f,0.99f});
		//MaSprite.rotate(degrees(1));
		MaWind.setFramerateLimit(60);
	}
}

void star()
{
	RenderWindow MaWind(VideoMode({ 500, 500 }), "Title hehe");
	ConvexShape star;

	star.setPointCount(8);

	star.setPoint(0, { 0.f,200.f });	//HAVE TO BE IN CLOCKWISE OR ANTICLOCKWISE ORDER
	star.setPoint(1, { 150.f,150.f });
	star.setPoint(2, { 200.f, 0.f });
	star.setPoint(3, { 250.f,150.f });
	star.setPoint(4, { 400.f,200.f });
	star.setPoint(5, { 250.f,250.f });
	star.setPoint(6, { 200.f,400.f });
	star.setPoint(7, { 150.f,250.f });

	while (MaWind.isOpen())
	{
		while (optional event = MaWind.pollEvent())
		{
			if (event->is<Event::Closed>())
				MaWind.close();
		}

		MaWind.clear(Color::Magenta);

		MaWind.draw(star);

		MaWind.display();

	}
}

void shapes()
{
	RenderWindow MaWind(VideoMode({ 500, 500 }), "Title hehe");
	CircleShape myCircle(60.f);
	CircleShape myTri(60.f, 3);
	RectangleShape myRect({ 50.f,100.f });
	Texture T("logo.png");


	myCircle.setTexture(&T);
	myCircle.setOutlineThickness(5.f);
	myCircle.setOutlineColor(Color(255, 0, 0));

	myTri.setFillColor(Color(0, 255, 0));

	myRect.setFillColor(Color(255, 100, 50));
	myRect.setOutlineThickness(5.f);
	myRect.setOutlineColor(Color(255, 0, 0));

	while (MaWind.isOpen())
	{
		while (optional event = MaWind.pollEvent())
		{
			if (event->is<Event::Closed>())
				MaWind.close();
		}

		myRect.setPosition({ 100.f,200.f });
		myTri.setPosition({ 130.f,0.f });

		MaWind.clear(Color::Magenta);

		MaWind.draw(myTri);
		MaWind.draw(myRect);
		MaWind.draw(myCircle);

		MaWind.display();

	}
}

//void font()
//{
//	RenderWindow MaWind(VideoMode({ 500, 500 }), "Title hehe");
//
//	Font myfont("arial.ttf"); //THE FONT DOESNT EXIST IN FOLDER AREA
//	Text mytext(myfont);
//
//	mytext.setString("AMITOKOSITA AN AN");
//	mytext.setCharacterSize(20); //size in pixel
//	mytext.setFillColor(Color::Cyan);
//	mytext.setStyle(Text::Bold | Text::Italic);
//
//	while (MaWind.isOpen())
//	{
//		while (optional event = MaWind.pollEvent())
//		{
//			if (event->is<Event::Closed>())
//				MaWind.close();
//		}
//
//		MaWind.clear(Color::Magenta);
//
//		MaWind.draw(mytext);
//
//		MaWind.display();
//
//	}
//}

void view()
{
	RenderWindow MaWind(VideoMode({ 500, 500 }), "MAP");
	View MyView;

	MyView = MaWind.getDefaultView();
	MyView.zoom(0.2f);
	MyView.setCenter({ 250.f,250.f });

	Texture texture("map.png");

	Sprite spr(texture);

	MaWind.setView(MyView);


	while (MaWind.isOpen())
	{
		while (optional event = MaWind.pollEvent())
		{
			if (event->is<Event::Closed>())
				MaWind.close();

		}


		MyView.move({ 1.f,0.f });
		MaWind.setView(MyView);
		MaWind.clear();

		MaWind.draw(spr);

		MaWind.display();
		MaWind.setFramerateLimit(60);
	}

}


float length(Vector2f& pos)
{
	float length = sqrt(pos.x * pos.x + pos.y * pos.y);
	return length;
}



void game()
{
	RenderWindow window(VideoMode({ 1920, 1080 }), "Game Bro YAH!");

	Texture playerT("player.png"), enemyT("enemy.png"), atkT("atk.png");
	Sprite player(playerT), enemy(enemyT), atk(atkT);

	player.setScale({ 0.7f,0.7f });
	enemy.setScale({ 0.7f,0.7f });
	atk.setScale({ 0.7f, 0.7f });

	player.setOrigin({ 130.f,130.f });
	enemy.setOrigin({ 257.f, 125.f });
	atk.setOrigin({ 225.f, 182.f });

	enemy.setPosition({ 500.f,500.f });

	bool attacked = false;

	float dis;
	int i = 1;
	while (window.isOpen())
	{
		dis = 1000;
		atk.setPosition(player.getPosition());
		window.setFramerateLimit(60);
		attacked = false;
		while (optional event = window.pollEvent())
		{
			if (event->is<Event::Closed>())
				window.close();

			if (const auto* click = event->getIf<Event::MouseButtonPressed>())
			{
				if (click->button == Mouse::Button::Left)
				{
					atk.setPosition(window.mapPixelToCoords(click->position));
					attacked = true;
				}
			}

		}


		if (Keyboard::isKeyPressed(Keyboard::Key::W))
		{
			player.move({ 0.f,-5.f });
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::A))
		{
			player.move({ -5.f,0.f });

		}
		if (Keyboard::isKeyPressed(Keyboard::Key::S))
		{
			player.move({ 0.f,5.f });

		}
		if (Keyboard::isKeyPressed(Keyboard::Key::D))
		{
			player.move({ 5.f,0.f });

		}

		Vector2f atkDis = enemy.getPosition() - atk.getPosition();
		float dis = length(atkDis);

		if (dis < 200)
		{
			cout << i << "HIT\n";
			i++;
		}


		window.clear();
		window.draw(player);
		window.draw(enemy);

		if (attacked)
			window.draw(atk);
		window.display();
	}
}

int main()
{
	
	//view();
	//font();
	//star();
	//shapes();
	rotLogo();
}
