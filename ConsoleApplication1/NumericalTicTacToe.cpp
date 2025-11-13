/**
 * @file main.cpp
 * @brief Main menu for FCAI Board Games Collection - Part 1
 *
 * This file contains the main menu and game launcher for Part 1 of the assignment.
 * Part 1 includes one group game (Numerical Tic-Tac-Toe) with a simple menu system.
 */

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "NumericalTicTacToe_Classes.h"

using namespace std;

/**
 * @brief Plays the Numerical Tic-Tac-Toe game
 *
 * Initializes and runs the Numerical Tic-Tac-Toe game with all necessary components.
 * Handles the complete game lifecycle including setup, execution, and cleanup.
 */
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

/**
 * @brief Displays the main menu
 *
 * Shows available options to the user including the group game and exit option.
 */
void displayMenu() {
    cout << "=========================================\n";
    cout << "      FCAI Board Games Collection       \n";
    cout << "             Part 1 - CS213            \n";
    cout << "=========================================\n";
    cout << "1. Play Numerical Tic-Tac-Toe (Game 9)\n";
    cout << "2. Exit Program\n";
    cout << "=========================================\n";
    cout << "Enter your choice (1-2): ";
}

/**
 * @brief Main function - Program entry point
 *
 * Controls the main program flow, displays menu, and handles user input
 * to launch the selected game or exit the program.
 *
 * @return int Returns 0 on successful execution
 */
int main() {
    int choice;

    // Seed random number generator for the entire program
    srand(static_cast<unsigned int>(time(0)));

    cout << "Welcome to FCAI Board Games - Assignment 3 Part 1\n";

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
            cout << "\nThank you for playing FCAI Board Games!\n";
            cout << "Goodbye!\n";
            break;
        default:
            cout << "Invalid choice! Please enter 1 or 2.\n\n";
        }
    } while (choice != 2);

    return 0;
}