/*#include "Four-in-a-rowTicTacToe.h"
#include <iostream>
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
    // نفترض أن move->get_x() هو رقم العمود (1-7) الذي اختاره اللاعب
    int col_number = move->get_x();
    char symbol = move->get_symbol();

    // تحويل رقم العمود إلى فهرس (0-6)
    int c = col_number - 1;

    // 1. التحقق من صحة العمود
    if (c < 0 || c >= COLS) // COLS = 7
    {
        cout << "Invalid column! Column must be 0-6.\n";
        return false;
    }


    int r = -1; 
    for (int row = ROWS - 1 ; row >= 0; --row) 
    {
        if (board[row][c] == ' ')
        {
            r = row; // وجدنا الصف الفارغ
            break;
        }
    }

    // 3. التحقق مما إذا كان العمود ممتلئًا (لم يتم العثور على صف)
    if (r == -1)
    {
        cout << "Column " << col_number << " is fully occupied!\n";
        return false;
    }

    // 4. وضع الرمز في الصف والعمود الصحيحين
    board[r][c] = symbol;

    // (يجب أن يتم زيادة عداد الحركات n_moves هنا)
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



bool Connect_Four_Board::is_position_available(int number, bool is_player1)
{
    int col = number ; 
    if (col < 0 || col >= columns) return false; 
    return board[0][col] == ' '; 
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
*/
