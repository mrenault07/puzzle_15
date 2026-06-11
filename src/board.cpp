#include <iostream>
#include <vector>
using namespace std;


class Tile {
    /*This class represents a single tile within the game board. Using a class here allows us 
    to overload the output operator to output a tile in the format we desire. 
    It also allows us to have well-named member functions that will increase the readability of code 
    related to a single tile.*/
private:
    int value;

public:
    Tile(int n){
        value = n;
    };

    bool isEmpty() const { // const = l'objet (value) ne sera pas modifié
        if (value == 0) return true;
        return false;
    }

    int getNum() const{
        return value;
    }
};

std::ostream& operator<<(std::ostream& out, const Tile& value)
{
    if (value.getNum() > 9) // if two digit number
        out << " " << value.getNum() << " ";
    else if (value.getNum() > 0) // if one digit number
        out << "  " << value.getNum() << " ";
    else if (value.getNum() == 0) // if empty spot
        out << "    ";
    return out;
}

// Increase amount of new lines if your board isn't
// at the very bottom of the console
constexpr int g_consoleLines{ 25 };
//constexpr  = la valeur de la fonction est constante

class Board 
{
private:
    int const n = 16;
    vector<Tile> board = {};
    public:
    
    Board()
    {
        for (int i = 0; i < n; i++){
            board.push_back(Tile(i));
        }
    }

    Tile getTile(int j){
        return board[j];
    }
};



std::ostream& operator<<(std::ostream& out, Board& board)
{
    for (int i = 0; i < g_consoleLines; i++){
        out << '\n';
    }

    for (int i = 1 ; i < 16; i++){
        if (i%4 == 0){
            if (board.getTile(i).getNum() <= 9)
                out << "  "<< board.getTile(i).getNum() << ' ';
            else if (board.getTile(i).getNum() > 9)
                out << ' ' << board.getTile(i).getNum() << ' ';
            else if (board.getTile(i).getNum() == 0)
                out << "    ";
            out << '\n';
        }
        else{
            if (board.getTile(i).getNum() <= 9)
                out << "  " << board.getTile(i).getNum() << ' ';
            else if (board.getTile(i).getNum() > 9)
                out << ' ' << board.getTile(i).getNum() << ' ';
            else if (board.getTile(i).getNum() == 0)
                out << "    ";
        }
    }
    return out;
}

int main()
{
    Board board{};
    std::cout << board;

    return 0;
}
