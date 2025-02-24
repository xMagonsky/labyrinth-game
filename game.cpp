#include "game.h"
#include <chrono>

Game::Game() {
	display.showStatMenu();

	this->sizeX = 25;
	this->sizeY = 35;
	floor.generateMaze(sizeX, sizeY);

	display.changeSize(sizeX, sizeY);

	int exitX = sizeX - 2;
	int exitY = sizeY - 1;
	floor[exitX][exitY] = true;
	exit = new Exit(exitX, exitY);
	
	player = new Player(1, 1, floor);

	addCoins(20);
	addEnemies(1);
}

Game::~Game() {
	delete player;
	delete exit;
	for (size_t i = 0; i < coins.size(); i++) delete coins[i];
	for (size_t i = 0; i < enemies.size(); i++) delete enemies[i];
}

void Game::start() {
	const int fps = 60;
	const int updateTickCount = 20;

	const double refrashRate = 1000.0 / fps;
	int updateTick = 0;
	bool win = false;
	
	auto start = std::chrono::high_resolution_clock::now();
	auto end = std::chrono::high_resolution_clock::now();

	bool play = true;
	while (play) {
		end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::milli> elapsed = end - start;
		
		if (elapsed.count() >= refrashRate) {
			start = end;

			KeyAction action = display.getKeyPressAction();
			switch (action) {
			case UP:
				player->up();
				break;
			case DOWN:
				player->down();
				break;
			case LEFT:
				player->left();
				break;
			case RIGHT:
				player->right();
				break;
			default:
				break;
			}

			if (updateTick == updateTickCount) {
				for (auto& enemy : enemies) {
					enemy->updatePosition();
				}
				updateTick = 0;
			}
			updateTick++;

			if (exit->collision(player->getX(), player->getY())) {
				play = false;
				win = true;
			}

			for (size_t i = 0; i < coins.size(); ) {
				if (coins[i]->collision(player->getX(), player->getY())) {
					coins.erase(coins.begin() + i);

					this->points++;
				}
				else {
					i++;
				}
			}

			for (size_t i = 0; i < enemies.size(); i++) {
				if (enemies[i]->collision(player->getX(), player->getY())) {
					play = false;
					win = false;
				}
			}

			Game::print();
		}
	}

	display.showEnding(win, points);
}

void Game::addCoins(int n) {
	std::random_device device;
	std::default_random_engine engine(device());
	std::uniform_int_distribution<int> randX(1, static_cast<int>(floor.size() - 2));
	std::uniform_int_distribution<int> randY(1, static_cast<int>(floor[0].size() - 2));

	for (size_t i = 0; i < n; ) {
		int x = randX(engine);
		int y = randY(engine);

		if (floor[x][y] && (x != 1 || y != 1)) {
			bool colision = false;
			for (auto& coin : coins) {
				if (coin->collision(x, y)) {
					colision = true;
					break;
				}
			}

			if (!colision) {
				coins.push_back(new Coin(x, y, floor));
				i++;
			}
		}
	}
}

void Game::addEnemies(int n) {
	std::random_device device;
	std::default_random_engine engine(device());
	std::uniform_int_distribution<int> randX(1, static_cast<int>(floor.size() - 2));
	std::uniform_int_distribution<int> randY(1, static_cast<int>(floor[0].size() - 2));

	for (size_t i = 0; i < n; ) {
		int x = randX(engine);
		int y = randY(engine);

		if (floor[x][y] && (x > 5 || y > 5)) {
			bool colision = false;
			for (auto& enemy : enemies) {
				if (enemy->collision(x, y)) {
					colision = true;
					break;
				}
			}

			if (!colision) {
				Enemy* e = new Enemy(x, y, floor);
				e->changeAI(std::make_unique<RandomAI>());
				enemies.push_back(e);
				i++;
			}
		}
	}
}

void Game::print() {
	display.draw(floor);

	display.draw(exit);

	for (size_t i = 0; i < coins.size(); i++) {
		display.draw(coins[i]);
	}

	for (size_t i = 0; i < enemies.size(); i++) {
		display.draw(enemies[i]);
	}

	display.draw(player);

	display.print();

	display.printPoints(points);
}
