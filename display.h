#pragma once
#include <iostream>
#include <vector>
#include "logic.h"
#include "leaderboard.h"

/**
 * @file display.h
 * @brief Plik nag��wkowy obs�uguj�cy wy�wietlanie w konsoli.
 */

 /**
  * @brief Enum akcji wci�nietego klawisza.
  */
enum KeyAction { STOP, UP, DOWN, LEFT, RIGHT };

/**
 * @class Display
 * @brief Klasa odpowiedzialna za wy�witlanie w konsoli.
 */
class Display {
	std::vector<std::vector<char>> canvas; /**< Wektor obrazu przechowywany w celu por�wnywania zmian */
	std::vector<std::vector<char>> newCanvas; /**< Wektor obrazu */

	Leaderboard leaderboard; /**< Tablica wynik�w */

	/**
	 * @brief Metoda wy�wietlaj�ca autora.
	 */
	void displayAuthor();
	/**
	 * @brief Metoda wy�wietlaj�ca tablice wynik�w.
	 */
	void displayLeaderboard();

public:
	/**
	 * @brief Konstruktor klasy.
	 */
	Display() : leaderboard("leaderboard.txt") {}

	/**
	 * @brief Metoda wy�wietlaj�ca menu start.
	 */
	void showStatMenu();
	/**
	 * @brief Metoda wy�wietlaj�ca zako�czenie gry.
	 * @param win Czy wygrana
	 * @param points Ilo�� monet
	 */
	void showEnding(bool win, int points);

	/**
	 * @brief Metoda zmieniaj�ca wymiary wktor�w obrazu.
	 * @param sizeX Szeroko��
	 * @param sizeY Wysoko��
	 */
	void changeSize(int sizeX, int sizeY);
	/**
	 * @brief Metoda rysuj�ca w konsoli.
	 */
	void print();
	/**
	 * @brief Metoda sprawdzaj�ca wci�ni�cie klawisza.
	 * @return Akcj� dla wci�nietego klawisza
	 */
	KeyAction getKeyPressAction();

	/**
	 * @brief Metoda rysuj�ca ilo�� monet w konsoli.
	 * @param points Ilo�� monet
	 */
	void printPoints(int points);

	/**
	 * @brief Metoda zapisuj�ca pod�og� do wektora obrazu.
	 * @param floor Wektor pod�ogi
	 */
	void draw(const std::vector<std::vector<bool>>& floor);
	/**
	 * @brief Metoda zapisuj�ca Object do wektora obrazu.
	 * @param object Obiekt do narysowania
	 */
	void draw(const Object* object);
};
