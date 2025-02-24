#pragma once
#include <string>
#include <fstream>

/**
 * @file leaderboard.h
 * @brief Plik nag³ówkowy z klasa tablicy wyników.
 */

/**
  * @class Leaderboard
  * @brief Klasa tablicy wyników.
  */
class Leaderboard {
	std::string filePath; /**< Scie¿ka do pliku danych */

public:
	/**
	 * @brief Konstruktor klasy.
	 * @param filePath_ Scie¿ka do pliku danych
	 */
	Leaderboard(std::string filePath_) : filePath(filePath_) {}

	/**
	 * @brief Metoda szablonowa dodaj¹ca do tablicy wyników.
	 */
	template<typename T>
	void add(T nick, int score);
	/**
	 * @brief Metoda przesy³aj¹ca do strumienia zawartoœæ pliku.
	 * @param stream Strumieñ
	 */
	void display(std::ostream& stream);
};

template<typename T>
inline void Leaderboard::add(T nick, int score) {
	std::ofstream file;
	file.open(filePath, std::ios::app);

	if (!file.is_open()) {
		//error
		return;
	}

	file << nick << " " << score << std::endl;

	file.close();
}
