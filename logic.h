#pragma once
#include <vector>
#include <random>
#include "symbols.h"
/**
 * @file logic.h
 * @brief Plik nag³ówkowy zawieraj¹cy obiekty labiryntu.
 */

 /**
  * @class Object
  * @brief Klasa bazowa obiektów.
  */
class Object {
protected:
	int posX; /**< Pozycja X objektu */
	int posY; /**< Pozycja Y obiektu */
	std::vector<std::vector<bool>> floor; /**< Wektor pod³ogi */
	
public:
	/**
	 * @brief Konstruktor klasy.
	 * @param pX Pozycja X obiektu
	 * @param pY Pozycja Y obiektu
	 * @param fl Pod³oga
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
	 * @brief Metoda sprawdzaj¹ca kolizje z obiektem.
	 * @param x Wspó³rzêdna X do sprawdzenia kolizji
	 * @param y Wspó³rzêdna Y do sprawdzenia kolizji
	 * @return Zwraca true w przypadku kolizji
	 */
	bool collision(int x, int y);
};

/**
 * @class Exit
 * @brief Klasa obiektu wyjœcia z labiryntu.
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
	 * @return Zwraca symbol wyjœcia
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
	 * @param fl Pod³oga
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
	std::vector<std::vector<bool>> floor; /**< Wektor pod³ogi */

public:
	/**
	 * @brief Konstruktor klasy.
	 */
	EnemyAI() : posX(0), posY(0), floor({}) {}
	/**
	 * @brief Metoda zmieniaj¹ca wartoœci atrybutów.
	 * @param pX Pozycja X obiektu
	 * @param pY Pozycja Y obiektu
	 * @param fl Pod³oga
	 */
	void setVariables(int pX, int pY, const std::vector<std::vector<bool>>& fl);
	
	/**
	 * @brief Metoda czysto wirtualna.
	 * @return Zwraca wspó³rzêdne nastêpnego ruchu
	 */
	virtual std::pair<int, int> getNextMove() = 0;
};

/**
 * @class NoAI
 * @brief Klasa AI przeciwnika (brak ruchów).
 */
class NoAI : public EnemyAI {
public:
	/**
	 * @brief Konstruktor klasy.
	 */
	NoAI() : EnemyAI() {}
	/**
	 * @brief Metoda wirtualna.
	 * @return Zwraca wspó³rzêdne nastêpnego ruchu
	 */
	virtual std::pair<int, int> getNextMove();
};

/**
 * @class RandomAI
 * @brief Klasa AI przeciwnika (losowe ruchy).
 */
class RandomAI : public EnemyAI {
	std::random_device device; /**< Urz¹dzenie losuj¹ce */
	std::default_random_engine engine; /**< Silnik losuj¹cy */
	std::uniform_int_distribution<int> randDirection; /**< Jednolity rozk³ad ca³kowity */

public:
	/**
	 * @brief Konstruktor klasy.
	 */
	RandomAI() : EnemyAI(), engine(device()), randDirection(0, 3) {}
	/**
	 * @brief Metoda wirtualna.
	 * @return Zwraca wspó³rzêdne nastêpnego ruchu
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
	 * @return Zwraca wspó³rzêdne nastêpnego ruchu
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
	 * @param fl Pod³oga
	 */
	Enemy(int pX, int pY, const std::vector<std::vector<bool>>& fl) : Object(pX, pY, fl), ai(new NoAI()) {};
	/**
	 * @brief Metoda wirtualna.
	 * @return Zwraca symbol przeciwnika
	 */
	virtual char getSymbol() const { return symbol::enemy; }

	/**
	 * @brief Metoda zmieniaj¹ca AI przeciwnika.
	 */
	void changeAI(std::unique_ptr<EnemyAI> ai);

	/**
	 * @brief Metoda aktualizuj¹ca pozycjê przeciwnika.
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
	 * @param fl Pod³oga
	 */
	Player(int pX, int pY, const std::vector<std::vector<bool>>& fl) : Object(pX, pY, fl) {}
	/**
	 * @brief Metoda wirtualna.
	 * @return Zwraca symbol gracza
	 */
	virtual char getSymbol() const { return symbol::player; }

	/**
	 * @brief Metoda poruszaj¹ca gracza do góry.
	 */
	void up();
	/**
	 * @brief Metoda poruszaj¹ca gracza w dó³.
	 */
	void down();
	/**
	 * @brief Metoda poruszaj¹ca gracza w lewo.
	 */
	void left();
	/**
	 * @brief Metoda poruszaj¹ca gracza w prawo.
	 */
	void right();
};
