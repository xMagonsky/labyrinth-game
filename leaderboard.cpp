#include "leaderboard.h"

void Leaderboard::display(std::ostream& stream) {
	std::ifstream file;
	file.open(filePath);

	if (!file.is_open()) {
		//error
		return;
	}

	std::string nick, score;
	while (file >> nick >> score) {
		stream << nick << " - punkty: " << score << std::endl;
	}
	
	file.close();
}
