#include <iostream>
#include<windows.h>
#include<fstream>
using namespace std;

struct position
{
	int ri, ci;
};

enum {red , blue};


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
void SetClr(int clr)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), clr);
}

void init(char** B, string Pname[2] ,int &turn,int& dim )
{
	ifstream rdr("Text.txt");
	rdr >> dim;
	cout << "inner dim : " << dim << endl;
	B = new char* [dim];
	for (int i = 0; i < dim; i++)
	{
		B [i] = new char [dim];
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
	{
		turn = red;

	}
	else
		turn = blue; 

}





void turn_msg(string Pname[], int turn)
{
	cout << Pname[turn] << "'s turn \n";
}











void square(int n, char sym = -37)
{
	for (int  i = 1 ; i <= n ; i++)
	{
		for (int j = 1 ; j <= n ; j++)
		{
			if (i == 1 || i == n || j == 1 || j == n ||
				i == n / 2 || i == n / 4 || i == ((n * 3) / 4) ||
				j == n / 2 || j == n / 4 || j == ((n *3 )/ 4) ||
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



bool is_red_piece(char sym)
{
	cout << "working2"<< sym << endl;
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
		cout << "Working" << endl;
		return is_red_piece(sym);
	}

	if (turn ==0)
	{
		cout << "WorkingLLL" << endl;
		return is_blue_piece(sym);
	}
}

bool isvaild_selction(char** B, position Sc, int turn, int dim)
{
	cout << Sc.ci << "       " << Sc.ri << endl;
	cout << "Dinensuib" << dim << endl;

	cout << "condition1" << ( Sc.ci >= dim )<< endl;
	cout << "condition2" << ( Sc.ri >= dim) << endl;
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

void selesct_pos(char** B,position& Sc, int turn, int dim)
{
	cout << "ENTER COORDINATES (A1 : E5)\n  ";
	cout << "ENTER COLUMN :  ";
	char C;
	cin >> C;
	C = toupper(C);
	Sc.ci = C - 'A';
	cout << "ENTER ROW :  ";
	int row;
	cin >> row;
	Sc.ri = row - 1;
}




int main()
{
	int dim=0,turn=0;
	char** B = {};
	position Sc, Dc;
	Sc.ri = 0, Sc.ci = 0;
	Dc.ri = 0, Dc.ci = 0;
	string Pname[2] = {};
	init(B, Pname, turn, dim);
	system("cls");
	cout << dim << "bdbsjkcxcxj\n\n\\n\n\n\n\n\n\n\n\n\n\n\n\n";

	square(30);
	turn_msg(Pname, turn);
	do 
	{
		selesct_pos(B, Sc, turn, dim);

		cout << isvaild_selction(B, Sc, turn, dim) << endl;


	} while (!isvaild_selction(B, Sc, turn, dim));

		


}




