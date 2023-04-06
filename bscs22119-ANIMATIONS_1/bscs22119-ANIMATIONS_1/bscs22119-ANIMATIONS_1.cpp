#include<iostream>
#include<conio.h>
#include<Windows.h>

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
void sleep(float f)
{
	for (long long x = 0; x < 10000000 * f; x++);
}

// problem no2
void L2R(int r, int cs, int ce, char sym = -37)
{
	for (int c = cs; c <= ce; c++)
	{
		gotoRowCol(r, c);
		cout << sym;
	}
}
void T2B(int c, int rs, int re, char sym = -37)
{
	for (int r = rs; r <= re; r++)
	{
		gotoRowCol(r, c);
		cout << sym;
	}
}
void stone()
{
	char sym = -37;
	int pir = 14, pic = 25;
	int ppr = pir, ppc = pic;
	int v = 15;
	for (float t = 0; true; t += 0.01)
	{
		int pr = pir + 4.9 * t * t;
		int pc = pic + v * t;
		if (pr < 70)
		{
			gotoRowCol(ppr, ppc);
			cout << " ";
			gotoRowCol(pr, pc);
			cout << sym;
			ppr = pr, ppc = pc;
			sleep(0.01);
		}
		else
		{
			gotoRowCol(ppr, ppc);
			cout << sym;
		}
	}
}
void stonemany()
{
	const int rows = 86;
	const int cols = 120;

	char sym = -37;

	int vs[] = { 7,14,21,28 ,35 };
	int size = sizeof(vs) / sizeof(int);
	int ir = 14, ic = 25;

	for (float t = 0; true; t += 0.01)
	{
		//int ppr = ir, ppc = ic;
		for (int vi = 0; vi < size; vi++)
		{
			int pr = ir + 4.9 * t * t;
			int pc = ic + vs[vi] * t;
			if (pr < rows - rows / 5)
			{
				//gotoRowCol(ppr, ppc);
				//cout << ' ';
				gotoRowCol(pr, pc);
				cout << sym;
				//ppr = pr, ppc = pc;
			}
			else
			{
				gotoRowCol(69, pc);
				cout << sym;
				break;
			}

			Sleep(1);
		}

	}

}
void printsarim(int cr, int cc)
{
	gotoRowCol(cr, cc);
	cout << "|";
	gotoRowCol(cr - 1, cc - 1);
	cout << "\\O/";
	gotoRowCol(cr + 1, cc - 1);
	cout << "/ \\";
}
void erassesarim(int cr, int cc)
{
	gotoRowCol(cr, cc);
	cout << " ";
	gotoRowCol(cr - 1, cc - 1);
	cout << " ";
	gotoRowCol(cr + 1, cc - 1);
	cout << " ";
}

int mainstones()
{
	const int rows = 86;
	const int cols = 120;

	_getch();
	char sym = -37;
	L2R(rows / 5, 0, cols / 5);
	T2B(cols / 5, rows / 5, rows - 1);
	L2R(rows - rows / 5, cols / 5, cols - 1);
	printsarim((rows / 5) - 1, (cols / 5) - 1);

	stone();


	_getch();
	return 0;

}
int mainthrowingmanystones()
{
	const int rows = 86;
	const int cols = 120;

	_getch();
	char sym = -37;
	L2R(rows / 5, 0, cols / 5);
	T2B(cols / 5, rows / 5, rows - 1);
	L2R(rows - rows / 5, cols / 5, cols - 1);
	printsarim((rows / 5) - 1, (cols / 5) - 1);

	stonemany();

	_getch();
	return 0;

}

