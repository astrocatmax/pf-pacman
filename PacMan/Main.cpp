#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>
#include<fstream>
#include<string>

using namespace sf;
using namespace std;

//constants
const int Player_Speed = 8, Vacuum_Speed = 10, Vacuum_Speed_Scared = 16;
const int menu = 0, playing = 1, game_over = 2, win = 3;
//constants

//global variables
int score_total = 0, food_counter = 0, live_counter = 3;
int state = menu;
int menusel = 0;
bool oiiaPlaying = false;
bool omegaMode = 0;
Clock oiiaClock;
//global variable


Font font("Fonts/Roboto/Roboto.ttf");
Text score(font);
Text livestext(font);
Text menutext(font);

SoundBuffer beepBuf("Sounds/beep.wav");
SoundBuffer meowBuf("Sounds/meow.mp3");
SoundBuffer explosionBuf("Sounds/explosion.wav");
SoundBuffer chompBuf("Sounds/chomp.mp3");
Sound beep(beepBuf);
Sound meow(meowBuf);
Sound explode(explosionBuf);
Sound chomp(chompBuf);

Music bgMusic("Sounds/music.mp3");
Music oiia("Sounds/oiia_power.mp3");


//BOB---------------------------------------------------------------------
Texture BOB_R("Textures/BOB.png");
Texture BOB_D("Textures/BOB_down.png");
Texture BOB_U("Textures/BOB_up.png");
Texture BOB_L("Textures/BOB_left.png");

Sprite bob(BOB_R);
int bobRowStrt, bobColStrt, bobRow, bobCol, keyDir;
//BOB---------------------------------------------------------------------


//Vacuums-----------------------------------------------------------------
Texture Scared_D("Textures/scared.png");
Texture Scared_R("Textures/scared_right.png");
Texture Scared_L("Textures/scared_left.png");
Texture Scared_U("Textures/scared_up.png");

Texture Vacuum_D("Textures/vacuum.png");
Texture Vacuum_R("Textures/vacuum_right.png");
Texture Vacuum_L("Textures/vacuum_left.png");
Texture Vacuum_U("Textures/vacuum_up.png");

Sprite vacuum(Vacuum_D);
int vacRowStrt[4], vacColStrt[4], vacRow[4], vacCol[4], vacDir[4] = { 0 };
//Vacuums-----------------------------------------------------------------



Texture Fish_T("Textures/fish.png");
Sprite fish(Fish_T);

Texture Tuna_T("Textures/tuna.png");
Sprite tuna(Tuna_T);

Texture Wall_T("Textures/wall.png");
Sprite wall(Wall_T);

Texture Yarn_T("Textures/yarn.png");
Sprite yarn(Yarn_T); 

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
			if (!omegaMode)
			{
				if (i == 0)
					vacuum.setColor(Color::Red);
				else if (i == 1)
					vacuum.setColor(Color::Green);
				else if (i == 2)
					vacuum.setColor(Color::Magenta);
				else if (i == 3)
					vacuum.setColor(Color::Cyan);
			}
			else
				vacuum.setColor(Color::Blue);

			vacuum.setPosition({ vacCol[i] * 30.f, vacRow[i] * 30.f + 50.f });
			window.draw(vacuum);
		}
		score.setString("SCORE: " + to_string(score_total));

		score.setCharacterSize(26);
		score.setFillColor(Color::White);
		score.setStyle(Text::Bold);
		score.setOutlineColor(Color::Black);
		score.setOutlineThickness(2.f);
		score.setPosition({ 15.f, 8.f });
		window.draw(score);



		livestext.setString("LIVES: ");
		livestext.setCharacterSize(26);
		livestext.setFillColor(Color::White);
		livestext.setStyle(Text::Bold);
		livestext.setOutlineColor(Color::Black);
		livestext.setOutlineThickness(2.f);
		livestext.setPosition({ 390.f, 8.f });
		window.draw(livestext);
		
		for (int i = 0; i < live_counter;i++) {
			yarn.setPosition({ 475.f+(i*28), 8.f});
			window.draw(yarn);
		}
		
	}

	void saveGame()
	{
		ofstream out("savegame.txt");

		out << score_total << " " << live_counter << "\n";
		out << bobRow << " " << bobCol << "\n";

		for (int i = 0; i < 4; i++)
			out << vacRow[i] << " " << vacCol[i] << " ";
		out << "\n";

		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
				out << data[i][j];
			out << "\n";
		}

		out.close();
	}
};

