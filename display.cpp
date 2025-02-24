#include "display.h"
#include <Windows.h>
#include <conio.h>
#include <string>
#include <random>
#include "symbols.h"


void Display::showStatMenu() {
	bool end = false;
	int pos = 0;
	while (!end) {
		system("cls");
		std::cout
			<< "-------------------------------\n"
			<< ((pos == 0) ? " > " : "   ") << "Graj!\n"
			<< ((pos == 1) ? " > " : "   ") << "Tablica wynikow\n"
			<< ((pos == 2) ? " > " : "   ") << "Autor\n"
			<< "-------------------------------\n";

		char ch = _getch();
		switch (ch) {
		case 72: //up arrow
			if (pos > 0) pos--;
			break;
		case 80://down arrow
			if (pos < 2) pos++;
			break;
		case 13://enter
			if (pos == 0) end = true;
			if (pos == 1) displayLeaderboard();
			if (pos == 2) displayAuthor();
			break;
		default:
			break;
		}
	}
}

void Display::displayAuthor() {
	system("cls");
	std::cout
		<< "-------------------------------\n"
		<< "     Autor: Patryk Magon\n"
		<< "-------------------------------\n";
	auto _ = _getch();
}

void Display::displayLeaderboard() {
	system("cls");
	std::cout
		<< "-------------------------------\n"
		<< "        Tablica Wynikow\n"
		<< "-------------------------------\n\n";
	leaderboard.display(std::cout);
	auto _ = _getch();
}

void Display::showEnding(bool win, int points) {
	std::random_device device;
	std::default_random_engine engine(device());
	std::uniform_int_distribution<int> rand(11111, 99999);

	system("cls");
	std::cout
		<< "-------------------------------\n"
		<< (win ? 
		   "          ZWYCIESTWO!" : 
		   "           PORAZKA!")
		<< "\n"
		<< "-------------------------------\n\n";
	
	if (win) {
		std::cout << "Chcesz podac swoj nick we wpisie? (t/n) ";
		std::string getNick;
		std::cin >> getNick;
		if (getNick == "t") {
			std::string nick;
			std::cout << "Podaj nick: ";
			std::cin >> nick;
			leaderboard.add<std::string>(nick, points);
		}
		else {
			leaderboard.add<int>(rand(engine), points);
		}
	}
	else {
		char x;
		do {
			x = _getch();
		} while (x != 13);
	}

	displayLeaderboard();
}

void Display::changeSize(int sizeX, int sizeY) {
	canvas.resize(sizeX, std::vector<char>(sizeY));
	newCanvas.resize(sizeX, std::vector<char>(sizeY));
}

void Display::print() {
	for (size_t i = 0; i < canvas.size(); i++) {
		for (size_t j = 0; j < canvas[0].size(); j++) {
			if (newCanvas[i][j] != canvas[i][j]) {
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast<short>(j), static_cast<short>(i) });
				std::cout << newCanvas[i][j];
			}
		}
	}

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast<short>(0), static_cast<short>(canvas.size()) });
	canvas = newCanvas;
}

KeyAction Display::getKeyPressAction() {
	if (_kbhit()) {
		char ch = _getch();

		switch (ch) {
		case 72:
			return KeyAction::UP;
			break;
		case 80:
			return KeyAction::DOWN;
			break;
		case 75:
			return KeyAction::LEFT;
			break;
		case 77:
			return KeyAction::RIGHT;
			break;
		default:
			return KeyAction::STOP;
			break;
		}
	}
	return KeyAction::STOP;;
}

void Display::printPoints(int points) {
	std::cout << "Zebrane monety: " << points;
}

void Display::draw(const std::vector<std::vector<bool>>& floor) {
	if (newCanvas.size() != floor.size() || newCanvas[0].size() != floor[0].size()) {
		//error
		return;
	}

	for (size_t i = 0; i < floor.size(); i++) {
		for (size_t j = 0; j < floor[0].size(); j++) {
			newCanvas[i][j] = floor[i][j] ? symbol::floor : symbol::wall;
		}
	}
}

void Display::draw(const Object* object) {
	newCanvas[object->getX()][object->getY()] = object->getSymbol();
}
