<<<<<<<< HEAD:ConsoleApplication1/main.cpp
﻿
========
﻿/**
 * @file main.cpp
 * @brief Main menu for FCAI Board Games Collection - Part 1
 *
 * This file contains the main menu and game launcher for Part 1 of the assignment.
 * Part 1 includes one group game (Numerical Tic-Tac-Toe) with a simple menu system.
 */
>>>>>>>> ccf4a4eb145740024e83ffece95dbf290ec929c5:ConsoleApplication1/Main.cpp
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "NumericalTicTacToe_Classes.h"
<<<<<<<< HEAD:ConsoleApplication1/main.cpp
#include <memory>
#include "SUSTicTacToe_Classes.h"

========
#include "InverseTicTacToe.h"
#include "PyramidXO_Classes.h"
>>>>>>>> ccf4a4eb145740024e83ffece95dbf290ec929c5:ConsoleApplication1/Main.cpp
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
    GameManager<char> numerical_game(SUS_board, players, game_ui);
    numerical_game.run();

    // Cleanup memory
    delete SUS_board;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
    delete[] players;
    delete game_ui;

    cout << "=== Game Finished ===\n\n";

}


void displayMenu() {
    cout << "=========================================\n";
    cout << "      FCAI Board Games Collection       \n";
    cout << "             Part 1 - CS213            \n";
    cout << "=========================================\n";
    cout << "1. Play Numerical Tic-Tac-Toe (Game 9)\n";
<<<<<<<< HEAD:ConsoleApplication1/main.cpp
    cout << "2. PLay SUS Tic-Tac-Toe (Game 1)\n"; 
    cout << "3. Exit Program\n";
    cout << "=========================================\n";
    cout << "Enter your choice ";
========
    cout << "2. Play Inverse Tic-Tac-Toe (Game 5)\n";
	cout << "3. Play Pyramid Tic-Tac-Toe (Game 8)\n";
    cout << "4. Exit Program\n";
    cout << "=========================================\n";
    cout << "Enter your choice (1-4): ";
>>>>>>>> ccf4a4eb145740024e83ffece95dbf290ec929c5:ConsoleApplication1/Main.cpp
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
<<<<<<<< HEAD:ConsoleApplication1/main.cpp
        case 2: 
            playSUS(); 
            break; 
        case 3:
========
        case 2 :
            playInverseTicTacToe();
            break;
        case 3:
            playPyramidXO();
			break;
        case 4:
>>>>>>>> ccf4a4eb145740024e83ffece95dbf290ec929c5:ConsoleApplication1/Main.cpp
            cout << "\nThank you for playing FCAI Board Games!\n";
            cout << "Goodbye!\n";
            break;
        default:
            cout << "Invalid choice! Please enter 1 or 2.\n\n";
        }
<<<<<<<< HEAD:ConsoleApplication1/main.cpp
    } while (choice != 3);
========
    } while (choice != 4);
>>>>>>>> ccf4a4eb145740024e83ffece95dbf290ec929c5:ConsoleApplication1/Main.cpp

    return 0;
}