
#include<iostream>
#include<conio.h>
#include<iomanip>
#include<Windows.h>
#include<math.h>

using namespace std;

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


void sinwave1a(int A, int n, int cr, char sym, int cols)
{
	float Dtheeta = (n * 360.0) / cols;

	float theeta = 0;
	for (int c = 0; c < cols; c++)
	{
		int r = A * (-1) * sin(theeta * 3.14 / 180) + cr;
		gotoRowCol(r, c);
		cout << sym;
		theeta += Dtheeta;
	}
}
void sinwave1b(int A, int n, int cr, char Arr[], int cols)
{
	float Dtheeta = (n * 360.0) / cols;

	float theeta = 0;
	for (int c = 0; c < cols; c++)
	{
		for (int i = 0; i < 5; i++)
		{
			int r = A * (-1) * sin(theeta * 3.14 / 180) + cr;
			gotoRowCol(r, c);
			cout << Arr[i];
			theeta += Dtheeta;
		}
	}
}
int main1a()
{
	_getch();
	int cols = 120;
	int rows = 80;
	float Amp = 10;
	sinwave1a(Amp, 3, rows / 2, '*', cols);
	_getch();

	return 0;
}
int main1b()
{
	int cols = 120;
	int rows = 80;
	float Amp = 10;
	char A[5] = { 'H','A','M','Z','A' };

	sinwave1b(Amp, 3, rows / 2, A, cols);

	_getch();

	return 0;
}

void sinwave2a(float sa, int A, int n, int cr, char sym, int cols)
{
	float Dtheeta = (n * 360.0) / cols;

	float theeta = sa;
	for (int c = 0; c < cols; c++)
	{
		int r = A * (-1) * sin(theeta * 3.14 / 180) + cr;
		gotoRowCol(r, c);
		cout << sym;
		theeta += Dtheeta;
	}
}
void sinwave2b(float sa, int A, int n, int cr, int cols)
{
	char Array[5] = { 'H','A','M','Z','A' };

	float Dtheeta = (n * 360.0) / cols;

	float theeta = sa;
	int s = 0;
	for (int c = 0; c < cols; c++)
	{
		int r = A * (-1) * sin(theeta * 3.14 / 180) + cr;
		gotoRowCol(r, c);
		cout << Array[s];
		theeta += Dtheeta;
		if (s < 4)
		{
			s++;
		}
		else
		{
			s = 0;
		}
	}
}
int main2a()
{
	int cols = 122;
	int rows = 85;
	float sa = 0;

	float Amp = 10;
	while (true)
	{
		sinwave2a(sa, Amp, 3, rows / 2, -37, cols);
		Sleep(10);
		sinwave2a(sa, Amp, 3, rows / 2, ' ', cols);
		sa++;

	}
	_getch();
	return 0;
}
int main2b()
{
	_getch();
	int cols = 120;
	int rows = 85;
	int sa = 0;

	float Amp = 10;
	while (true)
	{

		sinwave2b(sa, Amp, 2, rows / 2, cols);
		Sleep(10);
		sinwave2a(sa, Amp, 2, rows / 2, ' ', cols);
		sa++;
	}
	_getch();
	return 0;

}

void sinwave3(int sa, float A, int n, int cr, char sym, int cols)
{
	float Dtheeta = (n * 360.0) / cols;

	float theeta = sa;
	for (int c = 0; c < cols; c++)
	{
		int r = A * (-1) * sin(theeta * 3.14 / 180) + cr;
		gotoRowCol(r, c);
		cout << sym;
		theeta += Dtheeta;

	}

}
int main3()
{
	_getch();
	int cols = 120;
	int rows = 85;
	float sa = 0;

	float Amp;
	while (true)
	{
		for (Amp = 0; Amp <= 20; Amp += 1)
		{
			sinwave3(sa, Amp, 3, rows / 2, -37, cols);
			Sleep(10);
			sinwave3(sa, Amp, 3, rows / 2, ' ', cols);
			sa++;
		}
		for (Amp = 20; Amp >= 0; Amp -= 1)
		{
			sinwave3(sa, Amp, 3, rows / 2, -37, cols);
			Sleep(10);
			sinwave3(sa, Amp, 3, rows / 2, ' ', cols);
			sa++;
		}
	}
	_getch();
	return 0;

}


