#pragma once
#include <iostream>
#include <vector>
#include "logic.h"
#include "leaderboard.h"

/**
 * @file display.h
 * @brief Plik nag³ówkowy obs³uguj¹cy wyœwietlanie w konsoli.
 */

 /**
  * @brief Enum akcji wciœnietego klawisza.
  */
enum KeyAction { STOP, UP, DOWN, LEFT, RIGHT };

/**
 * @class Display
 * @brief Klasa odpowiedzialna za wyœwitlanie w konsoli.
 */
class Display {
	std::vector<std::vector<char>> canvas; /**< Wektor obrazu przechowywany w celu porównywania zmian */
	std::vector<std::vector<char>> newCanvas; /**< Wektor obrazu */

	Leaderboard leaderboard; /**< Tablica wyników */

	/**
	 * @brief Metoda wyœwietlaj¹ca autora.
	 */
	void displayAuthor();
	/**
	 * @brief Metoda wyœwietlaj¹ca tablice wyników.
	 */
	void displayLeaderboard();

public:
	/**
	 * @brief Konstruktor klasy.
	 */
	Display() : leaderboard("leaderboard.txt") {}

	/**
	 * @brief Metoda wyœwietlaj¹ca menu start.
	 */
	void showStatMenu();
	/**
	 * @brief Metoda wyœwietlaj¹ca zakoñczenie gry.
	 * @param win Czy wygrana
	 * @param points Iloœæ monet
	 */
	void showEnding(bool win, int points);

	/**
	 * @brief Metoda zmieniaj¹ca wymiary wktorów obrazu.
	 * @param sizeX Szerokoœæ
	 * @param sizeY Wysokoœæ
	 */
	void changeSize(int sizeX, int sizeY);
	/**
	 * @brief Metoda rysuj¹ca w konsoli.
	 */
	void print();
	/**
	 * @brief Metoda sprawdzaj¹ca wciœniêcie klawisza.
	 * @return Akcjê dla wciœnietego klawisza
	 */
	KeyAction getKeyPressAction();

	/**
	 * @brief Metoda rysuj¹ca iloœæ monet w konsoli.
	 * @param points Iloœæ monet
	 */
	void printPoints(int points);

	/**
	 * @brief Metoda zapisuj¹ca pod³ogê do wektora obrazu.
	 * @param floor Wektor pod³ogi
	 */
	void draw(const std::vector<std::vector<bool>>& floor);
	/**
	 * @brief Metoda zapisuj¹ca Object do wektora obrazu.
	 * @param object Obiekt do narysowania
	 */
	void draw(const Object* object);
};
