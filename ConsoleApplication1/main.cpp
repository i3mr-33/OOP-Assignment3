
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
#include "Four-in-a-rowTicTacToe.h"
#include "Obstacles_TTT_classes.h"
#include "WordTTT_Classes.h"

using namespace std;

void playNumericalTicTacToe()
{
    cout << "\n=== Starting Numerical Tic-Tac-Toe ===\n";
    cout << "\nInstructions:\n";
    cout << "Player 1 uses odd numbers (1,3,5,7,9) and Player 2 uses even numbers (2,4,6,8).\n";
    cout << "Players take turns placing one unused number in an empty cell.\n";
    cout << "Win by forming a row, column, or diagonal with sum = 15.\n";
    cout << "If the board is full with no sum = 15, the game is a draw.\n\n";

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
    for (int i = 0; i < 2; ++i)
    {
        delete players[i];
    }
    delete[] players;
    delete game_ui;

    cout << "=== Game Finished ===\n\n";
}
void playInverseTicTacToe()
{
    cout << "\n=== Starting Inverse Tic-Tac-Toe ===\n";
    cout << "\nInstructions:\n";
    cout << "Players try to avoid forming three marks in a row, column, or diagonal.\n";
    cout << "A player loses if they complete a line of three of their own marks.\n";
    cout << "If the board is full and no line is formed, the game is a draw.\n\n";

    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator

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
    for (int i = 0; i < 2; ++i)
    {
        delete players[i];
    }
    delete[] players;
    delete game_ui;
    cout << "=== Game Finished ===\n\n";
}
void playPyramidXO()
{

    cout << "\n=== Starting Pyramid Tic-Tac-Toe ===\n";
    cout << "\nInstructions:\n";
    cout << "Players take turns placing their 'X' or 'O' marks in empty squares.\n";
    cout << "The first player to place three of their marks in a row, column, or diagonal wins.\n\n";


    UI<char>* game_ui = new PyramidXO_UI();
    Board<char>* pyramid_board = new PyramidX_O_Board();

    Player<char>** players = game_ui->setup_players();

    GameManager<char> pyramid_game(pyramid_board, players, game_ui);

    pyramid_game.run();

    delete pyramid_board;
    for (int i = 0; i < 2; ++i)
    {
        delete players[i];
    }
    delete[] players;
    delete game_ui;

    cout << "=== Game Finished ===\n\n";
}

void playSUS()
{
    cout << "\n === Starting SUS Game ===\n";
    cout << "\nInstructions:\n";
    cout << "Players take turns placing either an S or a U in an empty square.\n";
    cout << "Each player must use the same letter every turn.\n";
    cout << "A player scores a point for each S-U-S sequence they create.\n";
    cout << "The game ends when the board is full.\n";
    cout << "The player with the most S-U-S sequences wins.\n\n";


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
    for (int i = 0; i < 2; ++i)
    {
        delete players[i];
    }
    delete[] players;
    delete game_ui;

    cout << "=== Game Finished ===\n\n";
}
void Play4x4()
{
    cout << "\n === Starting 4x4 Tic-Tac-Toe Game ===\n";
    cout << "\nInstructions:\n";
    cout << "Players take turns moving one of their tokens(X or O)\n";
    cout << "to an adjacent empty square (horizontal or vertical only).\n";
    cout << "Tokens cannot move diagonally.\n";
    cout << "Tokens cannot jump over other tokens.\n";
    cout << "The first player to align three of their tokens\n";
    cout << "in a row, column, or diagonal wins.\n\n";


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
    for (int i = 0; i < 2; ++i)
    {
        delete players[i];
    }
    delete[] players;
    delete game_ui;

    cout << "=== Game Finished ===\n\n";
}
void playInfinityTicTacToe()
{
    cout << "\n=== Starting Infinite Tic-Tac-Toe ===\n";
    cout << "\nInstructions:\n";
    cout << "After every three moves, the oldest mark on the board disappears.\n";
    cout << "The first player to align three marks in a row\n";
    cout << "before any of those marks vanish wins the game.\n\n";

    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator

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
    for (int i = 0; i < 2; ++i)
    {
        delete players[i];
    }
    delete[] players;
    delete game_ui;
    cout << "=== Game Finished ===\n\n";
}
void play5x5TicTacToe()
{
    cout << "\n=== Starting 5x5 Tic-Tac-Toe ===\n";
    cout << "\nInstructions:\n";
    cout << "Players take turns placing their mark in an empty square.\n";
    cout << "The game continues until only one square remains empty.\n";
    cout << "This results in a total of 24 moves.\n";
    cout << "Each player makes 12 moves.\n\n";

    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator

    // Create an instance of the specific UI for X-O using a pointer
    TicTacToe5x5_UI* ui = new TicTacToe5x5_UI();

    // Create the game board. For X-O, this is an X_O_Board.
    TicTacToe5x5_Board* board = new TicTacToe5x5_Board();

    // Use the UI to set up the players for the game.
    // The UI returns a dynamically allocated array of Player pointers.
    Player<char>** players = ui->setup_players();

    // Create the game manager with the board and the array of players.
    GameManager<char> gm(board, players, ui);
    gm.run();
    delete players[0];
    delete players[1];
    delete[] players;
    delete board;
    delete ui;
    cout << "=== Game Finished ===\n\n";
}

