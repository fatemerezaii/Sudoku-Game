# Sudoku Game 

A console-based Sudoku game developed in C++.

The game generates Sudoku puzzles, allows players to solve them through an interactive menu, and tracks player performance through a scoreboard.

## Features

- **Three Difficulty Levels**
  - Easy: 30 empty cells and 200 moves
  - Medium: 40 empty cells and 150 moves
  - Hard: 60 empty cells and 100 moves

- **Random Puzzle Generation**  
  Generates a completed Sudoku board and removes cells to create a puzzle.

- **Interactive Gameplay**  
  Navigate the board using the arrow keys and enter numbers using the keyboard.

- **Input Validation**  
  Checks rows, columns, and 3×3 subgrids to prevent invalid number placements.

- **Move Limit**  
  Players have a limited number of moves to complete the puzzle.

- **Delete Numbers**  
  Remove entered numbers while respecting the fixed cells of the puzzle.

- **Save and Continue**  
  Save the current game and resume it later.

- **Scoreboard**  
  Track player wins and losses, with rankings based on wins and losses.

- **Colored Console Interface**  
  Uses ANSI escape codes to display the Sudoku board, cursor, game status, and messages.

- **Elapsed Time Display**  
  Displays the time elapsed during gameplay.

## Technologies Used

- C++
- Standard C++ libraries
- File handling (`ifstream` and `ofstream`)
- Backtracking and recursion
- Random number generation
- Windows console input handling

## How to Play

1. Launch the game.
2. Select **New Game** from the main menu.
3. Choose a difficulty level.
4. Use the arrow keys to navigate the Sudoku board.
5. Press a number key (`1`–`9`) to enter a number into an empty cell.
6. Use the available menu options to delete numbers, check the board, save the game, or exit.
7. Complete the puzzle before running out of moves.

## Main Menu

- New Game
- Scoreboard
- Continue Saved Game
- Exit

## Game Rules

- Each row must contain the numbers 1 through 9 without repetition.
- Each column must contain the numbers 1 through 9 without repetition.
- Each 3×3 subgrid must contain the numbers 1 through 9 without repetition.
- Fixed cells cannot be edited.
- Invalid moves consume a move.
- The game ends when the move limit is reached or the puzzle is completed.

## Data Persistence

The game uses text files to store game data:

- `scoreBoard.txt` — Stores player names, wins, and losses.
- `SavedGame.txt` — Stores the board state, remaining moves, empty-cell count, and fixed-cell information.

These files are created or updated by the game when the corresponding features are used.

## Requirements

- A C++ compiler
- A Windows environment for the current console implementation

The project uses Windows-specific headers such as `windows.h` and `conio.h` for console interaction.

## Build and Run

Compile the source file using a C++ compiler that supports the required Windows headers.

For example, with MinGW on Windows:

```bash
g++ main.cpp -o sudoku.exe
```

Run the executable:

```bash
./sudoku.exe
```

If your source file has a different name, replace `main.cpp` with the correct filename.

## Project Structure

```text
Sudoku-Game/
├── main.cpp
├── README.md
├── scoreBoard.txt    # Created/updated during gameplay
└── SavedGame.txt     # Created when saving a game
```

The text files may be generated at runtime, depending on the features used.

## Future Improvements

- Improve puzzle generation to guarantee a unique solution.
- Add more robust save/load error handling.
- Improve cross-platform compatibility.
- Separate game logic, user interface, and data management into different modules.

## Author

Fateme Rezaii

## License

No license has been specified yet.
