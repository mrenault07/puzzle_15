#include <iostream>
#include <vector>
#include <cstdlib>  // pour rand()
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

    static Direction getRandomDirection(){ // static = appartient à la classe, pas à l'objet. Donc pas besoin de créer un objet Direction
        return Direction{ static_cast<Type>(rand() % 4) };
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

    friend Direction operator-(const Direction &type1);
};
// Get opposite direction 
Direction operator-(const Direction &type1){
    switch (type1.getType())
    {
    case Direction::up: // En dehors de la classe, donc ne pas oublier Direction
        return Direction{Direction::down};
    case Direction::down:
        return Direction{Direction::up};
    case Direction::left:
        return Direction{Direction::right};
    case Direction::right:
        return Direction{Direction::left};
    default:
        return type1;
    }
}


class Point{
private:
public:
    int x_axis, y_axis;
    Point(int x, int y){
        x_axis = x;
        y_axis = y;
    };

    Point getAdjacentPoint(Direction dir){
        switch (dir.getType())
        {
        case  Direction::up:
            return Point{x_axis - 1, y_axis};
        case  Direction::down:
            return Point{x_axis + 1, y_axis};
        case  Direction::left:
            return Point{x_axis, y_axis - 1};
        case  Direction::right:
            return Point{x_axis, y_axis + 1};
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


// Increase amount of new lines if your board isn't
// at the very bottom of the console
constexpr int g_consoleLines{ 25 };
//constexpr  = la valeur de la fonction est constante

class Board 
{
private:
public:
    Tile board[4][4];
    Board()
    {
        // Create a fixed size array
        int compteur = 1;
        for (int i = 0; i < 4; i++){
            for (int j = 0; j < 4; j++){
                board[i][j] = Tile{compteur};
                compteur++;
            }
        }
        board[3][3]= Tile{0};
    };

    Tile getTile(int k, int l){
        return board[k][l];
    };

    Point getEmptyPoint(){
        for (int i = 0; i < 4; i++){
            for (int j = 0; j < 4; j++){
                if (getTile(i, j).getNum() == 0){
                    return Point(i,j);
                }
            }
        }
        return Point(-1, -1);
    };

    bool isTileValid(int x, int y){
        /* Checks if tile exists (not outside the board).*/
        if ((x < 0 || x > 3) || (y < 0 || y > 3)){
            cout << "\nInvalid Tile.\n";
            return false;
        }
        return true;
    }

    Point getOppositePoint(Point empty_point, Direction dir){
        /* If user ask right, gives the tile at the left of the empty tile. 
        Same for up and down.*/
        Direction new_tile_direction{-dir};
        Point new_tile = empty_point.getAdjacentPoint(new_tile_direction); // Get new tile coordinates
        int x_new_tile = new_tile.x_axis;
        int y_new_tile = new_tile.y_axis;
        return Point(x_new_tile, y_new_tile);
    };

    void moveTile(Direction dir){
        // Get empty tile
        Point empty_point = getEmptyPoint();
        cout << "\nx : " << empty_point.x_axis;
        cout << "\ny : " << empty_point.y_axis;

        // Find opposite tile from the direction
        Point opposite_point = getOppositePoint(empty_point, dir);

        cout << "\nx opposite: " << opposite_point.x_axis;
        cout << "\ny opposite: " << opposite_point.y_axis;
        // Check if it's a valid choice (not outside the board)
        bool valid = isTileValid(opposite_point.x_axis, opposite_point.y_axis);
        if (!valid){
            return;
        }
        // Swap the tiles
        std::swap(board[empty_point.x_axis][empty_point.y_axis], board[opposite_point.x_axis][opposite_point.y_axis]);
    };

    void randomize(){
        /* Randomize board. It has to be solvable so starts from 
        the empty tile and randomize direction to swap tiles, wether the random direction is valid or not.*/
        for (int i = 0; i < 1000; i++){
            moveTile(Direction::getRandomDirection());
        }
    }
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
        }
        out << '\n'; // Retour à la ligne après chaque ligne
    }
    return out;
}


int main()
{
    Board board{};
    std::cout << board;
    board.randomize();
    std::cout << board;

    // string command = {}; 
    // Direction dir;

    // while (command != "quit"){
    //     dir.getUserInput(command);
    // };

    // std::cout << std::boolalpha;
    // std::cout << (Point{ 1, 1 }.getAdjacentPoint(Direction::up)    == Point{ 1, 0 }) << '\n';
    // std::cout << (Point{ 1, 1 }.getAdjacentPoint(Direction::down)  == Point{ 1, 2 }) << '\n';
    // std::cout << (Point{ 1, 1 }.getAdjacentPoint(Direction::left)  == Point{ 0, 1 }) << '\n';
    // std::cout << (Point{ 1, 1 }.getAdjacentPoint(Direction::right) == Point{ 2, 1 }) << '\n';
    // std::cout << (Point{ 1, 1 } != Point{ 2, 1 }) << '\n';
    // std::cout << (Point{ 1, 1 } != Point{ 1, 2 }) << '\n';
    // std::cout << !(Point{ 1, 1 } != Point{ 1, 1 }) << '\n';
    return 0;
}
