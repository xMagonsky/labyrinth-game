#include "logic.h"


bool Object::collision(int x, int y) {
	if (this->posX == x && this->posY == y) {
		return true;
	}
	return false;
}


void Player::up() {
	int newPosX = posX - 1;
	if (newPosX < 0) return;

	if (floor[newPosX][posY]) {
		posX -= 1;
	}
}

void Player::down() {
	int newPosX = posX + 1;
	if (newPosX >= floor.size()) return;

	if (floor[newPosX][posY]) {
		posX += 1;
	}
}

void Player::left() {
	int newPosY = posY - 1;
	if (newPosY < 0) return;

	if (floor[posX][newPosY]) {
		posY -= 1;
	}
}

void Player::right() {
	int newPosY = posY + 1;
	if (newPosY >= floor[0].size()) return;

	if (floor[posX][newPosY]) {
		posY += 1;
	}
}


void Enemy::updatePosition() {
	std::pair<int, int> p = ai->getNextMove();
	posX = p.first;
	posY = p.second;
}

void Enemy::changeAI(std::unique_ptr<EnemyAI> ai) {
	ai->setVariables(this->posX, this->posY, this->floor);
	this->ai = std::move(ai);
}

void EnemyAI::setVariables(int x, int y, const std::vector<std::vector<bool>>& floor) {
	this->posX = x;
	this->posY = y;
	this->floor = floor;
}

std::pair<int, int> NoAI::getNextMove() {
	return { posX, posY };
}

std::pair<int, int> RandomAI::getNextMove() {
	while (true) {
		int direction = randDirection(engine);

		switch (direction) {
		case 0:
		{
			int newPosX = posX - 1;
			if (newPosX < 0) break;

			if (floor[newPosX][posY]) {
				posX -= 1;
				return { newPosX, posY };
			}
			break;
		}
		case 1:
		{
			int newPosX = posX + 1;
			if (newPosX >= floor.size()) break;

			if (floor[newPosX][posY]) {
				posX += 1;
				return { newPosX, posY };
			}
			break;
		}
		case 2:
		{
			int newPosY = posY - 1;
			if (newPosY < 0) break;

			if (floor[posX][newPosY]) {
				posY -= 1;
				return { posX, newPosY };
			}
			break;
		}
		case 3:
		{
			int newPosY = posY + 1;
			if (newPosY >= floor[0].size()) break;

			if (floor[posX][newPosY]) {
				posY += 1;
				return { posX, newPosY };
			}
			break;
		}
		default:
			break;
		}
	}
}

std::pair<int, int> PathfindingAI::getNextMove() {
	return std::pair<int, int>();
}