Map map;

void resetPositions() { //created this to reset all positions when bob loses a live
	bobRow = bobRowStrt;
	bobCol = bobColStrt;
	keyDir = 0;
	bob.setTexture(BOB_R);
	for (int i = 0; i < 4; i++) {
		vacRow[i] = vacRowStrt[i];
		vacCol[i] = vacColStrt[i];
		vacDir[i] = 0;

	}
}

void startNewGame() {
	map.load("map.txt");
	resetPositions();
}

void drawCentered(const string& str, float y, int size, Color color)
{
	menutext.setString(str);
	menutext.setCharacterSize(size);
	menutext.setFillColor(color);
	menutext.setStyle(Text::Bold);
	menutext.setOutlineColor(Color::Black);
	menutext.setOutlineThickness(2.f);

	FloatRect b = menutext.getLocalBounds();
	menutext.setOrigin({ b.position.x + b.size.x / 2.f, 0.f });
	menutext.setPosition({ 285.f, y });
	window.draw(menutext);
}

void drawMenu()
{
	drawCentered("PAC-MAN", 120.f, 60, Color::Yellow);

	string options[3] = { "New Game", "Continue", "Exit" };
	for (int i = 0; i < 3; i++)
	{
		Color c = Color::White;
		if (i == menusel)
			c = Color::Yellow;

		string label = (i == menusel ? "> " : "  ") + options[i];
		drawCentered(label, 290.f + i * 60.f, 36, c);
	}

	drawCentered("Up/Down to move, Enter to select", 600.f, 18, Color::White);
}

void handleInput()
{
	while (optional event = window.pollEvent())
	{
		if (event->is<Event::Closed>())
			window.close();
		else if (const auto* key = event->getIf<Event::KeyPressed>())
		{
			if (state == menu)
			{
				if (key->code == Keyboard::Key::Up || key->code == Keyboard::Key::W)
					menusel = (menusel + 2) % 3;
				else if (key->code == Keyboard::Key::Down || key->code == Keyboard::Key::S)
					menusel = (menusel + 1) % 3;
				else if (key->code == Keyboard::Key::Enter)
				{
					if (menusel == 0) {
						startNewGame();
						state = playing;
					}     
					else if (menusel == 2)
						window.close();          
					
				}
			}
			else if (state == playing)
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
				else if (key->code == Keyboard::Key::Escape)
				{
					map.saveGame();
					omegaMode = 0;
                    oiiaPlaying = false;
					oiia.stop();
					bgMusic.play();

					state = menu;
				}
			}
			else if (state == win || state == game_over)
			{
				if (key->code == Keyboard::Key::Enter)
					state = menu;
			}
		}
	}
}


//-------------------------------GHOSTS--------------------------
bool freeCell(int row, int col, int dir) //checks if the cell you want to move has a wall or not
{
	if (dir == 1)
		row--;
	else if (dir == 2)
		row++;
	else if (dir == 3)
		col--;
	else if (dir == 4)
		col++;

	if (map.data[row][col] != '#')
		return 1;

	return 0;
}

int opposite(int dir) //returns the opposite direction
{
	if (dir == 1)
		return 2;
	else if (dir == 2)
		return 1;
	else if (dir == 3)
		return 4;
	else if (dir == 4)
		return 3;

	return 0;
}

