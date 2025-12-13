#include "Four-in-a-rowTicTacToe.h"
#include "BoardGame_Classes.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std; 

Connect_Four_Board::Connect_Four_Board() : Board(6, 7)
{
    // Initialize empty board
    for (auto& row : board)
        for (auto& cell : row)
            cell = ' ';

}

bool Connect_Four_Board::check_Four(char mark)
{
    
    int ROWS = 6;
    int COLS = 7;

    // 1) Horizontal check
    for (int r = 0; r < ROWS; r++)
    {
        for (int c = 0; c <= COLS - 4; c++)
        {
            if (board[r][c] == mark &&
                board[r][c + 1] == mark &&
                board[r][c + 2] == mark &&
                board[r][c + 3] == mark)
                return true;
        }
    }

    // 2) Vertical check 
    for (int c = 0; c < COLS; c++)
    {
        for (int r = 0; r <= ROWS - 4; r++)
        {
            if (board[r][c] == mark &&
                board[r + 1][c] == mark &&
                board[r + 2][c] == mark &&
                board[r + 3][c] == mark)
                return true;
        }
    }

    // 3) Diagonal to right 
    for (int r = 0; r <= ROWS - 4; r++)
    {
        for (int c = 0; c <= COLS - 4; c++)
        {
            if (board[r][c] == mark &&
                board[r + 1][c + 1] == mark &&
                board[r + 2][c + 2] == mark &&
                board[r + 3][c + 3] == mark)
                return true;
        }
    }

    // 4) Diagonal to left 
    for (int r = 3; r < ROWS; r++)
    {
        for (int c = 0; c <= COLS - 4; c++)
        {
            if (board[r][c] == mark &&
                board[r - 1][c + 1] == mark &&
                board[r - 2][c + 2] == mark &&
                board[r - 3][c + 3] == mark)
                return true;
        }
    }
    return false;
}

bool Connect_Four_Board::update_board(Move<char>* move)
{
    int ROWS = 6; 
    int COLS = 7; 
    
    int c = move->get_x() ;
    char symbol = move->get_symbol();

    if (c < 0 || c >= COLS) 
    {
        cout << "Invalid column! Column must be 0-6.\n";
        return false;
    }

    int r = -1; 
    for (int row = ROWS - 1 ; row >= 0; --row) 
    {
        if (board[row][c] == ' ')
        {
            r = row; 
            break;
        }
    }

    if (r == -1)
    {
        cout << "Column " << c << " is fully occupied!\n";
        return false;
    }

    board[r][c] = symbol;
    n_moves++; 

    return true;
}

bool Connect_Four_Board::is_win(Player<char>* player)
{
    return check_Four(player->get_symbol()); 
}

bool Connect_Four_Board::is_lose(Player<char>* player)
{
    char opponent_mark = (player->get_symbol() == 'X') ? 'O' : 'X'; 
    return check_Four(opponent_mark); 
}

bool Connect_Four_Board::is_draw(Player<char>* player)
{
    return (n_moves == rows * columns && !is_win(player) && !is_lose(player));
}

bool Connect_Four_Board::game_is_over(Player<char>* player)
{
    return is_win(player) || is_lose(player) || is_draw(player); 
}


vector<int> Connect_Four_Board::get_available_position(bool is_player1)
{
    vector<int> is_available;
    for (int c = 0; c < columns; c++)
    {
        if (board[0][c] == ' ')
            is_available.push_back(c); 
    }
    return is_available; 
}

int Connect_Four_Board::Connnect_Four_check_status()
{
    if (check_Four('X'))       
        return 2;
    if (check_Four('O'))       
        return -2;
    if (n_moves == rows * columns)  
        return 0;
    return 1; 
}


