#include "WordTTT_Classes.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include "../../OOP/OOP-Assignment3-master/ConsoleApplication1/BoardGame_Classes.h"
using namespace std;

// ---------------- Dictionary Loader ----------------
void WordTTT_Board::load_dictionary(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "ERROR: Could not open dictionary file: " << filename << endl;
        return;
    }

    string w;
    while (file >> w) {
        if (w.size() == 3) {
            transform(w.begin(), w.end(), w.begin(), ::toupper);
            dictionary.push_back(w);
        }
    }
    file.close();
}

// ---------------- Constructor ----------------
WordTTT_Board::WordTTT_Board()
    : Board<char>(3, 3)
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = '.';

    n_moves = 0;
    load_dictionary("dic.txt");
}

// ---------------- Game Logic ----------------
bool WordTTT_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char sym = move->get_symbol();

    if (x < 0 || x >= 3 || y < 0 || y >= 3) {
        cout << "Invalid position!\n";
        return false;
    }
    if (board[x][y] != '.') {
        cout << "Cell already taken.\n";
        return false;
    }

    board[x][y] = sym;
    n_moves++;
    return true;
}

bool WordTTT_Board::is_valid_word(const string& w) const {
    return find(dictionary.begin(), dictionary.end(), w) != dictionary.end();
}

bool WordTTT_Board::check_row(int r) const {
    string w;
    for (int j = 0; j < 3; j++) w += board[r][j];
    return is_valid_word(w);
}

bool WordTTT_Board::check_col(int c) const {
    string w;
    for (int i = 0; i < 3; i++) w += board[i][c];
    return is_valid_word(w);
}

bool WordTTT_Board::check_diagonals() const {
    string d1 = { board[0][0], board[1][1], board[2][2] };
    string d2 = { board[0][2], board[1][1], board[2][0] };
    return is_valid_word(d1) || is_valid_word(d2);
}

bool WordTTT_Board::is_win(Player<char>* p) {
    for (int i = 0; i < 3; i++)
        if (check_row(i) || check_col(i))
            return true;

    return check_diagonals();
}

bool WordTTT_Board::is_lose(Player<char>* p) {
    return is_win(p);
}

bool WordTTT_Board::is_draw(Player<char>* p) {
    return (n_moves == 9 && !is_win(p));
}

bool WordTTT_Board::game_is_over(Player<char>* p) {
    return is_win(p) || is_draw(p);
}

// ---------------- UI ----------------
WordTTT_UI::WordTTT_UI() : UI<char>("Word Tic-Tac-Toe", 2) {}

Player<char>* WordTTT_UI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}

Move<char>* WordTTT_UI::get_move(Player<char>* p) {
    Board<char>* board = p->get_board_ptr();
    auto matrix = board->get_board_matrix();

    if (p->get_type() == PlayerType::COMPUTER) {
        vector<pair<int, int>> empty;

        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (matrix[i][j] == '.')
                    empty.push_back({ i,j });

        int idx = rand() % empty.size();

        char random_letter = 'A' + (rand() % 26);

        cout << p->get_name() << " plays at ("
            << empty[idx].first << ", " << empty[idx].second
            << ") letter: " << random_letter << endl;

        return new Move<char>(empty[idx].first, empty[idx].second, random_letter);
    }

    int r, c;
    char letter;
    cout << p->get_name() << " enter (row col letter): ";
    cin >> r >> c >> letter;

    letter = toupper(letter);
    return new Move<char>(r, c, letter);
}