//problem no 1
void fanpart1(int ri, int ci, int height, char sym = -37)
{
	gotoRowCol(ri, ci);
	cout << sym;
	for (int x = 1; x <= height - 1; x++)
	{
		gotoRowCol(ri - x, ci - x);
		cout << sym;
		for (int j = 0; j < 2 * (x + 1) - 3; j++)
			cout << " ";
		cout << sym;
	}
	gotoRowCol(ri - height, ci - height);
	for (int j = 0; j < 2 * (height + 1) - 1; j++)
		cout << sym;
	for (int x = 1; x <= height - 1; x++)
	{
		gotoRowCol(ri + x, ci - x);
		cout << sym;
		for (int j = 0; j < 2 * (x + 1) - 3; j++)
			cout << " ";
		cout << sym;
	}
	gotoRowCol(ri + height, ci - height);
	for (int j = 0; j < 2 * (height + 1) - 1; j++)
		cout << sym;
}
void fanpart2(int ri, int ci, int height, char sym = -37)
{
	int j = 0;
	gotoRowCol(ri, ci);
	cout << sym;
	gotoRowCol(ri - height, ci - height);

	for (int j = 1; j <= 2 * (height + 1) - 1; j++)
	{
		cout << sym;
		gotoRowCol((ri - height) + j, ci - height);
	}
	gotoRowCol((ri - height) + j, ci - height);
	cout << sym;
	for (int x = 1; x <= height - 1; x++)
	{
		gotoRowCol(ri - x, ci - x);
		cout << sym;
		for (j = 1; j <= 2 * (x + 1) - 3; j++)
		{
			cout << " ";
			gotoRowCol((ri - x) + j, ci - x);
		}
		gotoRowCol((ri - x) + j, ci - x);
		cout << sym;
	}

	/*gotoRowCol(ri - height, ci + height);
	for (int j = 0; j < 2 * (height + 1) - 1; j++)
	{
		cout << sym;
		gotoRowCol((ri - height) + j, ci + height);
	}
	for (int x = 1; x <= height - 1; x++)
	{
		gotoRowCol(ri - x, ci + x);
		cout << sym;
		for (int j = 0; j < 2 * (x + 1) - 3; j++)
		{
			cout << " ";
			gotoRowCol((ri - x) + j, ci - x);
		}
		cout << sym;
	}*/
	gotoRowCol((ri - height), ci + height);
	cout << sym;
	for (int j = 1; j <= 2 * (height + 1) - 1; j++)
	{
		cout << sym;
		gotoRowCol((ri - height) + j, ci + height);
	}
	gotoRowCol((ri - height) + j, ci + height);
	cout << sym;
	for (int x = 1; x <= height - 1; x++)
	{
		gotoRowCol(ri - x, ci + x);
		cout << sym;
		for (j = 1; j <= 2 * (x + 1) - 3; j++)
		{
			cout << " ";
			gotoRowCol((ri - x) + j, ci + x);
		}
		gotoRowCol((ri - x) + j, ci + x);
		cout << sym;
	}
}
int mainfan()
{
	_getch();
	char sym = -37;
	int delay = 100;
	while (true)
	{

		fanpart1(30, 30, 10);
		sleep(delay);
		system("cls");
		fanpart2(30, 30, 10);
		sleep(delay);
		delay = delay * 0.9;
		system("cls");


		//_getch();
	}
	return 0;
}

// problem no 4
void spiral(int h, int k, int rows, int clos, int arm, char sym = -37)
{
	float r = 1;
	float arminterval = (rows / 2.0) / arm;
	float delta = arminterval / 360;
	while (r < rows / 2.0)
		for (int th = 0; th < 360; th++)
		{
			float rad = (th * 3.14 / 180);
			float x = ceil(r * cos(rad) + h);
			float y = ceil(r * sin(rad) + k);
			gotoRowCol(y, x);
			cout << sym;
			r += delta;

		}
}
int mainspiral()
{
	const int rows = 86;
	const int cols = 120;

	while (true)
	{
		for (int r = 1; r <= rows / 2 - 2; r++)
		{
			spiral(cols / 2, rows / 2, rows, cols, 10, -37);
			Sleep(10);
			spiral(cols / 2, rows / 2, rows, cols, 10, ' ');

		}


		for (int r = rows / 2 - 2; r >= 0; r--)
		{
			spiral(cols / 2, rows / 2, rows, cols, 10, -37);
			Sleep(10);
			spiral(cols / 2, rows / 2, rows, cols, 10, ' ');

		}

	}

	//spiral(cols / 2, rows / 2, rows, cols, 10, -37);
	return 0;

}

// problem no 3

// part no 1

void circle(int h, int k, int r, char sym)
{
	const int rows = 86;
	const int cols = 120;
	int threshold = 50;
	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; x < cols; x++)
		{
			gotoRowCol(y, x);
			if (abs((x - h) * (x - h) + (y - k) * (y - k) - (r * r)) <= threshold)
			{
				cout << sym;
			}
		}
	}
}
int maincircle()
{
	const int rows = 86;
	const int cols = 120;
	circle(cols / 2, rows / 2 - 2, rows / 2 - 2, '*');
	return 0;

}

