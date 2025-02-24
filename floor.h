#pragma once
#include <vector>
#include <random>

/**
 * @file floor.h
 * @brief Plik nag³ówkowy zawieraj¹cy klasê Floor.
 */

 /**
  * @class Floor
  * @brief Klasa reprezentuj¹ca pod³ogê labiryntu.
  */
class Floor {
    std::random_device device; /**< Urz¹dzenie losuj¹ce */
    std::default_random_engine randomEngine; /**< Silnik losuj¹cy */

	std::vector<std::vector<bool>> floor; /**< Dwu wymiarowy wektor reprezentuj¹cy pod³ogê */
    /**
     * @brief Algorytm generowania losowego algorytmu.
     * @param startX Wspó³rzêdna X w którym znajduje siê obecnie algorytm 
     * @param startX Wspó³rzêdna Y w którym znajduje siê obecnie algorytm 
     */
    void recursiveBacktracker(int startX = 1, int startY = 1);

public:
    /**
     * @brief Konstruktor klasy.
     */
    Floor() : randomEngine(device()) {}

    /**
     * @brief Metoda generuj¹ca logowy labirynt.
     * @param sizeX Szerokoœæ
     * @param sizeY Wysokoœæ
     */
    void generateMaze(int sizeX, int sizeY);

    /**
     * @brief Metoda sprawdzenia rozmiaru.
     * @return rozmiar wysokoœci
     */
    size_t size() { return floor.size(); }
    /**
     * @brief Operator konwesji.
     */
    operator std::vector<std::vector<bool>>() { return floor; };
    /**
     * @brief Operator tablicy.
     */
    std::vector<bool>& operator[](int index) { return floor[index]; };
};