void printH(int x, int y, int scale, char sym = -37)
{
	for (int s = 0; s < 2 * scale; s++) // this loop for printing - right and left form center  
	{
		gotoRowCol(x, y - scale + 1 + s);
		cout << sym;
	}


	for (int s = 0; s <= 2 * scale; s++) // this loop for printing | of right side
	{
		gotoRowCol(x + scale - s, y + scale);
		cout << sym;
	}


	for (int s = 0; s <= 2 * scale; s++) // this loop for printing | of left side
	{
		gotoRowCol(x + scale - s, y - scale);
		cout << sym;
	}
}
void printA(int x, int y, int scale, char sym)
{
	for (int s = 0; s < 2 * scale; s++)
	{
		gotoRowCol(x, y - scale + 1 + s);
		cout << sym;
	}

	for (int s = 0; s < 2 * scale; s++)
	{
		gotoRowCol(x - scale + s + 1, y - scale);
		cout << sym;
	}
	for (int s = 0; s < 2 * scale; s++)
	{
		gotoRowCol(x - scale + s + 1, y + scale);
		cout << sym;
	}

	for (int s = 0; s < 2 * scale; s++)
	{
		gotoRowCol(x - scale + 1, y - scale + 1 + s);
		cout << sym;
	}
}
void printZ(int x, int y, int scale, char sym)
{
	for (int i = 0; i < 2 * scale; i++)
	{
		gotoRowCol(x - 9, (y + i));
		cout << sym;
	}
	for (int s = 2 * scale; s > 0; s--)
	{
		gotoRowCol((x - s) + 11, y + s);
		cout << sym;
	}
	for (int i = 0; i < 2 * scale; i++)
	{
		gotoRowCol(x + 10, (y + i));
		cout << sym;
	}

}
void printM(int x, int y, int scale, char sym = -37)
{
	for (int s = 0; s < 2 * scale; s++)
	{
		gotoRowCol(x + s, y);
		cout << sym;
	}
	for (int s = 0; s < 2 * scale; s++)
	{
		gotoRowCol(x + s, y + s);
		cout << sym;
	}
	for (int s = 2 * scale; s > 0; s--)
	{
		gotoRowCol((x - s) + 20, (y + s) + 20);
		cout << sym;
	}

	for (int s = 0; s < 2 * scale; s++)
	{
		gotoRowCol(x + s, y + 2 * scale + 21);
		cout << sym;
	}
}
int mainAZ()
{
	int c = 11;
	SetClr(c);
	while (true)
	{
		int Rows = 84, Cols = 120;
		printA(Rows / 2, (Cols / 2) - 28, 10, '*');
		printZ((Rows / 2), (Cols / 2) + 28, 10, '*');


	}
	return _getch();
	return 0;
}
int maingrown()
{
	int Rows = 84, Cols = 120;

	
	for (int sc = 0; sc < Rows / 2; sc++)
	{
		printA(Rows / 2, Cols / 2, sc, '*');
		Sleep(1);
		printA(Rows / 2, Cols / 2, sc, ' ');
	}

	for (int sc = Rows / 2; sc >= 0; sc--)
	{
		printA(Rows / 2, Cols / 2, sc, '*');
		Sleep(1);
		printA(Rows / 2, Cols / 2, sc, ' ');
	}

	

	for (int sc = 0; sc < Rows / 2; sc++)
	{
		printZ(Rows / 2, Cols / 2, sc, '*');
		Sleep(1);
		printZ(Rows / 2, Cols / 2, sc, ' ');
	}

	for (int sc = Rows / 2; sc >= 0; sc--)
	{
		printZ(Rows / 2, Cols / 2, sc, '*');
		Sleep(1);
		printZ(Rows / 2, Cols / 2, sc, ' ');
	}

	


	return _getch();
	return 0;
}