void playDiamondTicTacToe()
{
    cout << "\n=== Starting Diamond Tic-Tac-Toe ===\n";
    cout << "\nInstructions:\n";
    cout << "Players take turns placing their 'X' or 'O' in empty cells.\n";
    cout << "A player wins by simultaneously completing:\n";
    cout << "- A line of three marks, and\n";
    cout << "- A line of four marks.\n";
    cout << "The two lines must be in different directions\n";
    cout << "(e.g., one horizontal and one diagonal).\n";
    cout << "The two lines may share one common mark.\n\n";

    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator

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
    for (int i = 0; i < 2; ++i)
    {
        delete players[i];
    }
    delete[] players;
    delete diamond_board;
    delete game_ui;
    cout << "=== Diamond Tic-Tac-Toe Finished ===\n\n";
}

void playConnectFour()
{
    cout << "\n === Starting Connect Four Game ===\n";
    cout << "\nInstructions:\n";
    cout << "The first player places an 'X' in the bottom-most square of any column.\n";
    cout << "Subsequent players take turns placing their mark\n";
    cout << "in the lowest available square of any column.\n";
    cout << "The first player to get four of their marks in\n";
    cout << "a row, horizontally, vertically, or diagonally wins.\n\n";
    cout << "The game is a draw if the board fills without a winner.\n\n";


    // Seed random number generator
    srand(static_cast<unsigned int>(time(0)));

    // Create game components
    UI<char>* game_ui = new Connect_Four_UI();
    Board<char>* Connect_Four_board = new Connect_Four_Board();
    Player<char>** players = game_ui->setup_players();

    // Create and run game manager
    GameManager<char> Connect_Four_game(Connect_Four_board, players, game_ui);
    Connect_Four_game.run();

    // Cleanup memory
    delete Connect_Four_board;
    for (int i = 0; i < 2; ++i)
    {
        delete players[i];
    }
    delete[] players;
    delete game_ui;

    cout << "=== Game Finished ===\n\n";
}
void ObstacleTicTacToe() {
    cout << "\n=== Starting Obstacle Tic-Tac-Toe ===\n";
    cout << "\nInstructions\n";
    cout << "After every round (one turn for each player),\n";
    cout << "two new obstacle cells are randomly added to the board.\n";
    cout << "These cells cannot be used by either player.\n";
    cout << "The first player to align four of their marks in \n";
    cout << "a row, horizontally, vertically, or diagonally wins.\n";
    cout << "The game is a draw if the board fills without a winner.\n\n";

    srand(static_cast<unsigned int>(time(0)));

    // Create game components
    Obstacles_UI* game_ui = new Obstacles_UI();
    Obstacles_Board* obs_board = new Obstacles_Board();

    // Link UI to board
    game_ui->set_board(obs_board);

    // Setup players
    Player<char>** players = game_ui->setup_players();

    // Create and run game manager
    GameManager<char> obs_game(obs_board, players, game_ui);
    obs_game.run();

    // Cleanup
    delete obs_board;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
    delete[] players;
    delete game_ui;


    cout << "=== Game Finished ===\n\n";

}
void playWordTicTacToe()
{
    cout << "\n=== Starting Word Tic-Tac-Toe ===\n";
    cout << "\nInstructions:\n";
    cout << "Players take turns placing one letter on the board.\n";
    cout << "Players attempt to form a valid word.\n";
    cout << "Letters already on the board can be used to build words.\n";
    cout << "The first player to form a valid three-letter word\n";
    cout << "horizontally, vertically, or diagonally wins.\n";
    cout << "The game is a draw if the board is filled\n";
    cout << "without a valid word being formed.\n";

    cout << "\nAdditional Details:\n";
    cout << "A file named dic.txt containing all valid\n";
    cout << "three-letter words will be provided.\n\n";

    srand(static_cast<unsigned int>(time(0)));

    WordTTT_UI* ui = new WordTTT_UI();
    WordTTT_Board* board = new WordTTT_Board();

    cout << "Choose Player-one (1. Human, 2. Computer): ";
    int t1;
    cin >> t1;

    cout << "Choose Player-Two (1. Human, 2. Computer): ";
    int t2;
    cin >> t2;

    Player<char>* players[2];

    PlayerType type1 = (t1 == 2 ? PlayerType::COMPUTER : PlayerType::HUMAN);
    PlayerType type2 = (t2 == 2 ? PlayerType::COMPUTER : PlayerType::HUMAN);

    string n1 = "Player-one";
    string n2 = "Player-Two";

    players[0] = new Player<char>(n1, '?', type1);
    players[1] = new Player<char>(n2, '?', type2);

    players[0]->set_board_ptr(board);
    players[1]->set_board_ptr(board);

    GameManager<char> gm(board, players, ui);
    gm.run();

    delete players[0];
    delete players[1];
    delete board;
    delete ui;

    cout << "=== Word Tic-Tac-Toe Finished ===\n\n";
}
void displayMenu()
{
    cout << "===========================================\n";
    cout << "1.  Play Numerical Tic-Tac-Toe \n";
    cout << "2.  Play Inverse Tic-Tac-Toe \n";
    cout << "3.  Play Pyramid Tic-Tac-Toe \n";
    cout << "4.  PLay SUS Tic-Tac-Toe \n";
    cout << "5.  PLay 4x4 Tic-Tac-Toe \n";
    cout << "6.  Play Infinity Tic-Tac-Toe \n";
    cout << "7.  Play 5x5 Tic-Tac-Toe \n";
    cout << "8.  Play Diamond Tic-Tac-Toe \n";
    cout << "9.  Play Connect Four Tic-Tac-Toe  \n";
    cout << "10. Play Obstacles Tic-Tac-Toe  \n";
    cout << "11. Play Word Tic-Tac-Toe  \n";
    cout << "12. Exit Program\n";
    cout << "===========================================\n";
    cout << "Enter your choice (1-12): ";

}

int main()
{
    int choice;

    // Seed random number generator for the entire program
    srand(static_cast<unsigned int>(time(0)));

    cout << "        Welcome to FCAI Board Games\n";

    do
    {
        displayMenu();
        cin >> choice;

        // Clear input buffer
        cin.clear();
        cin.ignore(10000, '\n');

        switch (choice)
        {
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
            playConnectFour();
            break;
        case 10:
            ObstacleTicTacToe();
            break;
        case 11:
            playWordTicTacToe();
            break;
        case 12:
            cout << "\nThank you for playing FCAI Board Games!\n";
            cout << "Goodbye!\n";
            break;
        default:
            cout << "Invalid choice! Please enter (1-12).\n\n";
        }

    } while (choice != 12);
    return 0;
}