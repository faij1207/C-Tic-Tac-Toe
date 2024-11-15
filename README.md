# Tic-Tac-Toe Game in C

Tic-Tac-Toe is a grid-based game implemented in C, offering two modes of gameplay:

- **Two-Player Mode:** Two users can play against each other.

- **Single-Player Mode:** Play against an AI that uses the Minimax algorithm for optimal moves.

## Features

- **Two Modes:**

- Two-Player Mode: Play with another user.

- Single-Player Mode: Play against an intelligent AI.

- **3x3 Grid:** The board is represented by a 3x3 grid.
- **Win Conditions:** Horizontal, vertical, or diagonal match wins the game.
- **Draw Condition:** Declared when the grid is full and no one wins.
- **AI Algorithm:** Uses the Minimax algorithm to evaluate the best possible moves.

## How to Play

1. Clone the repository:

     ```bash
     git clone https://github.com/faij1207/Tic-Tac-Toe-Game.git
     ```

2. Compile the code:

     ```bash
     gcc tictactoe.c -o tictactoe
     ```

3. Run the executable:

     ```bash
     ./tic_tac_toe
     ```

4. Choose the mode:
     - Enter 1 for Two-Player Mode.
     - Enter 2 for Single-Player Mode.
5. Follow the instructions to make your move by entering a number (1–9) corresponding to the grid position.

## Output Example

### Game Board Representation

```plaintext
 1 | 2 | 3
-----------
 4 | 5 | 6
-----------
 7 | 8 | 9
```

### Sample Gameplay

- **Player 1 Move (X):** Enters 5
- **AI Move (O):** Places O at position 1

**Current Game Board:**

```plaintext
 O | 2 | 3
-----------
 4 | X | 6
-----------
 7 | 8 | 9
```

- **Player 1 Move (X):** Enters 2
- **AI Move (O):** Places O at position 3

**Current Game Board:**

```plaintext
 O | X | O
-----------
 4 | X | 6
-----------
 7 | 8 | 9
```

- **Player 1 Move (X):** Enters 8
- **AI Move (O):** Places O at position 4

**Final Game Board:**

```plaintext
 O | X | O
-----------
 O | X | 6
-----------
 7 | X | 9
```

**Result:** Player 1 Wins (Diagonal Match)!

## File Structure

```plaintext
Tic-Tac-Toe-Game/
├── tic_tac_toe.c  # Main C source code
├── README.md      # Project documentation
```

## Technologies Used

- **Programming Language:** C
- **Algorithm:** Minimax (for AI)

## Contributing

Feel free to fork this repository and contribute! You can submit pull requests to improve features or fix bugs.

## License

This project is licensed under the MIT License. See the LICENSE file for details.

Happy Coding!