int Connect_Four_Board::evaluate_board(char ai_symbol, char human_symbol)
{
    int score = 0;
    int ROWS = 6, COLS = 7;

    // 1️⃣ Give preference to the center column
    int centerCol = COLS / 2;
    for (int r = 0; r < ROWS; r++)
        if (board[r][centerCol] == ai_symbol)
            score += 6;  // reward AI for occupying the center

    // Lambda function to evaluate a line of 4 cells
    auto evaluate_line = [&](char a, char b, char c, char d) -> int {
        int ai_count = 0, human_count = 0;
        char cells[4] = { a, b, c, d };
        for (int i = 0; i < 4; i++) {
            if (cells[i] == ai_symbol) ai_count++;      // count AI pieces
            else if (cells[i] == human_symbol) human_count++; // count opponent pieces
        }

        // Score AI opportunities
        if (ai_count > 0 && human_count == 0) { // AI can potentially win here
            if (ai_count == 4) return 10000;  // immediate win
            if (ai_count == 3) return 500;    // strong threat
            if (ai_count == 2) return 50;     // good chance
        }

        // Score opponent threats
        if (human_count > 0 && ai_count == 0) { // block opponent
            if (human_count == 4) return -10000; // prevent immediate loss
            if (human_count == 3) return -800;   // block strong threat
            if (human_count == 2) return -50;    // block small chance
        }

        return 0; // neutral line
        };

    for (int r = 0; r < ROWS; r++)       // Horizontal
        for (int c = 0; c <= COLS - 4; c++)
            score += evaluate_line(board[r][c], board[r][c + 1], board[r][c + 2], board[r][c + 3]);

    for (int c = 0; c < COLS; c++)       // Vertical
        for (int r = 0; r <= ROWS - 4; r++)
            score += evaluate_line(board[r][c], board[r + 1][c], board[r + 2][c], board[r + 3][c]);

    for (int r = 3; r < ROWS; r++)       // Diagonal 
        for (int c = 0; c <= COLS - 4; c++)
            score += evaluate_line(board[r][c], board[r - 1][c + 1], board[r - 2][c + 2], board[r - 3][c + 3]);

    for (int r = 0; r <= ROWS - 4; r++)    // Diagonal 
                for (int c = 0; c <= COLS-4; c++)
        score += evaluate_line(board[r][c], board[r + 1][c + 1], board[r + 2][c + 2], board[r + 3][c + 3]);

    return score;
}




// Minimax with alpha-beta pruning
int Connect_Four_Board::minimax4(int& best_col, bool isMaximizing, int depth,int alpha = -10000, int beta = 10000,int original_depth = -1)
{
    char ai_symbol = 'X';
    char human_symbol = 'O';

    if (original_depth == -1) original_depth = depth; 

    int status = Connnect_Four_check_status();
    if (status != 1 || depth == 0)
    {
        return evaluate_board(ai_symbol, human_symbol);
    }

    vector<int> moves = get_available_position(isMaximizing);

    if (isMaximizing)
    {
        int maxEval = -10000;
        for (int col : moves)
        {
            int row = -1;
            for (int r = rows - 1; r >= 0; r--)
                if (board[r][col] == ' ') { row = r; break; }

            if (row == -1) continue;

            board[row][col] = ai_symbol;
            n_moves++;

            int eval = minimax4(best_col, false, depth - 1, alpha, beta, original_depth);

            board[row][col] = ' ';
            n_moves--;

            if (eval > maxEval)
            {
                maxEval = eval;
                if (depth == original_depth)
                    best_col = col;
            }

            alpha = max(alpha, eval);
            if (beta <= alpha) break; // pruning
        }
        return maxEval;
    }
    else
    {
        int minEval = 10000;
        for (int col : moves)
        {
            int row = -1;
            for (int r = rows - 1; r >= 0; r--)
                if (board[r][col] == ' ') { row = r; break; }

            board[row][col] = human_symbol;
            n_moves++;

            int eval = minimax4(best_col, true, depth - 1, alpha, beta, original_depth);

            board[row][col] = ' ';
            n_moves--;

            minEval = min(minEval, eval);
            beta = min(beta, eval);
            if (beta <= alpha) break; // pruning
        }
        return minEval;
    }
}



Connect_Four_UI::Connect_Four_UI() : UI<char>("Welcome to Connect Four Game!", 3) {}