int allDirections(int directions[], int i) //Checks and stores the available directions in given order (UP, LEFT, DOWN, RIGHT) so it is easier to use later
{ 
	int count = 0;

	if (freeCell(vacRow[i], vacCol[i], 1)) 
	{
		directions[count] = 1;
		count++;
	}

	if (freeCell(vacRow[i], vacCol[i], 3))
	{
		directions[count] = 3;
		count++;
	}

	if (freeCell(vacRow[i], vacCol[i], 2))
	{
		directions[count] = 2;
		count++;
	}

	if (freeCell(vacRow[i], vacCol[i], 4))
	{
		directions[count] = 4;
		count++;
	}

	return count;
}

int distance(int row, int col, int dir)
{
	if (dir == 1)
		row--;
	else if (dir == 2)
		row++;
	else if (dir == 3)
		col--;
	else if (dir == 4)
		col++;

	return abs(row - bobRow) + abs(col - bobCol); // formula given in manual
}

void ghostMovementNormal(int i)
{
	int count, directions[4], done = 0;

	count = allDirections(directions, i);

	if (i == 0 || i == 2) //chasers
	{
		int shortest = 0;

		if (count == 1) //If there is only one way then it just picks it
			shortest = 0;
		else //If there is atleast 2 choices then it decides
		{
			for (int sel = 0; sel < count; sel++) //makes sure it never picks the direction turning it back
			{
				if (directions[sel] != opposite(vacDir[i]))
				{
					shortest = sel;
					break;
				}
			}

			for (int dir = 0; dir < count; dir++) //picks the shortest out of the direction not turning back
			{
				if (directions[dir] != opposite(vacDir[i]))
				{
					if (distance(vacRow[i], vacCol[i], directions[dir]) < distance(vacRow[i], vacCol[i], directions[shortest]))
						shortest = dir;
				}
			}
		}

		vacDir[i] = directions[shortest];
	}
	else if (i == 1 || i == 3) //wanderers
	{
		while (!done)
		{
			int pick;
			if (count == 1) //Only one choice? Then pick it
			{
				vacDir[i] = directions[0];
				done = 1;
			}
			else //picking a random one that is not opposite
			{
				pick = rand() % count;

				if (directions[pick] != opposite(vacDir[i]))
				{
					vacDir[i] = directions[pick];
					done = 1;
				}
			}
		}
	}

	if (vacDir[i] == 1) //Up
	{
		vacRow[i]--;
		vacuum.setTexture(Vacuum_U);
	}
	else if (vacDir[i] == 2) //Down
	{
		vacRow[i]++;
		vacuum.setTexture(Vacuum_D);
	}
	else if (vacDir[i] == 3) //Left
	{
		vacCol[i]--;
		vacuum.setTexture(Vacuum_L);
	}
	else if (vacDir[i] == 4) //Right
	{
		vacCol[i]++;
		vacuum.setTexture(Vacuum_R);
	}

}

void ghostMovementScared(int i)
{
	int count, directions[4], done = 0;

	count = allDirections(directions, i);

	while (!done)
	{
		int pick;
		if (count == 1) //Only one choice? Then pick it
		{
			vacDir[i] = directions[0];
			done = 1;
		}
		else //picking a random one that is not opposite
		{
			pick = rand() % count;
			if (directions[pick] != opposite(vacDir[i]))
			{
				vacDir[i] = directions[pick];
				done = 1;
			}
		}
	}

	if (vacDir[i] == 1) //Up
	{
		vacRow[i]--;
		vacuum.setTexture(Scared_U);
	}
	else if (vacDir[i] == 2) //Down
	{
		vacRow[i]++;
		vacuum.setTexture(Scared_D);
	}
	else if (vacDir[i] == 3) //Left
	{
		vacCol[i]--;
		vacuum.setTexture(Scared_L);
	}
	else if (vacDir[i] == 4) //Right
	{
		vacCol[i]++;
		vacuum.setTexture(Scared_R);
	}
}

bool ghostHitBob() {
	for (int i = 0; i < 4; i++)
	{
		if (vacRow[i] == bobRow && vacCol[i] == bobCol)
		{
			if (!omegaMode)
			{
				live_counter--;
				explode.play();
				resetPositions();

				if (live_counter <= 0) {
					state = game_over;
				}
			}
			else
			{
				score_total += 200;
				chomp.play();

				vacRow[i] = vacRowStrt[i];
				vacCol[i] = vacColStrt[i];
			}


			return true;
		}
	}
	return false;
}
//-------------------------------GHOSTS--------------------------

