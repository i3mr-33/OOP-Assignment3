
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "NumericalTicTacToe_Classes.h"
#include <memory>
#include "SUSTicTacToe_Classes.h"

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
    cout << "2. PLay SUS Tic-Tac-Toe (Game 1)\n"; 
    cout << "3. Exit Program\n";
    cout << "=========================================\n";
    cout << "Enter your choice ";
}


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
            playSUS(); 
            break; 
        case 3:
            cout << "\nThank you for playing FCAI Board Games!\n";
            cout << "Goodbye!\n";
            break;
        default:
            cout << "Invalid choice! Please enter 1 or 2.\n\n";
        }
    } while (choice != 3);

    return 0;
}