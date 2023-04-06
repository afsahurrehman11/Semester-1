#include <iostream>
#include<windows.h>
#include<fstream>


#define BLACK 0
#define BROWN 6
#define WHITE 15
#define GREEN 2
#define RED 4
#define LBLUE 9

using namespace std;

struct position
{
    int ri, ci;
};
enum { red, blue };


void getRowColbyLeftClick(int& rpos, int& cpos)
{
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD Events;
    INPUT_RECORD InputRecord;
    SetConsoleMode(hInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
    do
    {
        ReadConsoleInput(hInput, &InputRecord, 1, &Events);
        if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
        {
            cpos = InputRecord.Event.MouseEvent.dwMousePosition.X;
            rpos = InputRecord.Event.MouseEvent.dwMousePosition.Y;
            break;
        }
    } while (true);
}
void gotoRowCol(int rpos, int cpos)
{
    COORD scrn;
    HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
    scrn.X = cpos;
    scrn.Y = rpos;
    SetConsoleCursorPosition(hOuput, scrn);
}
void SetClr(int tcl, int bcl)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (tcl + (bcl * 16)));
}



void init(char**& B, string Pname[2], int& turn, int& dim)
{
    ifstream rdr("Text.txt");
    rdr >> dim;

    B = new char* [dim];
    for (int i = 0; i < dim; i++)
    {
        B[i] = new char[dim];
    }

    for (int r = 0; r < dim; r++)
    {
        for (int c = 0; c < dim; c++)
        {

            rdr >> B[r][c];
        }
    }


    cout << "ENTER 1st PLAYER NAME : \n";
    cin >> Pname[0];

    cout << "ENTER 2nd PLAYER NAME : \n";
    cin >> Pname[1];


    srand(time(0));
    int x = rand() % 2;

    if (x == 0)
        turn = red;
    else
        turn == blue;



}


void turn_msg(string Pname[], int turn)
{
    cout << Pname[turn] << "'s turn \n";
}




// old one 
void square(int n, char sym = -37)
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (i == 1 || i == n || j == 1 || j == n ||
                i == (n / 2) + 1 || i == (n / 4) + 1 || i == (((n * 3) / 4)) + 1 ||
                j == (n / 2) + 1 || j == (n / 4) + 1 || j == (((n * 3) / 4)) + 1 ||
                j == i || j == (n + 1 - i))
            {
                gotoRowCol(i, j);
                cout << sym;
            }
            else
                cout << " ";
        }
    }

}










void print_alpha(char** B, int dim)
{
    int x = dim / 2;
    int y = dim / 2;


    for (int r = 0; r < 5; r++)
    {
        for (int c = 0; c < 5; c++, "   ")
        {

            gotoRowCol(x, y);

            cout << B[r][c];
            y += dim - 1;
        }

        y = dim / 2;
        x += dim - 1;

    }
    cout << endl;
}
void left_to_right(int row, int col, int dim, char sym)
{
    gotoRowCol(row, col);
    for (int x = 0; x < dim; x++)
    {
        cout << sym;
    }
    cout << endl;
    for (int x = 0; x < dim - 2; x++)
    {
        gotoRowCol(row + 1 + x, col);
        cout << sym;
        for (int y = 0; y < dim - 2; y++)
        {
            if (x == y)
                cout << sym;
            else
                cout << " ";
        }
        cout << sym << endl;
    }
    gotoRowCol(row + dim, col);
    for (int x = 0; x < dim; x++)
    {
        cout << sym;
    }
}
void right_to_left(int row, int col, int dim, char sym)
{
    gotoRowCol(row, col);
    for (int x = 0; x < dim; x++)
    {
        cout << sym;
    }
    cout << endl;
    for (int x = 0; x < dim - 2; x++)
    {
        gotoRowCol(row + x + 1, col);
        cout << sym;
        for (int y = 0; y < dim - 2; y++)
        {
            cout << " ";
        }
        cout << sym;
        gotoRowCol(row + x + 1, col + dim - 2 - x);
        cout << sym << endl;
    }
    gotoRowCol(row + dim - 1, col);

    for (int x = 0; x < dim; x++)
    {
        cout << sym;
    }

}
void print_borad(int dim, char sym)
{
    int r = 0;
    for (int ri = 0; ri < 4; ri++)
    {
        int c = 0;
        for (int ci = 0; ci < 4; ci++)
        {

            if ((ri + ci) % 2 == 0)
            {
                left_to_right(ri * dim - r + (dim / 2), ci * dim - c + (dim / 2), dim, sym);
                c++;
            }
            else
            {
                right_to_left(ri * dim - r + (dim / 2), ci * dim - c + (dim / 2), dim, sym);
                c++;
            }
        }
    }
}





bool is_red_piece(char sym)
{
    cout << "working2" << sym << endl;
    if (sym == 'r')
        return true;
    else
        return false;
}

bool is_blue_piece(char sym)
{
    if (sym == 'b')
        return true;
    else
        return false;
}

bool isMyPiece(char sym, int turn)
{
    if (turn == 1)
    {
        return is_red_piece(sym);
    }

    if (turn == 0)
    {
        return is_blue_piece(sym);
    }
}





