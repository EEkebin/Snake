#include "Game.h"

Game::Game() {
	srand(unsigned int(time(NULL)));
	string command = "title " + title;
	system(command.c_str());


	boardSizeX = 20;
	boardSizeY = boardSizeX / 2;
	MainMenu();
}

Game::~Game() {

}

void Game::MainMenu() {
	unsigned int highlighted = 1;
	unsigned int selectedOption = 0;

	do {
		system("CLS");
		cout << asciiTitle << "\n\n\n";
		cout << "[1] Play";
		if (highlighted == 1) cout << " <--";
		cout << "\n\n";
		cout << "[2] Options";
		if (highlighted == 2) cout << " <--";
		cout << "\n\n";
		cout << "[3] Exit";
		if (highlighted == 3) cout << " <--";
		cout << "\n\n";
		switch (_getch()) {
		case 72:
			if (highlighted != 1) {
				highlighted -= 1;
			}
			else {
				highlighted = 3;
			}
			break;
		case 80:
			if (highlighted != 3) {
				highlighted += 1;
			}
			else {
				highlighted = 1;
			}
			break;
		case 13:
			selectedOption = highlighted;
			break;
		}
	} while (selectedOption == 0);

	switch (selectedOption) {
	case 1:
		StartGame();
		break;
	case 2:
		Options();
		break;
	case 3:
		exit(1);
		break;
	}
}

void Game::StartGame() {
	struct Snake {
		struct Position {
			struct head {
				int x = 0;
				int y = 0;
			} head;
			struct tail {
				int x = 0;
				int y = 0;
			} tail;
		} Position;
		int length = 0;
		string direction = "";
	};
	struct Apple {
		struct Position {
			int x = 0;
			int y = 0;
		} Position;
	};
	Snake snake;
	Apple apple;
	snake.Position.head.x = 1;
	snake.Position.head.y = boardSizeY / 2;
	snake.Position.tail.x = snake.Position.head.x;
	snake.Position.tail.y = snake.Position.head.y;
	snake.length = 1;
	snake.direction = "right";
	newApple(apple.Position.x, apple.Position.y);
	bool saidPause = false;
	int keyid = NULL;
	do {
		if (_kbhit()) {
			keyid = _getch();
			if (keyid != 224) {
				switch (tolower(char(keyid))) {
				case 'w':
					if (snake.direction == "left" || snake.direction == "right") snake.direction = "up";
					break;
				case 'a':
					if (snake.direction == "up" || snake.direction == "down") snake.direction = "left";
					break;
				case 's':
					if (snake.direction == "left" || snake.direction == "right") snake.direction = "down";
					break;
				case 'd':
					if (snake.direction == "up" || snake.direction == "down") snake.direction = "right";
					break;
				case 'p':
					if (paused == true) {
						Play();
					}
					else if (paused == false) {
						saidPause = false;
						Pause();
					}
					break;
				case 'r':
					for (int i = 3; i > 0; i--) {
						system("CLS");
						cout << "Restart in " << i << ".";
						Sleep(1000);
					}
					StartGame();
					break;
				case VK_ESCAPE:
					Play();
					MainMenu();
					break;
				}
			}
			else if (keyid == 224) {
				int arrowid = _getch();
				switch (arrowid) {
				case 72:
					if (snake.direction == "left" || snake.direction == "right") snake.direction = "up";
					break;
				case 75:
					if (snake.direction == "up" || snake.direction == "down") snake.direction = "left";
					break;
				case 80:
					if (snake.direction == "left" || snake.direction == "right") snake.direction = "down";
					break;
				case 77:
					if (snake.direction == "up" || snake.direction == "down") snake.direction = "right";
					break;
				}
			}
		}
		if (paused == false) {
			system("CLS");
			UpdateMovement(snake.Position.head.x, snake.Position.head.y, snake.Position.tail.x, snake.Position.tail.y, snake.length, snake.direction, apple.Position.x, apple.Position.y);
			Graphics(snake.Position.head.x, snake.Position.head.y, snake.Position.tail.x, snake.Position.tail.y, snake.length, apple.Position.x, apple.Position.y);
		}
		else {
			if (saidPause == false) {
				saidPause = true;
				cout << "\n" << "Paused";
			}
		}

	} while (true);
}

void Game::UpdateMovement(int& headX, int& headY, int& tailX, int& tailY, int& length, string& direction, int& appleX, int& appleY) {
	if ((headX == appleX) && (headY == appleY)) {
		length++;
		newApple(appleX, appleY);
	}

	if ((direction == "up") && headY - 1 != 0) headY--;
	else if ((direction == "right") && headX + 1 != boardSizeX - 1) headX++;
	else if ((direction == "down") && headY + 1 != boardSizeY - 1) headY++;
	else if ((direction == "left") && headX - 1 != 0) headX--;
	else {
		system("CLS");
		cout << "Game Over!" << "\n" << "Score: " << length - 1;
		Sleep(2000);
		MainMenu();
	}

}

void Game::Pause() {
	paused = true;
}

void Game::Play() {
	paused = false;
}

void Game::Options() {
	string rawInput = "";
	int input = -1;
	char key = NULL;

	do {
		system("CLS");
		cout << asciiOptions << "\n\n\n";
		cout << "Current Board Size: " << boardSizeX << "\n\n";
		cout << "New Board Size [20-50, 0 to exit]: ";
		getline(cin, rawInput);
		if (isdigit(rawInput[0])) {
			input = stoi(rawInput);
			if (input >= 20 && input <= 50) {
				boardSizeX = input;
				boardSizeY = boardSizeX / 2;
			}
		}
		cin.clear();
	} while (input != 0);
	MainMenu();
}

void Game::Graphics(int& headX, int& headY, int& tailX, int& tailY, int& length, int& appleX, int& appleY) {
	for (int y = 0; y < boardSizeY; y++) {
		for (int x = 0; x < boardSizeX; x++) {
			if (y == 0 || y == boardSizeY - 1) cout << "=";
			else if (x == 0 || x == boardSizeX - 1) cout << "|";
			else if (x == headX && y == headY) cout << "o";
			else if (x == appleX && y == appleY) cout << "a";
			else cout << " ";
		}
		cout << "\n";
	}
	cout << "\n\n" << "Press Escape to Exit.                             " << "Score: " << length - 1 << "\n";
}

void Game::newApple(int& x, int& y) {
	int newX = rand() % (boardSizeX - 2) + 1;
	int newY = rand() % (boardSizeY - 2) + 1;
	if (x == newX && y == newY) {
		newApple(newX, newY);
	}
	else {
		x = newX;
		y = newY;
	}
}