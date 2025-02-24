#pragma once
#include <string>
#include <fstream>

/**
 * @file leaderboard.h
 * @brief Plik nag��wkowy z klasa tablicy wynik�w.
 */

/**
  * @class Leaderboard
  * @brief Klasa tablicy wynik�w.
  */
class Leaderboard {
	std::string filePath; /**< Scie�ka do pliku danych */

public:
	/**
	 * @brief Konstruktor klasy.
	 * @param filePath_ Scie�ka do pliku danych
	 */
	Leaderboard(std::string filePath_) : filePath(filePath_) {}

	/**
	 * @brief Metoda szablonowa dodaj�ca do tablicy wynik�w.
	 */
	template<typename T>
	void add(T nick, int score);
	/**
	 * @brief Metoda przesy�aj�ca do strumienia zawarto�� pliku.
	 * @param stream Strumie�
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
