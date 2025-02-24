#pragma once
#include <vector>
#include <random>

/**
 * @file floor.h
 * @brief Plik nag��wkowy zawieraj�cy klas� Floor.
 */

 /**
  * @class Floor
  * @brief Klasa reprezentuj�ca pod�og� labiryntu.
  */
class Floor {
    std::random_device device; /**< Urz�dzenie losuj�ce */
    std::default_random_engine randomEngine; /**< Silnik losuj�cy */

	std::vector<std::vector<bool>> floor; /**< Dwu wymiarowy wektor reprezentuj�cy pod�og� */
    /**
     * @brief Algorytm generowania losowego algorytmu.
     * @param startX Wsp�rz�dna X w kt�rym znajduje si� obecnie algorytm 
     * @param startX Wsp�rz�dna Y w kt�rym znajduje si� obecnie algorytm 
     */
    void recursiveBacktracker(int startX = 1, int startY = 1);

public:
    /**
     * @brief Konstruktor klasy.
     */
    Floor() : randomEngine(device()) {}

    /**
     * @brief Metoda generuj�ca logowy labirynt.
     * @param sizeX Szeroko��
     * @param sizeY Wysoko��
     */
    void generateMaze(int sizeX, int sizeY);

    /**
     * @brief Metoda sprawdzenia rozmiaru.
     * @return rozmiar wysoko�ci
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
