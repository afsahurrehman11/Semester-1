#include <iostream>
#include <fstream>
#include <iomanip>
#include<math.h>
#include<Windows.h>
#include<conio.h>
using namespace std;
int const cols = 160;
int const rows = 70;
int const cap = 100;


char moves[20][9][9];
int moveCount = 0;

fstream MyFile;


struct capture
{
	char ofwhite[4][3]{};
	char ofblack[4][3]{};
};
void SetClr(int clr)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), clr);
}
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
void L2R(int r, int cs, int ce, char sym)
{
	for (int c = cs; c < ce; c++)
	{
		gotoRowCol(r, c);
		cout << sym;
	}
}
void U2B(int cl, int rs, int re, char sym)
{
	for (int c = rs; c < re; c++)
	{
		gotoRowCol(c, cl);
		cout << sym;
	}
}
enum color { White, Black };
struct position
{
	int ri;
	int ci;
};
void Init(int& Dim, char**& B, int& Turn, string Pname[], int ch)
{
	if (ch == 1)
	{
		ifstream rdr("Text.txt");
		rdr >> Dim;
		B = new char* [Dim];
		for (int i = 0; i < Dim; i++)
		{
			B[i] = new char[Dim];
		}

		for (int r = 0; r < Dim; r++)
		{
			for (int c = 0; c < Dim; c++)
			{
				rdr >> B[r][c];
			}
		}
	}
	if (ch == 2)
	{
		ifstream rdr("load.txt");
		rdr >> Dim;
		B = new char* [Dim];
		for (int i = 0; i < Dim; i++)
		{
			B[i] = new char[Dim];
		}

		for (int r = 0; r < Dim; r++)
		{
			for (int c = 0; c < Dim; c++)
			{
				rdr >> B[r][c];
			}
		}
	}

	cout << "Enter Names :" << endl;
	for (int i = 0; i < 2; i++)
	{
		cout << i + 1 << ". ";
		cin >> Pname[i];
	}

	Turn = rand() % 2;

}
void drawbox(int sr, int sc, int Dim)
{
	for (int r = 0; r < Dim; r++)
	{
		for (int c = 0; c < Dim; c++)
		{
			gotoRowCol(sr + r, sc + c);
			cout << char(177);
		}
	}
}
void drawboxHigh(int sr, int sc, int Dim, int color)
{
	sr = sr - Dim / 2;
	sc = sc - Dim / 2;
	SetClr(color);
	U2B(sc, sr, sr + Dim, 177);
	L2R(sr, sc, sc + Dim - 1, 177);
	U2B(sc + Dim - 1, sr, sr + Dim, 177);
	L2R(sr + Dim - 1, sc, sc + Dim, 177);
}
void drawpawn(int r, int c)
{
	for (int ln = 0; ln < 5 / 2; ln++)
	{
		gotoRowCol(ln + r - 2, c - ln);
		for (int sl = 0; sl < ln * 2 + 1; sl++)
			cout << char(-37);
	}
	for (int ln = 2, cl = 0; ln < 5 / 2 + 2; ln++, cl++)
	{
		gotoRowCol(ln + r - 2, c - cl);
		for (int sl = 0; sl < cl * 2 + 1; sl++)
			cout << char(-37);
	}
}
void draw_p_pawn(int r, int c)
{
	for (int ln = 0; ln < 5 / 2; ln++)
	{
		gotoRowCol(ln + r - 2, c - ln);
		for (int sl = 0; sl < ln * 2 + 1; sl++)
			cout << char(-37);
	}
	for (int ln = 2, cl = 0; ln < 5 / 2 + 2; ln++, cl++)
	{
		gotoRowCol(ln + r - 2, c - cl);
		for (int sl = 0; sl < cl * 2 + 1; sl++)
			cout << char(-37);
	}
	gotoRowCol(r - 3, c + 2);
	cout << "P";

}
void drawrook(int r, int c)
{
	gotoRowCol(r, c);
	cout << char(219);

	gotoRowCol(r - 1, c - 1);
	cout << char(200);
	gotoRowCol(r - 1, c + 1);
	cout << char(188);
	gotoRowCol(r + 1, c + 1);
	cout << char(205);
	gotoRowCol(r + 1, c);
	cout << char(205);
	gotoRowCol(r + 1, c - 1);
	cout << char(205);
}
void drawbishop(int r, int c)
{
	for (int ln = 0; ln <= 5 / 2; ln++)
	{
		gotoRowCol(ln + r - 2, c - ln);
		for (int sl = 0; sl < ln * 2 + 1; sl++)
			cout << char(-37);
	}
	for (int ln = 5 / 2 + 1, cl = 1; ln < 5; ln++, cl--)
	{
		gotoRowCol(ln + r - 2, c - cl);
		for (int sl = 0; sl < cl * 2 + 1; sl++)
			cout << char(-37);
	}

}
void drawking(int r, int c)
{
	gotoRowCol(r, c);
	cout << char(178);
	gotoRowCol(r - 1, c);
	cout << char(241);
}
void drawgolden(int r, int c)
{
	gotoRowCol(r, c);
	cout << char(219);
	gotoRowCol(r - 1, c);
	cout << char(118);
	gotoRowCol(r, c + 1);
	cout << char(191);
	gotoRowCol(r, c - 1);
	cout << char(218);
	gotoRowCol(r + 1, c - 1);
	cout << char(217);
	gotoRowCol(r + 1, c + 1);
	cout << char(192);
}
void drawsilver(int r, int c)
{
	gotoRowCol(r, c);
	cout << char(219);
	gotoRowCol(r - 1, c);
	cout << char(118);
	gotoRowCol(r, c + 1);
	cout << char(191);
	gotoRowCol(r, c - 1);
	cout << char(218);

}
void drawknight(int r, int c)
{
	gotoRowCol(r, c);
	cout << char(153);
	gotoRowCol(r - 1, c - 1);
	cout << char(218);
	gotoRowCol(r + 1, c + 1);
	cout << char(217);
}
void drawlance(int r, int c)
{
	for (int ln = 0; ln < 5 / 2; ln++)
	{
		gotoRowCol(ln + r - 2, c - ln);
		for (int sl = 0; sl < ln * 2 + 1; sl++)
			cout << char(-37);
	}
	for (int ln = 5 / 2; ln < 5; ln++)
	{
		{
			gotoRowCol(ln + r - 2, c - 1);
			if (ln == 5 / 2)
				for (int sl = 0; sl < (2 * ln) - 1; sl++)
					cout << char(-37);
		}
		{
			gotoRowCol(ln + r - 2, c - 1);
			if (ln == 5 / 2 + 1)
				for (int sl = 0; sl < (2 * ln) - ln; sl++)
					cout << char(-37);
		}
		{
			gotoRowCol(ln + r - 2, c - 3);
			if (ln == 5 - 1)
				for (int sl = 0; sl < (2 * ln) - 1; sl++)
					cout << char(-37);
		}

	}
}
void drawp_rook(int r, int c)
{
	gotoRowCol(r, c);
	cout << char(219);
	gotoRowCol(r - 1, c - 1);
	cout << char(200);
	gotoRowCol(r - 1, c + 1);
	cout << char(188);
	gotoRowCol(r + 1, c + 1);
	cout << char(205);
	gotoRowCol(r + 1, c);
	cout << char(205);
	gotoRowCol(r + 1, c - 1);
	cout << char(205);
	gotoRowCol(r - 3, c + 2);
	cout << "P";
}
void drawp_bishop(int r, int c)
{
	for (int ln = 0; ln <= 5 / 2; ln++)
	{
		gotoRowCol(ln + r - 2, c - ln);
		for (int sl = 0; sl < ln * 2 + 1; sl++)
			cout << char(-37);
	}
	for (int ln = 5 / 2 + 1, cl = 1; ln < 5; ln++, cl--)
	{
		gotoRowCol(ln + r - 2, c - cl);
		for (int sl = 0; sl < cl * 2 + 1; sl++)
			cout << char(-37);
	}

	gotoRowCol(r - 3, c + 2);
	cout << "P";
}
void drawp_silver(int r, int c)
{
	gotoRowCol(r, c);
	cout << char(219);
	gotoRowCol(r - 1, c);
	cout << char(118);
	gotoRowCol(r, c + 1);
	cout << char(191);
	gotoRowCol(r, c - 1);
	cout << char(218);
	gotoRowCol(r - 3, c + 2);
	cout << "P";
}
void drawp_night(int r, int c)
{
	gotoRowCol(r, c);
	cout << char(153);
	gotoRowCol(r - 1, c - 1);
	cout << char(218);
	gotoRowCol(r + 1, c + 1);
	cout << char(217);
	gotoRowCol(r - 3, c + 2);
	cout << "p";
}
void drawp_lance(int r, int c)
{
	for (int ln = 0; ln < 5 / 2; ln++)
	{
		gotoRowCol(ln + r - 2, c - ln);
		for (int sl = 0; sl < ln * 2 + 1; sl++)
			cout << char(-37);
	}
	for (int ln = 5 / 2; ln < 5; ln++)
	{
		{
			gotoRowCol(ln + r - 2, c - 1);
			if (ln == 5 / 2)
				for (int sl = 0; sl < (2 * ln) - 1; sl++)
					cout << char(-37);
		}
		{
			gotoRowCol(ln + r - 2, c - 1);
			if (ln == 5 / 2 + 1)
				for (int sl = 0; sl < (2 * ln) - ln; sl++)
					cout << char(-37);
		}
		{
			gotoRowCol(ln + r - 2, c - 3);
			if (ln == 5 - 1)
				for (int sl = 0; sl < (2 * ln) - 1; sl++)
					cout << char(-37);
		}

	}
	gotoRowCol(r - 3, c + 2);
	cout << "P";
}
void printboard(int Dim, char** B, int P_N[][7])
{
	system("cls");
	int sr = 5, sc = 5;
	int dim = 8;
	for (int i = 65, c = sc + dim / 2; i <= 73; i++, c += dim)
	{
		gotoRowCol(sr - 2, c);
		cout << char(i);
	}
	for (int i = 1, r = sr + dim / 2; i <= Dim; i++, r += dim)
	{
		gotoRowCol(r, sc - 2);
		cout << i;
	}
	U2B(sc - 1, sr - 1, sr + Dim * dim, 177);
	L2R(sr - 1, sc - 1, sc + Dim * dim + 1, 177);
	U2B(sc + Dim * dim, sr - 1, sr + Dim * dim + 1, 177);
	L2R(sr + Dim * dim, sc - 1, sc + Dim * dim + 1, 177);
	for (int r = sr; r <= sr + Dim * dim - dim; r += dim * 2)
	{
		for (int c = sc; c <= sc + Dim * dim - dim; c += dim * 2)
		{
			drawbox(r, c, dim);
		}
	}
	for (int r = sr + dim; r <= sr + Dim * dim - dim; r += dim * 2)
	{
		for (int c = sc + dim; c <= sc + Dim * dim - dim; c += dim * 2)
		{
			drawbox(r, c, dim);
		}
	}
	for (int r = sr + dim / 2, br = 0; r <= dim * Dim + dim; r += dim, br++)
	{
		for (int c = sc + dim / 2, bc = 0; c <= dim * Dim + dim; c += dim, bc++)
		{

			if ((B[br][bc] >= 'A' && B[br][bc] <= 'Z') || (B[br][bc] >= char(35) && B[br][bc] <= char(41)))
			{
				SetClr(7);
			}
			if (B[br][bc] >= 'a' && B[br][bc] <= 'z' || (B[br][bc] >= char(48) && B[br][bc] <= char(53)))
			{
				SetClr(3);
			}
			if (B[br][bc] == 'p' || B[br][bc] == 'P')
			{
				drawpawn(r, c);
			}
			if (B[br][bc] == '3' || B[br][bc] == '&')
			{
				draw_p_pawn(r, c);
			}
			if (B[br][bc] == 'r' || B[br][bc] == 'R')
			{
				drawrook(r, c);
			}
			if (B[br][bc] == '5' || B[br][bc] == ')')
			{
				drawp_rook(r, c);
			}
			if (B[br][bc] == 'b' || B[br][bc] == 'B')
			{
				drawbishop(r, c);
			}
			if (B[br][bc] == '4' || B[br][bc] == '(')
			{
				drawp_bishop(r, c);
			}
			if (B[br][bc] == 'k' || B[br][bc] == 'K')
			{
				drawking(r, c);
			}
			if (B[br][bc] == 'g' || B[br][bc] == 'G')
			{
				drawgolden(r, c);
			}
			if (B[br][bc] == 's' || B[br][bc] == 'S')
			{
				drawsilver(r, c);
			}
			if (B[br][bc] == '0' || B[br][bc] == '#')
			{
				drawp_silver(r, c);
			}
			if (B[br][bc] == 'n' || B[br][bc] == 'N')
			{
				drawknight(r, c);
			}
			if (B[br][bc] == '1' || B[br][bc] == '$')
			{
				drawp_night(r, c);
			}
			if (B[br][bc] == 'l' || B[br][bc] == 'L')
			{
				drawlance(r, c);
			}
			if (B[br][bc] == '2' || B[br][bc] == '%')
			{
				drawp_lance(r, c);
			}
		}
	}
	sr = 37;
	sc = 90;
	int change = 15;
	for (int r = sr; r <= sr + dim * 3; r += dim)
	{
		for (int c = sc; c <= sc + dim; c += dim)
		{
			SetClr(change);
			drawbox(r, c, dim);
			if (change == 15)
				change = 0;
			else
				change = 15;
		}
		if (change == 15)
			change = 0;
		else
			change = 15;
	}
	char wp[2][7] = { { 'p','l','n','s','g','r','b' }, { 'P','L','N','S','G','R','B' } };
	int sizew = 0;
	int sizeb = 0;
	int turn = 0;
	for (int r = sr + dim / 2, br = 0; r <= (sr + dim / 2) + 3 * dim; r += dim, br++)
	{
		for (int c = sc + dim / 2, bc = 0; c <= (sc + dim / 2) + dim; c += dim, bc++)
		{
			if ((wp[turn][sizew] >= 'A' && wp[turn][sizew] <= 'Z') || (wp[turn][sizew] >= char(35) && wp[turn][sizew] <= char(41)))
			{
				SetClr(7);
			}
			if (wp[turn][sizew] >= 'a' && wp[turn][sizew] <= 'z' || (wp[turn][sizew] >= char(48) && wp[turn][sizew] <= char(53)))
			{
				SetClr(3);
			}
			if (wp[turn][sizew] == 'p' || wp[turn][sizew] == 'P')
			{
				drawpawn(r, c);
			}
			if (wp[turn][sizew] == '3' || wp[turn][sizew] == '&')
			{
				draw_p_pawn(r, c);
			}
			if (wp[turn][sizew] == 'r' || wp[turn][sizew] == 'R')
			{
				drawrook(r, c);
			}
			if (wp[turn][sizew] == '5' || wp[turn][sizew] == ')')
			{
				drawp_rook(r, c);
			}
			if (wp[turn][sizew] == 'b' || wp[turn][sizew] == 'B')
			{
				drawbishop(r, c);
			}
			if (wp[turn][sizew] == '4' || wp[turn][sizew] == '(')
			{
				drawp_bishop(r, c);
			}
			if (wp[turn][sizew] == 'k' || wp[turn][sizew] == 'K')
			{
				drawking(r, c);
			}
			if (wp[turn][sizew] == 'g' || wp[turn][sizew] == 'G')
			{
				drawgolden(r, c);
			}
			if (wp[turn][sizew] == 's' || wp[turn][sizew] == 'S')
			{
				drawsilver(r, c);
			}
			if (wp[turn][sizew] == '0' || wp[turn][sizew] == '#')
			{
				drawp_silver(r, c);
			}
			if (wp[turn][sizew] == 'n' || wp[turn][sizew] == 'N')
			{
				drawknight(r, c);
			}
			if (wp[turn][sizew] == '1' || wp[turn][sizew] == '$')
			{
				drawp_night(r, c);
			}
			if (wp[turn][sizew] == 'l' || wp[turn][sizew] == 'L')
			{
				drawlance(r, c);
			}
			if (wp[turn][sizew] == '2' || wp[turn][sizew] == '%')
			{
				drawp_lance(r, c);
			}
			if (sizew < 7)
			{
				gotoRowCol(r - 3, c - 3);
				cout << P_N[turn][sizew];
			}
			sizew++;
		}
	}

	sr = 37;
	sc = 120;
	turn = 1;
	for (int r = sr; r <= sr + dim * 3; r += dim)
	{
		for (int c = sc; c <= sc + dim; c += dim)
		{
			SetClr(change);
			drawbox(r, c, dim);
			if (change == 15)
				change = 0;
			else
				change = 15;
		}
		if (change == 15)
			change = 0;
		else
			change = 15;
	}
	for (int r = sr + dim / 2, br = 0; r <= (sr + dim / 2) + 3 * dim; r += dim, br++)
	{
		for (int c = sc + dim / 2, bc = 0; c <= (sc + dim / 2) + dim; c += dim, bc++)
		{
			if ((wp[turn][sizeb] >= 'A' && wp[turn][sizeb] <= 'Z') || (wp[turn][sizeb] >= char(35) && wp[turn][sizeb] <= char(41)))
			{
				SetClr(7);
			}
			if (wp[turn][sizeb] >= 'a' && wp[turn][sizeb] <= 'z' || (wp[turn][sizeb] >= char(48) && wp[turn][sizeb] <= char(53)))
			{
				SetClr(3);
			}
			if (wp[turn][sizeb] == 'p' || wp[turn][sizeb] == 'P')
			{
				drawpawn(r, c);
			}
			if (wp[turn][sizeb] == '3' || wp[turn][sizeb] == '&')
			{
				draw_p_pawn(r, c);
			}
			if (wp[turn][sizeb] == 'r' || wp[turn][sizeb] == 'R')
			{
				drawrook(r, c);
			}
			if (wp[turn][sizeb] == '5' || wp[turn][sizeb] == ')')
			{
				drawp_rook(r, c);
			}
			if (wp[turn][sizeb] == 'b' || wp[turn][sizeb] == 'B')
			{
				drawbishop(r, c);
			}
			if (wp[turn][sizeb] == '4' || wp[turn][sizeb] == '(')
			{
				drawp_bishop(r, c);
			}
			if (wp[turn][sizeb] == 'k' || wp[turn][sizeb] == 'K')
			{
				drawking(r, c);
			}
			if (wp[turn][sizeb] == 'g' || wp[turn][sizeb] == 'G')
			{
				drawgolden(r, c);
			}
			if (wp[turn][sizeb] == 's' || wp[turn][sizeb] == 'S')
			{
				drawsilver(r, c);
			}
			if (wp[turn][sizeb] == '0' || wp[turn][sizeb] == '#')
			{
				drawp_silver(r, c);
			}
			if (wp[turn][sizeb] == 'n' || wp[turn][sizeb] == 'N')
			{
				drawknight(r, c);
			}
			if (wp[turn][sizeb] == '1' || wp[turn][sizeb] == '$')
			{
				drawp_night(r, c);
			}
			if (wp[turn][sizeb] == 'l' || wp[turn][sizeb] == 'L')
			{
				drawlance(r, c);
			}
			if (wp[turn][sizeb] == '2' || wp[turn][sizeb] == '%')
			{
				drawp_lance(r, c);
			}
			if (sizeb < 7)
			{
				gotoRowCol(r - 3, c - 3);
				cout << P_N[turn][sizeb];
			}
			sizeb++;
		}
	}


}
void Turnmsg(string pnames[], int Turn)
{
	gotoRowCol(7, 90);
	cout << "1. " << pnames[0] << " ";
	SetClr(7);
	cout << "2. " << pnames[1] << endl;

	gotoRowCol(10, 90);
	cout << pnames[Turn] << "'s turn!" << endl;
}
void capture_pieces(string pnames[])
{
	gotoRowCol(34, 90);
	cout << "1. " << pnames[0] << " ";
	SetClr(7);
	gotoRowCol(34, 120);
	cout << "2. " << pnames[1] << endl;
}
void near_find(int& x, int& y)
{
	int sr = 5, sc = 5;
	int gap = 8;
	int dim = 9;
	int rows[100], size = 0;
	int cols[100];
	int min_r = abs(9 - x);
	int min_c = abs(9 - y);
	int k = x;
	int l = y;

	for (int r = sr + gap / 2, br = 0; r <= gap * dim + gap; r += gap, br++)
	{
		for (int c = sc + gap / 2, bc = 0; c <= gap * dim + gap; c += gap, bc++)
		{
			if (abs(r - x) <= min_r && abs(c - y) <= min_c)
			{
				min_r = abs(r - x), min_c = abs(c - y);
				k = r, l = c;
			}

		}
	}
	x = k;
	y = l;
}
void near_find_w(int& x, int& y)
{
	int sr = 37, sc = 90;
	int gap = 8;
	int dim = 9;
	int rows[100], size = 0;
	int cols[100];
	int min_r = abs(9 - x);
	int min_c = abs(9 - y);
	int k = x;
	int l = y;

	for (int r = sr + gap / 2, br = 0; r <= (sr + gap / 2) + 3 * gap; r += gap, br++)
	{
		for (int c = sc + gap / 2, bc = 0; c <= (sc + gap / 2) + gap; c += gap, bc++)
		{
			if (abs(r - x) <= min_r && abs(c - y) <= min_c)
			{
				min_r = abs(r - x), min_c = abs(c - y);
				k = r, l = c;
			}

		}
	}
	x = k;
	y = l;
}
void near_find_b(int& x, int& y)
{
	int sr = 37, sc = 120;
	int gap = 8;
	int dim = 9;
	int rows[100], size = 0;
	int cols[100];
	int min_r = abs(9 - x);
	int min_c = abs(9 - y);
	int k = x;
	int l = y;

	for (int r = sr + gap / 2, br = 0; r <= (sr + gap / 2) + 3 * gap; r += gap, br++)
	{
		for (int c = sc + gap / 2, bc = 0; c <= (sc + gap / 2) + gap; c += gap, bc++)
		{
			if (abs(r - x) <= min_r && abs(c - y) <= min_c)
			{
				min_r = abs(r - x), min_c = abs(c - y);
				k = r, l = c;
			}

		}
	}
	x = k;
	y = l;
}
void source_move(position& src, char** B, int Dim)
{
	int x, y;
	gotoRowCol(12, 90);
	cout << "Select Source";
	getRowColbyLeftClick(x, y);
	gotoRowCol(13, 140);
	cout << x << " " << y;
	if (y <= 78)
		near_find(x, y);
	if (y >= 90 && y <= 105)
		near_find_w(x, y);
	if (y >= 119 && y <= 136)
		near_find_b(x, y);

	int br = Dim - (x % Dim), bc = Dim - (y % Dim);
	if (br == Dim)
		br = 0;
	if (bc == Dim)
		bc = 0;
	gotoRowCol(15, 100);
	src.ri = br;
	src.ci = bc;
}
void destination_move(position& des, char** B, int Dim)
{
	int x, y;
	gotoRowCol(17, 90);
	cout << "Select Destination";
	getRowColbyLeftClick(x, y);
	if (y <= 78)
		near_find(x, y);
	if (y >= 90 && y <= 105)
		near_find_w(x, y);
	if (y >= 119 && y <= 136)
		near_find_b(x, y);
	gotoRowCol(13, 140);
	cout << x << " " << y;
	int br = Dim - (x % Dim), bc = Dim - (y % Dim);
	if (br == Dim)
		br = 0;
	if (bc == Dim)
		bc = 0;
	gotoRowCol(19, 100);

	des.ri = br;
	des.ci = bc;
}
bool isBlackpiece(char sym)
{
	return (sym >= 'A' && sym <= 'Z') || (sym >= char(35) && sym <= char(41));
}
bool isWhitepiece(char sym)
{
	return  (sym >= 'a' && sym <= 'z') || (sym >= char(48) && sym <= char(53));
}
bool isHorizontal(position src, position des)
{
	return src.ri == des.ri;
}
bool isVertical(position src, position des)
{
	return src.ci == des.ci;
}
bool isDiagonal(position src, position des)
{
	if (abs(src.ri - des.ri) == abs(src.ci - des.ci))
		return true;
	return false;
}
bool isHorizontal_PC(char** B, position src, position des)
{
	if (src.ci < des.ci)
	{
		for (int c = src.ci + 1; c < des.ci; c++)
		{
			if (B[src.ri][c] != '-')
				return false;
		}
		return true;
	}
	else
	{
		for (int c = des.ci + 1; c < src.ci; c++)
		{
			if (B[src.ri][c] != '-')
				return false;
		}
		return true;
	}
}
bool isVertical_PC(char** B, position src, position des)
{
	if (src.ri < des.ri)
	{
		for (int c = src.ri + 1; c < des.ri; c++)
		{
			if (B[c][src.ci] != '-')
				return false;
		}
		return true;
	}
	else
	{
		for (int c = des.ri + 1; c < src.ri; c++)
		{
			if (B[c][src.ci] != '-')
				return false;
		}
		return true;
	}
}
bool isDiagonal_L2R_PC(char** B, position src, position des)
{
	if (src.ri < des.ri)
	{
		for (int r = src.ri + 1, c = src.ci + 1; r < des.ri; r++, c++)
		{
			if (B[r][c] != '-')
				return false;
		}
		return true;
	}
	else
	{
		for (int r = src.ri - 1, c = src.ci - 1; r > des.ri; r--, c--)
		{
			if (B[r][c] != '-')
				return false;
		}
		return true;
	}
}
bool isDiagonal_R2L_PC(char** B, position src, position des)
{
	if (src.ri < des.ri)
	{
		for (int r = src.ri + 1, c = src.ci - 1; r < des.ri; r++, c--)
		{
			if (B[r][c] != '-')
				return false;
		}
		return true;
	}
	else
	{
		for (int r = src.ri - 1, c = src.ci + 1; r > des.ri; r--, c++)
		{
			if (B[r][c] != '-')
				return false;
		}
		return true;
	}
}
bool isDiangonal_PC(char** B, position src, position des)
{

	if ((src.ri < des.ri && src.ci < des.ci) || (src.ri > des.ri && src.ci > des.ci))
		return (isDiagonal_L2R_PC(B, src, des));
	else
		return (isDiagonal_R2L_PC(B, src, des));
}
bool RookLegality(char** B, position src, position des)
{
	return (((isHorizontal(src, des) && isHorizontal_PC(B, src, des)) || (isVertical(src, des) && isVertical_PC(B, src, des))));
}
bool BishopLegality(char** B, position src, position des)
{
	return(isDiagonal(src, des) && isDiangonal_PC(B, src, des));
}
bool KingLegality(char** B, position src, position des)
{
	int dr = abs(src.ri - des.ri);
	int dc = abs(src.ci - des.ci);
	if (dr < 0 || dr>1)
		return false;
	if (dc < 0 || dc>1)
		return false;
	else
		return (RookLegality(B, src, des) || BishopLegality(B, src, des));

}
bool RookLegality_p(char** B, position src, position des)
{
	return (((isHorizontal(src, des) && isHorizontal_PC(B, src, des)) || (isVertical(src, des) && isVertical_PC(B, src, des)) || (KingLegality(B, src, des))));
}
bool BishopLegality_p(char** B, position src, position des)
{
	return(isDiagonal(src, des) && isDiangonal_PC(B, src, des) || KingLegality(B, src, des));
}
bool G_Legality(char** B, position src, position des)
{
	int sr = src.ri;
	int sc = src.ci;
	int dr1 = des.ri;
	int dc1 = des.ci;
	int dr = abs(src.ri - des.ri);
	int dc = abs(src.ci - des.ci);
	if (dr < 0 || dr>1)
		return false;
	if (dc < 0 || dc>1)
		return false;
	if (dr1 == sr - 1 && dc1 == sc - 1)
		return false;
	if (dr1 == sr - 1 && dc1 == sc + 1)
		return false;
	else
		return true;

}
bool g_Legality(char** B, position src, position des)
{
	int sr = src.ri;
	int sc = src.ci;
	int dr1 = des.ri;
	int dc1 = des.ci;
	int dr = abs(src.ri - des.ri);
	int dc = abs(src.ci - des.ci);
	if (dr < 0 || dr>1)
		return false;
	if (dc < 0 || dc>1)
		return false;
	if (dr1 == sr + 1 && dc1 == sc - 1)
		return false;
	if (dr1 == sr + 1 && dc1 == sc + 1)
		return false;
	else
		return true;

}
bool s_legality(char** B, position src, position des)
{
	int sr = src.ri;
	int sc = src.ci;
	int dr1 = des.ri;
	int dc1 = des.ci;
	int dr = abs(src.ri - des.ri);
	int dc = abs(src.ci - des.ci);
	if (dr < 0 || dr>1)
		return false;
	if (dc < 0 || dc>1)
		return false;
	if (dr1 == sr + 1 && dc1 == sc)
		return false;
	if (dr1 == sr && dc1 == sc - 1)
		return false;
	if (dr1 == sr && dc1 == sc + 1)
		return false;
	return true;
}
bool S_legality(char** B, position src, position des)
{
	int sr = src.ri;
	int sc = src.ci;
	int dr1 = des.ri;
	int dc1 = des.ci;
	int dr = abs(src.ri - des.ri);
	int dc = abs(src.ci - des.ci);
	if (dr < 0 || dr>1)
		return false;
	if (dc < 0 || dc>1)
		return false;
	if (dr1 == sr - 1 && dc1 == sc)
		return false;
	if (dr1 == sr && dc1 == sc - 1)
		return false;
	if (dr1 == sr && dc1 == sc + 1)
		return false;
	return true;
}
bool n_legality(char** B, position src, position des)
{
	int sr = src.ri;
	int sc = src.ci;
	int dr1 = des.ri;
	int dc1 = des.ci;
	int dr = abs(src.ri - des.ri);
	int dc = abs(src.ci - des.ci);
	if (dr1 == sr - 2 && dc1 == sc - 1)
		return true;
	if (dr1 == sr - 2 && dc1 == sc + 1)
		return true;
	else
		return false;
}
bool N_legality(char** B, position src, position des)
{
	int sr = src.ri;
	int sc = src.ci;
	int dr1 = des.ri;
	int dc1 = des.ci;
	int dr = abs(src.ri - des.ri);
	int dc = abs(src.ci - des.ci);
	if (dr1 == sr + 2 && dc1 == sc - 1)
		return true;
	if (dr1 == sr + 2 && dc1 == sc + 1)
		return true;
	else
		return false;
}
bool l_legality(char** B, position src, position des)
{
	int sr = src.ri;
	int sc = src.ci;
	int dr1 = des.ri;
	int dc1 = des.ci;
	int dr = abs(src.ri - des.ri);
	int dc = abs(src.ci - des.ci);
	if (src.ri > des.ri)
		return isVertical(src, des) && isVertical_PC(B, src, des);
	return false;
}
bool L_legality(char** B, position src, position des)
{
	int sr = src.ri;
	int sc = src.ci;
	int dr1 = des.ri;
	int dc1 = des.ci;
	int dr = abs(src.ri - des.ri);
	int dc = abs(src.ci - des.ci);
	if (src.ri < des.ri)
		return isVertical(src, des) && isVertical_PC(B, src, des);
	return false;
}
bool p_legality(char** B, position src, position des)
{
	int sr = src.ri;
	int sc = src.ci;
	int dr1 = des.ri;
	int dc1 = des.ci;
	int dr = abs(src.ri - des.ri);
	int dc = abs(src.ci - des.ci);
	if (dr1 == sr - 1 && dc1 == sc)
		return true;
	return false;
}
bool P_legality(char** B, position src, position des)
{
	int sr = src.ri;
	int sc = src.ci;
	int dr1 = des.ri;
	int dc1 = des.ci;
	int dr = abs(src.ri - des.ri);
	int dc = abs(src.ci - des.ci);
	if (dr != 1 && dc != 0)
		return false;
	if (dr1 == sr + 1 && dc1 == sc)
		return true;
	return false;
}
bool isValidMove(char** B, position src, position des, int turn)
{
	switch (B[src.ri][src.ci])
	{
	case 'R':
		return RookLegality(B, src, des);
	case 'r':
		return RookLegality(B, src, des);
	case '5':
	case ')':
		return RookLegality_p(B, src, des);
	case 'b':
	case 'B':
		return BishopLegality(B, src, des);
	case '4':
	case '(':
		return BishopLegality_p(B, src, des);
	case 'K':
	case 'k':
		return KingLegality(B, src, des);
	case 'g':
	case '3':
	case '2':
	case '1':
	case '0':
		return g_Legality(B, src, des);
	case 'G':
	case '#':
	case '$':
	case '%':
	case '&':
		return G_Legality(B, src, des);
	case 's':
		return s_legality(B, src, des);
	case 'S':
		return S_legality(B, src, des);
	case 'n':
		return n_legality(B, src, des);
	case 'N':
		return N_legality(B, src, des);
	case 'l':
		return l_legality(B, src, des);
	case 'L':
		return L_legality(B, src, des);
	case 'p':
		return p_legality(B, src, des);
	case 'P':
		return P_legality(B, src, des);

	}
}
bool isValidSrc(int turn, char** B, position src, int dim)
{
	if (turn == 0)
	{
		return isWhitepiece(B[src.ri][src.ci]);
	}
	else
		return isBlackpiece(B[src.ri][src.ci]);
}
bool isValidDest(int turn, char** B, position src, int dim)
{
	if (turn == 0)
	{
		return !(isWhitepiece(B[src.ri][src.ci]));
	}
	else
		return !(isBlackpiece(B[src.ri][src.ci]));
}
void updateBoard(char** B, position des, position src)
{
	B[des.ri][des.ci] = B[src.ri][src.ci];
	B[src.ri][src.ci] = '-';
}
void change_turn(int& turn)
{
	turn++;
	if (turn == 2)
		turn = 0;
}
bool** valid_map(char** B, position src, int turn)
{
	int dim = 9;
	bool** bool_map;
	bool_map = new bool* [dim];
	for (int r = 0; r < dim; r++)
	{
		bool_map[r] = new bool[dim];
		for (int c = 0; c < dim; c++)
		{
			bool_map[r][c] = false;
		}
	}
	position des;
	for (int r = 0; r < dim; r++)
	{
		for (int c = 0; c < dim; c++)
		{
			des.ri = r;
			des.ci = c;
			if (isValidMove(B, src, des, turn))
			{
				bool_map[r][c] = true;
			}
			else
				bool_map[r][c] = false;
		}
	}
	return bool_map;
}
bool isEnemyy(char** B, position des, int turn)
{
	if (turn == 0)
		return !isWhitepiece(B[des.ri][des.ci]);
	else
		return !isBlackpiece(B[des.ri][des.ci]);
}
bool isEnemy(char** B, position des, int turn)
{
	if (turn == 1)
		return isWhitepiece(B[des.ri][des.ci]);
	else
		return isBlackpiece(B[des.ri][des.ci]);
}
void highlight(bool** bool_map, position src, int turn, char** B)
{
	int dim = 9;
	int sr = 5, sc = 5;
	int gap = 8;
	position des;
	for (int r = sr + gap / 2, br = 0; r <= gap * dim + gap; r += gap, br++)
	{
		for (int c = sc + gap / 2, bc = 0; c <= gap * dim + gap; c += gap, bc++)
		{
			des.ri = br;
			des.ci = bc;
			if (bool_map[br][bc] == true && isValidMove(B, src, des, turn) && isEnemyy(B, des, turn))
			{
				drawboxHigh(r, c, gap, 13);
			}
		}
	}
}
void un_highlight(bool** bool_map, position src, int turn, char** B)
{
	int dim = 9;
	int sr = 5, sc = 5;
	int gap = 8;
	position des;
	for (int r = sr + gap / 2, br = 0; r <= gap * dim + gap; r += gap, br++)
	{
		for (int c = sc + gap / 2, bc = 0; c <= gap * dim + gap; c += gap, bc++)
		{
			des.ri = br;
			des.ci = bc;
			if (bool_map[br][bc] == true && isValidMove(B, src, des, turn) && isEnemyy(B, des, turn))
			{
				drawboxHigh(r, c, gap, 0);
			}
		}
	}
}
bool isPromotionZone(position des, int turn)
{
	if (turn == 0)
	{
		if (des.ri >= 0 && des.ri <= 2)
			return true;
		return false;
	}
	else
	{
		if (des.ri >= 6 && des.ri <= 8)
			return true;
		return false;
	}
}
bool isPromotable(position src, char** B, int turn)
{
	if (turn == 0)
	{
		if (B[src.ri][src.ci] >= char(48) && B[src.ri][src.ci] <= char(53))
			return false;
	}
	if (turn == 1)
	{
		if (B[src.ri][src.ci] >= char(35) && B[src.ri][src.ci] <= char(41))
			return false;
	}
	return true;
}
void promotion_msg(char& choice)
{
	gotoRowCol(26, 100);
	SetClr(15);
	cout << "Want promotion or not(Y/N) ";
	cin >> choice;

}
void PromotePiece(position src, char** B, int turn)
{
	if (turn == 0)
	{
		if (B[src.ri][src.ci] == 'p')
			B[src.ri][src.ci] = '3';
		if (B[src.ri][src.ci] == 'l')
			B[src.ri][src.ci] = '2';
		if (B[src.ri][src.ci] == 'n')
			B[src.ri][src.ci] = '1';
		if (B[src.ri][src.ci] == 's')
			B[src.ri][src.ci] = '0';
		if (B[src.ri][src.ci] == 'r')
			B[src.ri][src.ci] = '5';
		if (B[src.ri][src.ci] == 'b')
			B[src.ri][src.ci] = '4';
	}
	else
	{
		if (B[src.ri][src.ci] == 'P')
			B[src.ri][src.ci] = '&';
		if (B[src.ri][src.ci] == 'S')
			B[src.ri][src.ci] = '#';
		if (B[src.ri][src.ci] == 'N')
			B[src.ri][src.ci] = '$';
		if (B[src.ri][src.ci] == 'L')
			B[src.ri][src.ci] = '%';
		if (B[src.ri][src.ci] == 'R')
			B[src.ri][src.ci] = ')';
		if (B[src.ri][src.ci] == 'B')
			B[src.ri][src.ci] = '(';
	}


}
int index_find(char p[][7], char** B, char t, int turn)
{
	for (int i = 0; i < 7; i++)
	{
		if (p[turn][i] == t)
			return i;
	}
}
void piece_convert_to_white(char& p)
{
	if (p >= 'A' && p <= 'Z')
		p = char(p + 32);
	if (p == '&')
		p = 'p';
	if (p == '#')
		p = 's';
	if (p == '$')
		p = 'n';
	if (p == '%')
		p = 'l';
	if (p == '(')
		p = 'b';
	if (p == ')')
		p = 'r';
}
void piece_convert_to_black(char& p)
{
	if (p >= 'a' && p <= 'z')
		p = char(p - 32);
	if (p == '0')
		p = 'S';
	if (p == '1')
		p = 'N';
	if (p == '2')
		p = 'L';
	if (p == '3')
		p = 'P';
	if (p == '4')
		p = 'B';
	if (p == '5')
		p = 'R';
}
void capturing(int turn, char** B, position des, char p[][7], int P_N[][7])
{
	if (isEnemy(B, des, turn))
	{
		if (turn == 0)
		{
			char pc = B[des.ri][des.ci];
			piece_convert_to_white(pc);
			int x = index_find(p, B, pc, turn);
			P_N[turn][x]++;
		}
		else
		{
			char pc = B[des.ri][des.ci];
			piece_convert_to_black(pc);
			int x = index_find(p, B, pc, turn);
			P_N[turn][x]++;
		}
	}
}
void self_king_find(char** B, int turn, int& ri, int& ci, int dim)
{
	for (int r = 0; r < dim; r++)
	{
		for (int c = 0; c < dim; c++)
		{
			if (turn == 0)
			{
				if (B[r][c] == 'k')
					ri = r, ci = c; break;

			}
			else
				if (B[r][c] == 'K')
					ri = r, ci = c; break;

		}
	}
}
void opponent_king_find(char** B, int turn, int& ri, int& ci, int dim)
{
	for (int r = 0; r < dim; r++)
	{
		for (int c = 0; c < dim; c++)
		{
			if (turn == 0)
			{
				if (B[r][c] == 'K')
					ri = r, ci = c; break;

			}
			else
				if (B[r][c] == 'k')
					ri = r, ci = c; break;

		}
	}
}
bool isKingDanger(bool** map, char** B, int dim, int turn)
{
	for (int r = 0; r < dim; r++)
	{
		for (int c = 0; c < dim; c++)
		{
			if (turn == 0)
			{
				if (map[r][c] == true && B[r][c] == 'k')
					return true;
			}
			if (turn == 1)
			{
				if (map[r][c] == true && B[r][c] == 'K')
					return true;
			}
		}
	}
	return false;
}
bool self_check(char** B, int turn, int dim)
{
	int ri, ci;
	self_king_find(B, turn, ri, ci, dim);
	position src;
	for (int r = 0; r < dim; r++)
	{
		for (int c = 0; c < dim; c++)
		{
			if (turn == 0)
			{
				src.ri = r, src.ci = c;
				if (B[src.ri][src.ci] != '-' && isBlackpiece(B[src.ri][src.ci]))
				{
					bool** bool_map = valid_map(B, src, turn);
					if (isKingDanger(bool_map, B, dim, turn))
						return true;
				}
			}
			if (turn == 1)
			{
				src.ri = r, src.ci = c;
				if (B[src.ri][src.ci] != '-' && isWhitepiece(B[src.ri][src.ci]))
				{
					bool** bool_map = valid_map(B, src, turn);
					if (isKingDanger(bool_map, B, dim, turn))
						return true;
				}
			}
		}
	}
	return false;
}
bool self_check_sp(char** const B, int turn, int dim, position des, position srcs)
{
	char** dB = B;
	updateBoard(dB, des, srcs);
	int ri, ci;
	self_king_find(dB, turn, ri, ci, dim);
	position src;
	for (int r = 0; r < dim; r++)
	{
		for (int c = 0; c < dim; c++)
		{
			if (turn == 0)
			{
				srcs.ri = r, srcs.ci = c;
				if (dB[srcs.ri][srcs.ci] != '-' && isBlackpiece(dB[srcs.ri][srcs.ci]))
				{
					bool** bool_map = valid_map(dB, srcs, turn);
					if (isKingDanger(bool_map, dB, dim, turn))
						return true;
				}
			}
			if (turn == 1)
			{
				srcs.ri = r, srcs.ci = c;
				if (dB[srcs.ri][srcs.ci] != '-' && isWhitepiece(dB[srcs.ri][srcs.ci]))
				{
					bool** bool_map = valid_map(dB, srcs, turn);
					if (isKingDanger(bool_map, dB, dim, turn))
						return true;
				}
			}
		}
	}
	return false;
}
void check_message(int turn, string pnames[])
{
	gotoRowCol(30, 90);
	cout << pnames[turn] << "in check" << endl;
}


