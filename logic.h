#pragma once
#include <vector>
#include <random>
#include "symbols.h"
/**
 * @file logic.h
 * @brief Plik nag��wkowy zawieraj�cy obiekty labiryntu.
 */

 /**
  * @class Object
  * @brief Klasa bazowa obiekt�w.
  */
class Object {
protected:
	int posX; /**< Pozycja X objektu */
	int posY; /**< Pozycja Y obiektu */
	std::vector<std::vector<bool>> floor; /**< Wektor pod�ogi */
	
public:
	/**
	 * @brief Konstruktor klasy.
	 * @param pX Pozycja X obiektu
	 * @param pY Pozycja Y obiektu
	 * @param fl Pod�oga
	 */
	Object(int pX, int pY, const std::vector<std::vector<bool>>& fl) : posX(pX), posY(pY), floor(fl) {}

	/**
	 * @brief Getter pozycji X.
	 */
	int getX() const { return posX;	}
	/**
	 * @brief Getter pozycji Y.
	 */
	int getY() const { return posY; }

	/**
	 * @brief Metoda czysto wirtualna.
	 * @return Zwraca symbol Obiektu
	 */
	virtual char getSymbol() const = 0;

	/**
	 * @brief Metoda sprawdzaj�ca kolizje z obiektem.
	 * @param x Wsp�rz�dna X do sprawdzenia kolizji
	 * @param y Wsp�rz�dna Y do sprawdzenia kolizji
	 * @return Zwraca true w przypadku kolizji
	 */
	bool collision(int x, int y);
};

/**
 * @class Exit
 * @brief Klasa obiektu wyj�cia z labiryntu.
 */
class Exit : public Object {
public:
	/**
	 * @brief Konstruktor klasy.
	 * @param pX Pozycja X obiektu
	 * @param pY Pozycja Y obiektu
	 */
	Exit(int pX, int pY) : Object(pX, pY, {}) {}
	/**
	 * @brief Metoda wirtualna.
	 * @return Zwraca symbol wyj�cia
	 */
	virtual char getSymbol() const { return symbol::exit; }
};

/**
 * @class Coin
 * @brief Klasa obiektu monety.
 */
class Coin : public Object {
public:
	/**
	 * @brief Konstruktor klasy.
	 * @param pX Pozycja X obiektu
	 * @param pY Pozycja Y obiektu
	 * @param fl Pod�oga
	 */
	Coin(int pX, int pY, const std::vector<std::vector<bool>>& fl) : Object(pX, pY, fl) {}
	/**
	 * @brief Metoda wirtualna.
	 * @return Zwraca symbol monety
	 */
	virtual char getSymbol() const { return symbol::coin; }
};

/**
 * @class EnemyAI
 * @brief Klasa AI przeciwnika (strategia).
 */
class EnemyAI {
protected:
	int posX; /**< Pozycja X objektu */
	int posY; /**< Pozycja Y objektu */
	std::vector<std::vector<bool>> floor; /**< Wektor pod�ogi */

public:
	/**
	 * @brief Konstruktor klasy.
	 */
	EnemyAI() : posX(0), posY(0), floor({}) {}
	/**
	 * @brief Metoda zmieniaj�ca warto�ci atrybut�w.
	 * @param pX Pozycja X obiektu
	 * @param pY Pozycja Y obiektu
	 * @param fl Pod�oga
	 */
	void setVariables(int pX, int pY, const std::vector<std::vector<bool>>& fl);
	
	/**
	 * @brief Metoda czysto wirtualna.
	 * @return Zwraca wsp�rz�dne nast�pnego ruchu
	 */
	virtual std::pair<int, int> getNextMove() = 0;
};

/**
 * @class NoAI
 * @brief Klasa AI przeciwnika (brak ruch�w).
 */
class NoAI : public EnemyAI {
public:
	/**
	 * @brief Konstruktor klasy.
	 */
	NoAI() : EnemyAI() {}
	/**
	 * @brief Metoda wirtualna.
	 * @return Zwraca wsp�rz�dne nast�pnego ruchu
	 */
	virtual std::pair<int, int> getNextMove();
};

/**
 * @class RandomAI
 * @brief Klasa AI przeciwnika (losowe ruchy).
 */
class RandomAI : public EnemyAI {
	std::random_device device; /**< Urz�dzenie losuj�ce */
	std::default_random_engine engine; /**< Silnik losuj�cy */
	std::uniform_int_distribution<int> randDirection; /**< Jednolity rozk�ad ca�kowity */

public:
	/**
	 * @brief Konstruktor klasy.
	 */
	RandomAI() : EnemyAI(), engine(device()), randDirection(0, 3) {}
	/**
	 * @brief Metoda wirtualna.
	 * @return Zwraca wsp�rz�dne nast�pnego ruchu
	 */
	virtual std::pair<int, int> getNextMove();
};

/**
 * @class PathfindingAI
 * @brief Klasa AI przeciwnika (przeciwnik zmierza do wylosowanego punktu).
 */
class PathfindingAI : public EnemyAI {
public:
	/**
	 * @brief Konstruktor klasy.
	 */
	PathfindingAI() : EnemyAI() {}
	/**
	 * @brief Metoda wirtualna.
	 * @return Zwraca wsp�rz�dne nast�pnego ruchu
	 */
	virtual std::pair<int, int> getNextMove();
};

/**
 * @class Enemy
 * @brief Klasa obiektu przeciwnika.
 */
class Enemy : public Object {
	std::unique_ptr<EnemyAI> ai;

public:
	/**
	 * @brief Konstruktor klasy.
	 * @param pX Pozycja X obiektu
	 * @param pY Pozycja Y obiektu
	 * @param fl Pod�oga
	 */
	Enemy(int pX, int pY, const std::vector<std::vector<bool>>& fl) : Object(pX, pY, fl), ai(new NoAI()) {};
	/**
	 * @brief Metoda wirtualna.
	 * @return Zwraca symbol przeciwnika
	 */
	virtual char getSymbol() const { return symbol::enemy; }

	/**
	 * @brief Metoda zmieniaj�ca AI przeciwnika.
	 */
	void changeAI(std::unique_ptr<EnemyAI> ai);

	/**
	 * @brief Metoda aktualizuj�ca pozycj� przeciwnika.
	 */
	void updatePosition();
};

/**
 * @class Player
 * @brief Klasa obiektu gracza.
 */
class Player : public Object {
public:
	/**
	 * @brief Konstruktor klasy.
	 * @param pX Pozycja X obiektu
	 * @param pY Pozycja Y obiektu
	 * @param fl Pod�oga
	 */
	Player(int pX, int pY, const std::vector<std::vector<bool>>& fl) : Object(pX, pY, fl) {}
	/**
	 * @brief Metoda wirtualna.
	 * @return Zwraca symbol gracza
	 */
	virtual char getSymbol() const { return symbol::player; }

	/**
	 * @brief Metoda poruszaj�ca gracza do g�ry.
	 */
	void up();
	/**
	 * @brief Metoda poruszaj�ca gracza w d�.
	 */
	void down();
	/**
	 * @brief Metoda poruszaj�ca gracza w lewo.
	 */
	void left();
	/**
	 * @brief Metoda poruszaj�ca gracza w prawo.
	 */
	void right();
};