//-------------------------------PLAYER--------------------------
void playerMovement()
{

	if (keyDir == 1 && map.data[bobRow - 1][bobCol] != '#') //Up
	{
		bob.setTexture(BOB_U);
		bobRow--;
	}
	else if (keyDir == 2 && map.data[bobRow + 1][bobCol] != '#') //Down
	{

		bob.setTexture(BOB_D);
		bobRow++;
	}
	else if (keyDir == 3 && map.data[bobRow][bobCol - 1] != '#') //Left
	{
		bob.setTexture(BOB_L);
		bobCol--;
	}
	else if (keyDir == 4 && map.data[bobRow][bobCol + 1] != '#') //Right
	{
		bob.setTexture(BOB_R);
		bobCol++;
	}
}
//-------------------------------PLAYER--------------------------


int bobFrame = Player_Speed;
int vacFrame[4] = { Vacuum_Speed, Vacuum_Speed, Vacuum_Speed, Vacuum_Speed };

void updateGame()
{
	if (state != playing)
		return;

	if (keyDir != 0) //Waits for you to actually move before they start to move
	{
		for (int i = 0; i < 4; i++) //Handles the movement of ghosts
		{
			vacFrame[i]++;
			if (vacFrame[i] > Vacuum_Speed && !omegaMode)
			{
				ghostMovementNormal(i);
				vacFrame[i] = 1;
			}
			else if (vacFrame[i] > Vacuum_Speed_Scared && omegaMode)
			{
				ghostMovementScared(i);
				vacFrame[i] = 1;
			}
		}
	}

	if (oiiaPlaying && oiiaClock.getElapsedTime().asSeconds() >= 5.f)
	{
		omegaMode = 0;
		oiiaPlaying = false;
		bgMusic.play();   //resumes from where it was paused
	}


	ghostHitBob();

	bobFrame++;
	if (bobFrame > Player_Speed)
	{
		playerMovement();
		bobFrame = 1;
	}

	ghostHitBob();

	if (map.data[bobRow][bobCol] == '.') {
		map.data[bobRow][bobCol] = '-';
		score_total += 10;
		food_counter--;
		beep.play();


	}
	if (map.data[bobRow][bobCol] == 'o') {
		omegaMode = 1;
		map.data[bobRow][bobCol] = '-';
		score_total += 50;
		food_counter--;
		//meow.play();
		bgMusic.pause();
		oiia.stop();      //restarts from the beginning if another tuna is eaten mid-sound
		oiia.play();
		oiiaClock.restart();
		oiiaPlaying = true;

	}

	if (food_counter <= 0) //all pellets eaten
		state = win;
}

void drawEndScreen() {
	RectangleShape shade({ 570.f, 630.f });
	shade.setPosition({ 0.f, 50.f }); //leaves the HUD strip visible
	shade.setFillColor(Color(0, 0, 0, 170));
	window.draw(shade);

	if (state == win)
		drawCentered("YOU WIN!", 250.f, 60, Color::Yellow);
	else
		drawCentered("GAME OVER", 250.f, 60, Color::Blue);

	drawCentered("Score: " + to_string(score_total), 340.f, 30, Color::White);
	drawCentered("Press Enter for menu", 420.f, 22, Color::White);
}

void drawGame()
{
	window.clear();

	if (state == menu)
		drawMenu();
	else {
		map.display();
		if (state == win || state == game_over) {
			drawEndScreen();
		}
	}

	window.display();
}

int main()
{
	srand(time(0)); //makes it so random ACTUALLY works as random

	if (!map.load("map.txt"))
	{
		cout << "Map not Found";
		return 0;
	}
	cout << food_counter;

	bgMusic.setLooping(true);
	bgMusic.setVolume(40);
	bgMusic.play();

	window.setFramerateLimit(60);

	while (window.isOpen())
	{
		handleInput();
		updateGame();
		drawGame();
	}
}