const int maxdim = 100;
void matrix(int box[][maxdim], int dim)
{

	for (int a = 0; a < dim / 2; a++)
	{
		int count = 1;
		for (int c = a; c < dim - 1 - a; c++, count++)
		{
			box[a][c] = count;
		}

		for (int r = a; r < dim - 1 - a; r++, count++)
		{
			box[r][dim - 1 - a] = count;
		}
		for (int c = dim - 1 - a; c > a; c--, count++)
		{
			box[dim - 1 - a][c] = count;
		}
		for (int r = dim - 1 - a; r > a; r--, count++)
		{
			box[r][a] = count;
		}


		/*
		if (a == 1)
		{
			int b = box[1][0];
			swap(box[0][0], box[1][0]);

			b++;
		}
		*/
	}
}
void print(int box[][maxdim], int dim)
{
	for (int r = 0; r < dim; r++)
	{
		for (int c = 0; c < dim; c++)
		{
			cout << setw(3) << box[r][c];

		}
		cout << endl;
	}
}
int mainmatrix()
{
	const int maxdim = 100;
	int dim = 7;
	int box[maxdim][maxdim] = {};
	matrix(box, dim);
	print(box, dim);

	return 0;
}
void SpacingRecSpiral(int d, char S)
{
	const int rows = 84;
	const int cols = 120;
	system("cls");
	for (int rec = 0; rec < rows / (2 * d); rec++)
	{
		for (int c = (rec - 1) * d; c < cols - 1 - rec * d; c++)
		{
			gotoRowCol(rec * d, c);
			cout << S;
			Sleep(7);
		}
		for (int r = rec * d; r <= rows - 1 - rec * d; r++)
		{
			gotoRowCol(r, cols - 1 - rec * d);
			cout << S;
			Sleep(3);
		}
		for (int cs = cols - 1 - rec * d; cs > rec * d; cs--)
		{
			gotoRowCol(rows - 1 - rec * d, cs);
			cout << S;
			Sleep(3);

		}
		for (int re = rows - 1 - (rec - 1) * d; re > rec * d; re--)
		{
			gotoRowCol(re, (rec - 1) * d);
			cout << S;
			Sleep(2);
		}

	}
}
int mainSpacingRecSpiral()
{
	char symbol = '/';
	int nr = 82;
	int nc = 170;
	int ang;
	cout << "Enter no. of Spacing: ";
	cin >> ang;
	SpacingRecSpiral(ang, symbol);
	return 0;
}


void menu()
{
	system("cls");
	cout << "1. Sin wave" << endl;
	cout << "2. Name wave " << endl;
	cout << "3. Sine wave moving" << endl;
	cout << "4. Name wave moving" << endl;
	cout << "5. changing amplitude" << endl;
	cout << "6. Print Name" << endl;
	cout << "7. Grown Name " << endl;
	cout << "8. print Matrix " << endl;
	cout << "9. SpacingRecSpiral " << endl;

}
int main()
{
	int choice;
	char con = 'y';
	while (con == 'y' || con == 'y')
	{
		menu();
		cin >> choice;
		cout << "----------------------" << endl;
		switch (choice)
		{
		case 1:
			main1a(); break;
		case 2:
			main1b(); break;
		case 3:
			main2a(); break;
		case 4:
			main2b(); break;
		case 5:
			main3(); break;
		case 6:
			mainAZ(); break;
		case 7:
			maingrown(); break;
		case 8:
			mainmatrix(); break;
		case 9:
			mainSpacingRecSpiral(); break;



		}
		cout << "------------------------" << endl;
		cout << "Do you want to continue: ";
		cin >> con;


	}

}
