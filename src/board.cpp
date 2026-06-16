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
    char userInput;
public:
    enum Type { up, down, right, left };
    Type m_type;
    Direction(Type type) : m_type(type) {}

    Type getType() const {
        return m_type;
    }

    void getUserInput(string& command){
        cout << "\n" << "Enter a command : ";
        cin >> userInput;

        switch (userInput){
            case 'w': 
                m_type = up;
                break;
            case 'a':
                m_type = left;
                break;
            case 's':
                m_type = down;
                break;
            case 'd':
                m_type = right;
                break;
            case 'q':
                cout << "\n\nBye !\n\n"; //TODO: End code
                break;
            default:
                cout << "\nInvalid command";
        }
        cout << "\nDirection : " << command;
    };
};

class Point{
private:
    int x_axis, y_axis;
public:
    Point(int x, int y){
        x_axis = x;
        y_axis = y;
    };

    Point getAdjacentPoint(Direction dir){
        switch (dir.getType())
        {
        case  Direction::up:
            return Point{x_axis, y_axis - 1};
        case  Direction::down:
            return Point{x_axis, y_axis + 1};
        case  Direction::left:
            return Point{x_axis - 1, y_axis};
        case  Direction::right:
            return Point{x_axis + 1, y_axis};
        default:
            return Point{x_axis, y_axis};
        }
    };
    friend bool operator==(const Point &pt1, const Point &pt2);
    friend bool operator!=(const Point &pt1, const Point &pt2);

};

// Overload operator ==. On redéfinit l'opérateur == 
bool operator== (const Point &pt1, const Point &pt2)
{
    return (pt1.x_axis == pt2.x_axis &&
            pt1.y_axis == pt2.y_axis);
}
bool operator!= (const Point &pt1, const Point &pt2)
{
    return (pt1.x_axis != pt2.x_axis ||
            pt1.y_axis != pt2.y_axis);
}


int main()
{
    // Board board{};
    // std::cout << board;

    // string command = {}; 
    // Direction dir;

    // while (command != "quit"){
    //     dir.getUserInput(command);
    // };

    std::cout << std::boolalpha;
    std::cout << (Point{ 1, 1 }.getAdjacentPoint(Direction::up)    == Point{ 1, 0 }) << '\n';
    std::cout << (Point{ 1, 1 }.getAdjacentPoint(Direction::down)  == Point{ 1, 2 }) << '\n';
    std::cout << (Point{ 1, 1 }.getAdjacentPoint(Direction::left)  == Point{ 0, 1 }) << '\n';
    std::cout << (Point{ 1, 1 }.getAdjacentPoint(Direction::right) == Point{ 2, 1 }) << '\n';
    std::cout << (Point{ 1, 1 } != Point{ 2, 1 }) << '\n';
    std::cout << (Point{ 1, 1 } != Point{ 1, 2 }) << '\n';
    std::cout << !(Point{ 1, 1 } != Point{ 1, 1 }) << '\n';
    return 0;
}