void save(int dim, char** B)
{
	MyFile.open("load.txt", ios::out);
	string savedata = "";
	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
			savedata = savedata + B[i][j];
		}
		savedata = savedata + '\n';

	}
	MyFile << dim << endl;
	MyFile << savedata;
	MyFile.close();
}

void SaveMove(char** B, int dim)
{

	for (int j = 0; j < dim; j++)
	{
		for (int z = 0; z < dim; z++)
		{
			moves[moveCount][j][z] = B[j][z];
		}
	}
	moveCount++;
}




int main()
{
	int dim;
	char** B;
	int turn;
	position src;
	position dstn;
	string pnames[2];
	bool** valid_mapa;
	capture wb{};
	int p_n[2][7] = {};
	char wp[2][7] = { { 'p','l','n','s','g','r','b'}, {'P','L','N','S','G','R','B'} };
	cout << "new game or load game \n";
	cout << "1 ? \n";
	cout << "2 ? \n";

	int ch = 0;
	cin >> ch;
	Init(dim, B, turn, pnames, ch);
	SetClr(15);
	printboard(dim, B, p_n);
	while (true)
	{

		Turnmsg(pnames, turn);
		capture_pieces(pnames);
		if (self_check(B, turn, dim))
			check_message(turn, pnames);
		do
		{
			do
			{
				source_move(src, B, dim);
				if (!isValidSrc(turn, B, src, dim)) {
				}
				else
					break;
			} while (!isValidSrc(turn, B, src, dim));
			valid_mapa = (valid_map(B, src, turn));
			highlight(valid_mapa, src, turn, B);
			do
			{

				destination_move(dstn, B, dim);
				if (!isValidDest(turn, B, dstn, dim)) {
				}
				else
					break;
			} while (!isValidDest(turn, B, dstn, dim));
			un_highlight(valid_mapa, src, turn, B);
		} while (!(isValidMove(B, src, dstn, turn)));
		if (isPromotionZone(dstn, turn) && isPromotable(src, B, turn))
		{
			char ans = 'o';
			promotion_msg(ans);
			if (ans == 'Y' || ans == 'y')
				PromotePiece(src, B, turn);
		}
		capturing(turn, B, dstn, wp, p_n);
		updateBoard(B, dstn, src);
		SaveMove(B, dim);
		SetClr(15);
		printboard(dim, B, p_n);
		change_turn(turn);
		save(dim, B);

	}
	gotoRowCol(rows + 5, 0);
	return 0;
}



/*

void undoMove(char**& B , int dim) {

		for (int j = 0; j < dim; j++)
		{
			for (int z = 0; z < dim; z++)
			{

				B[j][z] = moves[moveCount][j][z];
			}
		}
	}




void printMove(int dim) {
	for (int i = 0; i < moveCount; i++) {

	for (int j = 0; j < dim; j++)
	{
		for (int z = 0; z < dim; z++)
		{
			cout << moves[i][j][z];
		}
		cout << endl;
	}
	cout << "NEXT MOVE >>>>>>" << endl;
	}

}


*/