void Connect_Four_UI::display_board_matrix(const vector<vector<char>>& matrix) const
{
    if (matrix.empty() || matrix[0].empty()) return;

    int rows = matrix.size();
    int cols = matrix[0].size();
    int cell_width = 3;  

    cout << "\n   ";  
    for (int j = 0; j < cols; ++j) {
        if (j > 0) cout << " ";
        cout << setw(cell_width + 1) << j;
    }
    cout << "\n";
    cout << "   " << string((cell_width + 2) * cols, '-') << "\n";

    for (int i = 0; i < rows; ++i) {
        cout << setw(2) << i << " |";
        for (int j = 0; j < cols; ++j)
            cout << setw(cell_width) << matrix[i][j] << " |";
        cout << "\n   " << string((cell_width + 2) * cols, '-') << "\n";
    }
    cout << endl;
}

Player<char>* Connect_Four_UI::create_player(string& name, char symbol, PlayerType type)
{
    return new Player<char>(name, symbol, type);
}

Move<char>* Connect_Four_UI::get_move(Player<char>* player)
{
    char player_symbol = player->get_symbol();
    int y = 0;  
    int best_col = -1;

    // AI MOVE
    if (player->get_type() == PlayerType::COMPUTER)
    {
        Connect_Four_Board* board = dynamic_cast<Connect_Four_Board*>(player->get_board_ptr());

        string ai_name = player->get_name();
        cout << "\n" << ai_name << " (Ai) " << " is thinking..." << endl;

        Connect_Four_AI_Player* ai_player = new Connect_Four_AI_Player(player_symbol, board);
        ai_player->get_best_move4(best_col);
        cout << "\n" << ai_name << " (Ai) his symbol is: " << player_symbol
            << "\nchooses column " << best_col << endl;

        delete ai_player;
        return new Move<char>(best_col, y, player_symbol);
    }

    // HUMAN MOVE
    else if (player->get_type() == PlayerType::HUMAN)
    {
        int col;
        while (true)
        {
            cout << "\n" << player->get_name()
                << " (Your symbol is " << player_symbol << ") choose a column (0-6): ";

            if (cin >> col && col >= 0 && col <= 6)
                break;
            else
            {
                cout << "Invalid input! Please enter a number between 0 and 6.\n";
                cin.clear();
                cin.ignore(10000, '\n');
            }
        }
        return new Move<char>(col, y, player_symbol);
    }
}

Player<char>** Connect_Four_UI::setup_players()
{
    Player<char>** players = new Player<char>*[2];
    vector<string> type_options = { "Human", "Ai" };

    // 1. Player 1

    // Name
    string name1 = get_player_name("Player 1");

    // Type
    PlayerType type1 = get_player_type_choice("Player 1", type_options);

    // Symbol 
    cout << "\n" << name1 << ", choose your symbol:\n"
        << "1) X\n"
        << "2) O\n";

    int symbol_choice;
    while (true)
    {
        cout << "Enter choice (1 or 2): ";
        if (cin >> symbol_choice && (symbol_choice == 1 || symbol_choice == 2))
        {
            cin.ignore(10000, '\n');
            break;
        }
        cout << "Invalid input! Please enter 1 or 2.\n";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    char symbol1 = (symbol_choice == 1 ? 'X' : 'O');
    char symbol2 = (symbol1 == 'X' ? 'O' : 'X');

    players[0] = create_player(name1, symbol1, type1);

    // 2. Player 2

    // Name 
    string name2;
    name2 = get_player_name("Player 2 (uses " + string(1, symbol2) + ")");

    // Type
    PlayerType type2 = get_player_type_choice("Player 2", type_options);

    players[1] = create_player(name2, symbol2, type2);

    return players;
}

Connect_Four_AI_Player::Connect_Four_AI_Player(char symbol, Connect_Four_Board* b) : Player<char>("AI_Player", symbol, PlayerType::COMPUTER)
{
    board = b;
}

void Connect_Four_AI_Player::get_best_move4(int& best_col)
{
    int MAX_DEPTH = 9; 
    int depth = MAX_DEPTH;
    board->minimax4(best_col, true, depth);

    vector<int> moves = board->get_available_position(true);
    if (find(moves.begin(), moves.end(), best_col) == moves.end()) {
        best_col = moves[0];
    }
}