bool isvaild_selction(char** B, position Sc, int turn, int dim)
{
    if (Sc.ci < 0 || Sc.ci >= dim)
    {
        return false;
    }

    if (Sc.ri < 0 || Sc.ri >= dim)
    {
        return false;
    }
    return isMyPiece(B[Sc.ri][Sc.ci], turn);
}



bool isvaild_drop(char** B, position sc, position dc, int turn, int dim)
{

    if (B[sc.ri][dc.ci] != '-')
    {

        return false;
    }

    if ((dc.ri == sc.ri) && (dc.ci == sc.ci + 1 || dc.ci == sc.ci - 1))
    {
        B[dc.ri][dc.ci] = B[sc.ri][sc.ci];
        B[sc.ri][sc.ci] = '-';

        return true;
    }


    if ((dc.ci == sc.ci) && (dc.ri == sc.ri + 1 || dc.ri == sc.ri - 1))
    {
        B[dc.ri][dc.ci] = B[sc.ri][sc.ci];
        B[sc.ri][sc.ci] = '-';
        return true;
    }

    // hor 2  


    if ((dc.ri == sc.ri) && (dc.ci == sc.ci + 2) && (B[sc.ri][sc.ci + 1] == '-'))
    {
        B[dc.ri][dc.ci] = B[sc.ri][sc.ci];
        B[sc.ri][sc.ci] = '-';
        B[sc.ri][sc.ci + 1] = '-';

    }

    if ((dc.ri == sc.ri) && dc.ci == sc.ci - 2 && B[sc.ri][sc.ci - 1] == '-')
    {
        B[dc.ri][dc.ci] = B[sc.ri][sc.ci];
        B[sc.ri][sc.ci] = '-';
        B[sc.ri][sc.ci - 1] = '-';
    }

    if ((dc.ci == sc.ci) && (dc.ri == sc.ri + 2) && (B[sc.ci][sc.ri + 1] == '-'))
    {
        B[dc.ri][dc.ci] = B[sc.ri][sc.ci];
        B[sc.ri][sc.ci] = '-';
        B[sc.ri + 1][sc.ci] = '-';

    }

    if ((dc.ci == sc.ci) && (dc.ri == sc.ri - 2) && (B[sc.ci][sc.ri - 1] == '-'))
    {
        B[dc.ri][dc.ci] = B[sc.ri][sc.ci];
        B[sc.ri][sc.ci] = '-';
        B[sc.ri - 1][sc.ci] = '-';

    }
    // daigonal condition
    if ((sc.ci + sc.ri) % 2 == 0)
    {
        if (sc.ri < dc.ri)
        {
            if (dc.ri = sc.ri + 1)
            {
                B[dc.ri][dc.ci] = B[sc.ri][sc.ci];
                B[sc.ri][sc.ci] = '-';
            }
            if (dc.ri = sc.ri + 2)
            {
                B[dc.ri][dc.ci] = B[sc.ri][sc.ci];
                B[sc.ri][sc.ci] = '-';
                B[sc.ri + 1][sc.ci + 1] = '-';
            }
        }
        if (sc.ri > dc.ri)
        {
            if (dc.ri = sc.ri - 1)
            {
                B[dc.ri][dc.ci] = B[sc.ri][sc.ci];
                B[sc.ri][sc.ci] = '-';
            }
            if (dc.ri = sc.ri - 2)
            {
                B[dc.ri][dc.ci] = B[sc.ri][sc.ci];
                B[sc.ri][sc.ci] = '-';
                B[sc.ri - 1][sc.ci - 1] = '-';
            }
        }
    }
    return true;
}



void selesct_pos(char** B, position& Sc, int turn, int dim)
{
    cout << endl;
    cout << "ENTER SELECTION COORDINATES (A1 : E5)\n ";
    cout << "ENTER COLUMN : ";
    char C;
    cin >> C;
    C = toupper(C);
    Sc.ci = C - 'A';
    cout << "ENTER ROW : ";
    int row;
    cin >> row;
    Sc.ri = row - 1;
}

void select_des(char** B, position& Dc, int turn, int dim)
{
    cout << "ENTER DROPING COORDINATES (A1 : E5)\n ";
    cout << "ENTER COLUMN : ";
    char C;
    cin >> C;
    C = toupper(C);
    Dc.ci = C - 'A';
    cout << "ENTER ROW : ";
    int row;
    cin >> row;
    Dc.ri = row - 1;
}


void change_turn(int& turn)
{
    if (turn == red)
        turn = blue;
    else
        turn = red;
}


int main()
{
    int dim = 0, turn = 0;
    char** B = {};
    position Sc, Dc;
    Sc.ri = 0, Sc.ci = 0;
    Dc.ri = 0, Dc.ci = 0;
    string Pname[2] = {};
    init(B, Pname, turn, dim);
    system("cls");


    print_borad(10, -37);
    print_alpha(B, 10);


    cout << "\n\n\n\n\n\n";
    turn_msg(Pname, turn);

    do
    {
        do
        {
            selesct_pos(B, Sc, turn, dim);
        } while (!isvaild_selction(B, Sc, turn, dim));
    } while (!isvaild_drop(B, Sc, Dc, turn, dim));

    change_turn(turn);



}