// part no 2

void circlep(int h, int k, int R, char sym = -37)
{

	for (int th = 0; th < 360; th++)
	{
		float  rad = (th * 3.14) / 180;
		int x = ceil(R * cos(rad) + h);
		int y = ceil(R * sin(rad) + k);

		gotoRowCol(y, x);
		cout << sym;
	}
}
int maincircleexpanding()
{

	const int rows = 86;
	const int cols = 120;
	while (true)
	{
		for (int R = 1; R <= rows / 2 - 2; R++)
		{
			circlep(cols / 2.0, rows / 2.0, R, -37);
			sleep(10);
			circlep(cols / 2.0, rows / 2.0, R, ' ');

		}

		for (int R = rows / 2 - 2; R >= 0; R--)
		{
			circlep(cols / 2, rows / 2, R, -37);
			sleep(10);
			circlep(cols / 2, rows / 2, R, ' ');

		}

	}


	return 0;

}


// part no 3

void emoji(int h, int k, int r, char sym)
{
	for (int th = 0; th < 360; th++)
	{
		float rad = (th * 3.14 / 180);
		float x = ceil(r * cos(rad) + h);
		float y = ceil(r * sin(rad) + k);
		gotoRowCol(y, x);
		cout << sym;

	}
}
void curve(int h, int k, int r, char sym)
{
	for (int th = 30; th < 150; th++)
	{
		float rad = (th * 3.14 / 180);
		float x = ceil(r * cos(rad) + h);
		float y = ceil(r * sin(rad) + k);
		gotoRowCol(y, x);
		cout << sym;

	}
}
void eyebrow1(int h, int k, int r, char sym)
{
	for (int th = 210; th < 320; th++)
	{
		float rad = (th * 3.14 / 180);
		float x = ceil(r * cos(rad) + h);
		float y = ceil(r * sin(rad) + k);
		gotoRowCol(y, x);
		cout << sym;

	}
}
void eyebrow2(int h, int k, int r, char sym)
{
	for (int th = 210; th < 320; th++)
	{
		float rad = (th * 3.14 / 180);
		float x = ceil(r * cos(rad) + h);
		float y = ceil(r * sin(rad) + k);
		gotoRowCol(y, x);
		cout << sym;

	}
}
int mainEmoji()
{
	const int rows = 86;
	const int cols = 120;

	emoji(cols / 2, rows / 2, rows / 2, '*');
	curve(cols / 2, rows / 2, rows / 4, '*');
	eyebrow1(cols * 0.40, rows * 0.25, rows / 8, '*');
	eyebrow2(cols * 0.60, rows * 0.25, rows / 8, '*');

	int A[2][2] = { {cols * 0.40, rows * 0.25},{cols * 0.60, rows * 0.25} };
	int size = sizeof(A) / sizeof(int);
	int maxradius = rows / 16;

	for (int R = 1; R <= maxradius; R++) {

		for (int st = 0; st < 2; st++)
		{
			int h = A[st][0];
			int k = A[st][1];
			emoji(h, k, R, -37);
			Sleep(100);
			emoji(h, k, R, ' ');
		}
	}


	return 0;
}



// Question no 3
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

int mainHamza()
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





void menu()
{
	system("cls");
	cout << "1. throwing stone" << endl;
	cout << "2. throwing many stone " << endl;
	cout << "3. print fan" << endl;
	cout << "4. spiral" << endl;
	cout << "5. circle" << endl;
	cout << "6. many circle" << endl;
	cout << "7. Print Emoji " << endl;
	cout << "8. Print Name " << endl;
	cout << "9. Growing name " << endl;

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
			mainstones(); break;
		case 2:
			mainthrowingmanystones(); break;
		case 3:
			mainfan(); break;
		case 4:
			mainspiral(); break;
		case 5:
			maincircle(); break;
		case 6:
			maincircleexpanding(); break;
		case 7:
			mainEmoji(); break;
		case 8:
			mainHamza(); break;
		case 9:
			maingrown(); break;
		}
		cout << "------------------------" << endl;
		cout << "Do you want to continue: ";
		cin >> con;


	}


}