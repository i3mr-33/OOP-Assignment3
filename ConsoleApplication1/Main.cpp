
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "NumericalTicTacToe_Classes.h"
#include <memory>
#include "SUSTicTacToe_Classes.h"
#include "InverseTicTacToe.h"
#include "PyramidXO_Classes.h"
#include "4x4TicTacToe.h"
#include "InfinityTic-Tac-Toe.h"
#include "TicTacToe5x5_Classes.h"
#include "DiamondTicTacToe.h"

using namespace std;


void playNumericalTicTacToe() {
    cout << "\n=== Starting Numerical Tic-Tac-Toe ===\n";

    // Seed random number generator
    srand(static_cast<unsigned int>(time(0)));

    // Create game components
    UI<int>* game_ui = new NumericalTicTacToe_UI();
    Board<int>* numerical_board = new NumericalTicTacToe_Board();
    Player<int>** players = game_ui->setup_players();

    // Create and run game manager
    GameManager<int> numerical_game(numerical_board, players, game_ui);
    numerical_game.run();

    // Cleanup memory
    delete numerical_board;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
    delete[] players;
    delete game_ui;

    cout << "=== Game Finished ===\n\n";
}
void playInverseTicTacToe() {
    cout << "\n=== Starting Inverse Tic-Tac-Toe ===\n";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator

    // Create an instance of the specific UI for X-O using a pointer 
    UI<char>* game_ui = new InverseTicTacToe_UI();

    // Create the game board. For X-O, this is an X_O_Board.
    Board<char>* xo_board = new InverseTicTacToe_Board();

    // Use the UI to set up the players for the game.
    // The UI returns a dynamically allocated array of Player pointers.
    Player<char>** players = game_ui->setup_players();

    // Create the game manager with the board and the array of players.
    GameManager<char> x_o_game(xo_board, players, game_ui);
    x_o_game.run();
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
    delete[] players;
    delete game_ui;
    cout << "=== Game Finished ===\n\n";

}
void playPyramidXO() {

    cout << "\n=== Starting Pyramid Tic-Tac-Toe ===\n";

    UI<char>* game_ui = new PyramidXO_UI();
    Board<char>* pyramid_board = new PyramidX_O_Board();


    Player<char>** players = game_ui->setup_players();

    GameManager<char> pyramid_game(pyramid_board, players, game_ui);

    pyramid_game.run();

    delete pyramid_board;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
    delete[] players;
    delete game_ui;

    cout << "=== Game Finished ===\n\n";
}


void playSUS() {
    cout << "\n === Starting SUS Game ===\n";

    // Seed random number generator
    srand(static_cast<unsigned int>(time(0)));

    // Create game components
    UI<char>* game_ui = new SUS_UI();
    Board<char>* SUS_board = new SUS_Board();
    Player<char>** players = game_ui->setup_players();

    // Create and run game manager
    GameManager<char> SUS_game(SUS_board, players, game_ui);
    SUS_game.run();

    // Cleanup memory
    delete SUS_board;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
    delete[] players;
    delete game_ui;

    cout << "=== Game Finished ===\n\n";

}
void Play4x4() {
    cout << "\n === Starting 4x4 Tic-Tac-Toe Game ===\n";

    // Seed random number generator
    srand(static_cast<unsigned int>(time(0)));

    // Create game components
    UI<char>* game_ui = new TicTacToe4x4_UI();
    Board<char>* TicTacToe4x4_board = new TicTacToe4x4_Board();
    Player<char>** players = game_ui->setup_players();

    // Create and run game manager
    GameManager<char> TicTacToe4x4_game(TicTacToe4x4_board, players, game_ui);
    TicTacToe4x4_game.run();

    // Cleanup memory
    delete TicTacToe4x4_board;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
    delete[] players;
    delete game_ui;

    cout << "=== Game Finished ===\n\n";

}
void playInfinityTicTacToe() {
    cout << "\n=== Starting Infinite Tic-Tac-Toe ===\n";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator

    // Create an instance of the specific UI for X-O using a pointer 
    UI<char>* game_ui = new Infinity_UI();

    // Create the game board. For X-O, this is an X_O_Board.
    Board<char>* xo_board = new Infinity_Board();

    // Use the UI to set up the players for the game.
    // The UI returns a dynamically allocated array of Player pointers.
    Player<char>** players = game_ui->setup_players();

    // Create the game manager with the board and the array of players.
    GameManager<char> x_o_game(xo_board, players, game_ui);
    x_o_game.run();
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
    delete[] players;
    delete game_ui;
    cout << "=== Game Finished ===\n\n";

}
void play5x5TicTacToe() {
    cout << "\n=== Starting Infinite Tic-Tac-Toe ===\n";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator

    // Create an instance of the specific UI for X-O using a pointer 
    UI<char>* game_ui = new TicTacToe5x5_UI();

    // Create the game board. For X-O, this is an X_O_Board.
    Board<char>* xo_board = new TicTacToe5x5_Board();

    // Use the UI to set up the players for the game.
    // The UI returns a dynamically allocated array of Player pointers.
    Player<char>** players = game_ui->setup_players();

    // Create the game manager with the board and the array of players.
    GameManager<char> x_o_game(xo_board, players, game_ui);
    x_o_game.run();
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
    delete[] players;
    delete game_ui;
    cout << "=== Game Finished ===\n\n";

}

