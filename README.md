# Maze Game

## Overview
This project is a console-based maze game written in C++. The game challenges the player to navigate through a maze, collect items (coins), avoid moving enemies, and reach the exit. The maze consists of various field types (floor, walls, exit) that react differently to player interaction. The game also maintains a leaderboard to store high scores, supporting both named users and anonymous players identified by a numeric value.

The project adheres to object-oriented programming (OOP) principles and utilizes advanced C++ techniques such as inheritance, polymorphism, templates, and design patterns.

## Features
- **Maze Navigation**: Players move through a dynamically generated maze using arrow keys.
- **Item Collection**: Collect coins scattered across the maze to increase your score.
- **Enemies**: Avoid moving enemies that can end the game upon contact.
- **Exit Goal**: Reach the exit to complete the maze.
- **Field Types**: Different field behaviors (walls block movement, floor allows passage, exit ends the game).
- **Leaderboard**: Persistent score history stored in `leaderboard.txt` for both named and anonymous players.
- **Console Interface**: Simple, text-based display with a menu system controlled via arrow keys and Enter.

## Technical Requirements
The game was developed with the following OOP and C++ techniques:
- **Classes with Inheritance**: Base class `Object` with derived classes like `Coin`, `Enemy`, and `Exit`.
- **Polymorphism**: Different objects return unique symbols (e.g., `x` for enemies, `$` for coins) for display.
- **Templates**: Used in the leaderboard to handle both `std::string` (named users) and `int` (anonymous users).
- **Design Pattern**: Strategy pattern for managing enemy AI algorithms, allowing easy extension.
- **Additional Technique**: Operator overloading for intuitive interaction with the `Floor` class (treated like a 2D vector).

The application separates logic (e.g., `Game`, `Floor`) from display (`Display` class) for better modularity.

## Usage
1. Launch the executable.
2. Use the arrow keys to navigate the start menu and press Enter to select an option.
3. In-game controls:
   - **Arrow Keys**: Move the player (up, down, left, right).
   - Reach the exit to win or avoid enemies to survive.
4. After the game ends, enter your name for the leaderboard or leave it blank to remain anonymous.
5. Scores are saved to `leaderboard.txt` in the format: `{name / anonymous ID} - {coin count}`.

## Project Structure
- **Game**: Main class managing gameplay, containing instances of `Floor`, `Player`, `Exit`, and vectors of `Coin` and `Enemy`.
- **Floor**: Generates and manages the maze layout.
- **Object**: Base class for interactive elements (coins, enemies, exit).
- **Display**: Handles console rendering.
- **Leaderboard**: Manages score storage and retrieval from `leaderboard.txt`.

The game runs in an infinite loop with a frame rate limit of 60 FPS.

## Testing
- **Boundary Checks**: Prevents out-of-bounds movement to avoid memory access errors.
- **Collision Detection**: Ensures proper interaction with coins (score increase) and enemies (game over).
- **UI Validation**: Limits menu navigation to valid options using arrow keys and Enter.

## Conclusions
This project demonstrates the power of object-oriented programming in creating modular, extensible software. Inheritance and polymorphism enabled a flexible hierarchy of game objects, while the Strategy pattern allows for future enemy AI enhancements. Templates and operator overloading improved code reusability and usability. The separation of logic and display ensures maintainability, making this a solid foundation for further development.
