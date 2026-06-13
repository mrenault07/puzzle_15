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
    Tile() : value(0) {}; //Constructeur par défaut, permet de créer un Tile vide
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
    Tile board[4][4];

public:
    Board()
    {
        // Create a fixed size array
        int compteur = 0;
        for (int i = 0; i < 4; i++){
            for (int j = 0; j < 4; j++){
                board[i][j] = Tile{compteur};
                compteur++;
            }
        }
    };

    Tile getTile(int k, int l){
        return board[k][l];
    };
    
};



std::ostream& operator<<(std::ostream& out, Board& board)
{   
    //Put the board at the bottom of the console
    for (int i = 0; i < g_consoleLines; i++){
        out << '\n';
    }

    for (int i = 0 ; i < 4; i++){
        for (int j = 0 ; j < 4; j++){
            out << board.getTile(i, j);
            if (j%4 == 0){
                out << '\n';
            }
        }
    }
    return out;
}

class Direction{
/*
The user will be entering single-letter (char) commands on the keyboard to slide tiles in cardinal directions (e.g. 'w'=up, 'a'=left). 
Converting these char commands into a Direction object (representing a cardinal direction) will make our code more intuitive and prevent 
our code from being littered with char literals (Direction::left is more meaningful than 'a').
*/
private:
public:
    char userInput;

    void getUserInput(string& command){
        cout << "\n" << "Enter a command : ";
        cin >> userInput;

        switch (userInput){
            case 'w':
                command = "up";
                break;
            case 'a':
                command = "left";
                break;
            case 's':
                command = "down";
                break;
            case 'd':
                command = "right";
                break;
            case 'q':
                cout << "\n\nBye !\n\n";
                command = "quit";
                break;
            default:
                cout << "\nInvalid command";
        }
        cout << "\nDirection : " << command;
    };
};

int main()
{
    Board board{};
    std::cout << board;

    string command = {}; // pointer to value of command
    Direction dir;

    while (command != "quit"){
        dir.getUserInput(command);
    };

    return 0;
}
