#pragma once
#include "logic.h"
#include "display.h"
#include "floor.h"
#include <vector>

/**
 * @file game.h
 * @brief Plik nag³ówkowy zawieraj¹cy g³ówn¹ mechanikê gry.
 */

 /**
  * @class Game
  * @brief G³ówna klasa gry.
  */
class Game {
	int sizeX; /**< Rozmiar X planszy */
	int sizeY; /**< Rozmiar Y planszy */
	
	Display display; /**< Rysowanie obrazu */

	Floor floor;  /**< Pod³oga labiryntu */
	Player* player;  /**< Gracz */
	Exit* exit;  /**< Wyjœcie (zwyciêstwo) */
	std::vector<Coin*> coins;  /**< Wektor monet */
	std::vector<Enemy*> enemies;  /**< Wektor przeciwników */

	int points;  /**< Monety */
	
	/**
	 * @brief Metoda rysuj¹ca.
	 */
	void print();
	/**
	 * @brief Metoda dodaj¹ca moenty na plaszê.
	 * @param n Iloœæ monet
	 */
	void addCoins(int n);
	/**
	 * @brief Metoda dodaj¹ca przecieników na plansz¹.
	 * @param n Iloœæ przeciwników
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
	 * @brief Metoda uruchamiaj¹ca grê.
	 */
	void start();
};

