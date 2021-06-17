#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <Windows.h>
#include <string>
#include <cstring>
#include <iomanip>
#include <conio.h>
#include <vector>
#include <sstream>

using namespace std;

class Game {
public:
	Game();
	~Game();
	struct Snake;
	void MainMenu();
	void StartGame();
	void UpdateMovement(int& headX, int& headY, int& tailX, int& tailY, int& length, string& direction, int& appleX, int& appleY);
	void Pause();
	void Play();
	void Options();
	void Graphics(int& headX, int& headY, int& tailX, int& tailY, int& length, int& appleX, int& appleY);
	void Clear();
	void newApple(int& x, int& y);
private:
	bool paused = false;
	string title = "Snake4";
	string asciiTitle = " _____             _            ___ \n\/  ___|           | |          \/   |\n\\ `--. _ __   __ _| | _____   \/ \/| |\n `--. \\ '_ \\ \/ _` | |\/ \/ _ \\ \/ \/_| |\n\/\\__\/ \/ | | | (_| |   <  __\/ \\___  |\n\\____\/|_| |_|\\__,_|_|\\_\\___|     |_\/\n";
	string asciiOptions = " _____       _   _\n|  _  |     | | (_)\n| | | |_ __ | |_ _  ___  _ __  ___\n| | | | '_ \\| __| |\/ _ \\| '_ \\\/ __|\n\\ \\_\/ \/ |_) | |_| | (_) | | | \\__ \\\n \\___\/| .__\/ \\__|_|\\___\/|_| |_|___\/\n      | |\n      |_|\n";
	int boardSizeY = 0;
	int boardSizeX = 0;
	int screenY = 120;
	int screenX = 30;
};

#endif