void playDiamondTicTacToe() {
    cout << "\n=== Starting Diamond Tic-Tac-Toe ===\n";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator

    // Create an instance of the specific UI for Diamond Tic-Tac-Toe
    UI<char>* game_ui = new DiamondTicTacToe_UI();

    // Create the game board
    Board<char>* diamond_board = new DiamondTicTacToe_Board();

    // Use the UI to set up the players for the game
    Player<char>** players = game_ui->setup_players();

    // Create the game manager with the board and the array of players
    GameManager<char> diamond_game(diamond_board, players, game_ui);
    diamond_game.run();

    // Clean up
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
    delete[] players;
    delete diamond_board;
    delete game_ui;
    cout << "=== Diamond Tic-Tac-Toe Finished ===\n\n";
}

void displayMenu() {
    cout << "=========================================\n";
    cout << "      FCAI Board Games Collection       \n";
    cout << "             Part 1 - CS213            \n";
    cout << "=========================================\n";
    cout << "1. Play Numerical Tic-Tac-Toe (Game 9)\n";
    cout << "2. Play Inverse Tic-Tac-Toe (Game 5)\n";
	cout << "3. Play Pyramid Tic-Tac-Toe (Game 8)\n";
    cout << "4. PLay SUS Tic-Tac-Toe (Game 1)\n";
    cout << "5. PLay 4x4 Tic-Tac-Toe (Game 7)\n";
	cout << "6. Play Infinity Tic-Tac-Toe (Game 11)\n";
	cout << "7. Play 5x5 Tic-Tac-Toe (Game 3)\n";
    cout << "8. Play Diamond Tic-Tac-Toe (Game 6)\n";
    cout << "9. Exit Program\n";
    cout << "=========================================\n";
    cout << "Enter your choice (1-9): ";
}


int main() {
    int choice;

    // Seed random number generator for the entire program
    srand(static_cast<unsigned int>(time(0)));

    cout << "Welcome to FCAI Board Games - Assignment 3\n";

    do {
        displayMenu();
        cin >> choice;

        // Clear input buffer
        cin.clear();
        cin.ignore(10000, '\n');

        switch (choice) {
        case 1:
            playNumericalTicTacToe();
            break; 
        case 2:
            playInverseTicTacToe();
            break;
        case 3:
            playPyramidXO();
			break;
        case 4:
            playSUS(); 
            break; 
        case 5:
            Play4x4();
            break;
		case 6:
            playInfinityTicTacToe();
			break;
        case 7:
            play5x5TicTacToe();
			break;
        case 8:
            playDiamondTicTacToe();
            break;
        case 9:
            cout << "\nThank you for playing FCAI Board Games!\n";
            cout << "Goodbye!\n";
            break;
        default:
            cout << "Invalid choice! Please enter 1 or 9.\n\n";
        }


    } while (choice != 9);
    return 0;
}