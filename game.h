#pragma once
#include "logic.h"
#include "display.h"
#include "floor.h"
#include <vector>

/**
 * @file game.h
 * @brief Plik nag��wkowy zawieraj�cy g��wn� mechanik� gry.
 */

 /**
  * @class Game
  * @brief G��wna klasa gry.
  */
class Game {
	int sizeX; /**< Rozmiar X planszy */
	int sizeY; /**< Rozmiar Y planszy */
	
	Display display; /**< Rysowanie obrazu */

	Floor floor;  /**< Pod�oga labiryntu */
	Player* player;  /**< Gracz */
	Exit* exit;  /**< Wyj�cie (zwyci�stwo) */
	std::vector<Coin*> coins;  /**< Wektor monet */
	std::vector<Enemy*> enemies;  /**< Wektor przeciwnik�w */

	int points;  /**< Monety */
	
	/**
	 * @brief Metoda rysuj�ca.
	 */
	void print();
	/**
	 * @brief Metoda dodaj�ca moenty na plasz�.
	 * @param n Ilo�� monet
	 */
	void addCoins(int n);
	/**
	 * @brief Metoda dodaj�ca przecienik�w na plansz�.
	 * @param n Ilo�� przeciwnik�w
	 */
	void addEnemies(int n);

public:
	/**
	 * @brief Konstruktor klasy.
	 */
	Game();
	/**
	 * @brief Destruktor klasy.
	 */
	~Game();

	/**
	 * @brief Metoda uruchamiaj�ca gr�.
	 */
	void start();
};

