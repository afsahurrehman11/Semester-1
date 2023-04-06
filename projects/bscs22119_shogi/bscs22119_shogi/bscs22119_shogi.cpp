#include<iostream>
#include<windows.h>
#include<fstream>
#include<iomanip>
using namespace std;
//9
//lnsgkgsnl
//- r---- - b -
//ppppppppp
//-------- -
//-------- -
//-------- -
//PPPPPPPPP
//- B---- - R -
//LNSGKGSNL
//   https:// playshogi.com /#Board:b-1368688477 


fstream MyFile;

#define sb_size 8       // single box size 
const int  max_cols= 160;
const int max_rows=80;
char moves[20][9][9];
int moveCount = 0;

enum { white, black };
struct position
{
	int ri, ci;
};

char** copyB;


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








void init(char**& B,char**& copyB, int& dim, string Pname[2], int turn,int choice)
{
	/*
	copyB = new char* [dim];
	for (int i = 0; i < dim; i++)
	{
		copyB[i] = new char[dim];
	}
	*/


	if (choice == 1)
	{
		ifstream rdr("text.txt");
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
	}
	if (choice == 2)
	{
		ifstream rdr("load.txt");
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
	}

	cout << "ENTER 1st PLAYER NAME : \n";
	cin >> Pname[0];

	cout << "ENTER 2nd PLAYER NAME : \n";
	cin >> Pname[1];

	turn = white;
	
}

void print_Board(char** B, int dim)
{
	for (int r = 0; r < dim; r++)
	{
		for (int c = 0; c < dim; c++)
		{
			cout << B[r][c];
		}
		cout << endl;
	}
}

void turn_msg(string Pname[], int turn)
{
	cout << Pname[turn] << "'s turn \n";
}
	

bool isWhite(char sym)
{
	if (sym < 'A' || sym > 'Z')
	{
		return false ;
	}
	else
	{
		return true;
	}
}
bool isBlack(char sym)
{
	if (sym < 'a' || sym > 'z')
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool isMyPiece(char sym, int turn)
{
	if (turn == white)
	{
		return isWhite(sym);
	}

	if (turn == black)
	{
		return isBlack(sym);
	}
}

bool isValid_Selection(char** B, position Sc, int dim, int turn)     // why i passed b & ???
{
	if (Sc.ci < 0 || Sc.ci >= dim)
	{
		cout << "COLUMNS ARE OUT OF BOUNDARY !!! \n";
		return false;
	}

	if (Sc.ri < 0 || Sc.ri >= dim)
	{
		cout << "ROWS ARE OUT OF BOUNDARY !!! \n";
		return false;
	}

	if (!isMyPiece(B[Sc.ri][Sc.ci], turn))
	{
		return false;
	}


	if (isMyPiece(B[Sc.ri][Sc.ci], turn))
		return true;
}

bool isValid_Drop(char** B, position Dc, int dim, int turn)
{
	if (Dc.ci < 0 || Dc.ci >= dim)
	{
		cout << "DROPPING COLUMNS ARE OUT OF BOUNDARY !!! \n";
		return false;
	}

	if (Dc.ri < 0 || Dc.ri >= dim)
	{
		cout << "DROPPING ROWS ARE OUT OF BOUNDARY !!! \n";
		return false;
	}

	if (isMyPiece(B[Dc.ri][Dc.ci], turn))
	{
		cout << "INVALID DROP!!! THERE IS ALREADY YOUR PIECE\n";
		return false;
	}
	
	if (!(isMyPiece(B[Dc.ri][Dc.ci], turn)))
	{
		return true;
	}

	
}



void select_position(char**& B, position &Sc, int dim, int turn)
{
	int srow = 0, scol = 0;

	getRowColbyLeftClick(srow, scol);

	Sc.ri = srow / sb_size;
	Sc.ci = scol / sb_size;


}

void select_desti(char**& B, position &Dc, int dim, int turn)
{
	int drow = 0, dcol = 0;
	getRowColbyLeftClick(drow, dcol);
	Dc.ri = drow / sb_size;
	Dc.ci = dcol / sb_size;

}




void updateBoard(char**& B, position Sc, position Dc)
{
	char piece = B[Sc.ri][Sc.ci];
	B[Sc.ri][Sc.ci] = '-';
	B[Dc.ri][Dc.ci] = piece;
}

void turn_Change(int& turn)
{
	if (turn == white)
	{
		turn = black;
	}
	else
	{
		turn = white;
	}
}

void single_box(int sr, int sc, int mrows, int mcols,char sym , int clr, int textcl)
{
	int r, c;
	for (r = 0; r < mrows; r++)
	{
		for ( c = 0; c < mcols; c++)
		{
			SetClr(clr);
			gotoRowCol(sr + r, sc + c);
			cout << char(-37);
		}
	}
	SetClr(textcl);
	gotoRowCol(mrows / 2 +sr, mcols / 2+sc );
	cout << sym;
}

void draw_background(char **B,int dim, int mrows, int mcols)
{

	for (int ri = 0; ri < dim; ri++)
	{
		for (int ci = 0; ci < dim; ci++)
		{
			if ((ri + ci) % 2 == 0)
			{
				single_box(ri * mrows, ci * mcols, mrows, mcols,B[ri][ci], 15,14);
			}
			else
			{
				single_box(ri * mrows, ci * mcols, mrows, mcols, B[ri][ci], 3,14);

			}
		}
	}
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n";
	
	
}
 

//------------>>> PIECE MOVEMENTS

bool is_Horizonal_move(position Sc, position Dc)
{
	if (Sc.ri == Dc.ri)
	{
		return true;
	}

	return false;

}

bool is_Vertical_move(position Sc, position Dc)
{

	if (Sc.ci == Dc.ci)
		return true;
	return false;

}

bool is_Diagonal_move(position Sc, position Dc)
{
	if (abs(Dc.ri - Sc.ri) == abs(Dc.ci - Sc.ci))
		return true;
	return false;

}


bool iS_Hori_path_clr(char** B, position Sc, position Dc)
{
	int cs = 0, ce = 0;

	if (Sc.ci < Dc.ci)
	{
		cs = Sc.ci + 1;
		ce = Dc.ci - 1;
	}

	else
	{
		cs = Dc.ci + 1;
		ce = Sc.ci - 1;
	}

	for (int c = cs ; c <= ce ; c++)
	{
		if (B[Sc.ri][c] != '-')
			return false;
	}
	return true;
}

bool is_Vertical_path_clr(char** B, position Sc, position Dc)
{
	int rs = 0, re = 0;
	if (Sc.ri < Dc.ri)
	{
		rs = Sc.ri + 1;
		re = Dc.ri - 1;
	}
	else
	{
		rs = Dc.ri + 1;
		re = Sc.ri - 1;
	}

	for (int r = rs; r <= re; r++)
	{
		if (B[r][Sc.ci] != '-')
			return false;
	}
	return true;
	
}

bool is_Diagonal_path_clr_L2R (char** B, position Sc, position Dc)
{
	if (Sc.ri < Dc.ri)
	{
		int gap = Dc.ri - Sc.ri - 1;
		
		for (int i = 1; i <= gap; i++)
		{
			if (B[Sc.ri + i][Sc.ci + i] != '-')
			{
				return false;

			}
		}
		return true;
	
	}


	if (Sc.ri > Dc.ri)
	{
		int gap = Sc.ri - Dc.ri - 1;

		for (int i = 1; i <= gap; i++)
		{
			if (B[Sc.ri - i][Sc.ci - i] != '-')
			{
				return false;

			}
		}
		return true;

	}
}

bool is_Diagonal_path_clr_R2L(char** B, position Sc, position Dc)
{
	int rs = 0, re = 0;
	int cs = 0, ce = 0;
	if (Sc.ri > Dc.ri)
	{
		rs = Dc.ri + 1; re = Sc.ri - 1;
		cs = Sc.ci + 1; ce = Dc.ci - 1;
	}
	else
	{

		rs = Sc.ri + 1; re = Dc.ri - 1;
		cs = Dc.ci + 1; ce = Sc.ci - 1;
	}

	int r = rs , c =0;
	
	while (r <= re)       // just for double check 
	{
		for (int c=cs;c<=ce;c++, r++)
		{
			if (B[Sc.ri + r][Sc.ci + c] != '-')
			{
				return false;
			}
		}

	}
	return true;
}



bool rook_legality(char** B, position Sc, position Dc)
{
	return ((is_Horizonal_move(Sc, Dc) && iS_Hori_path_clr(B, Sc, Dc)) || 
		     (is_Vertical_move(Sc, Dc) && is_Vertical_path_clr(B, Sc, Dc)));
}

bool bishop_legality(char** B, position Sc, position Dc)
{
	return ((is_Diagonal_move(Sc, Dc) && is_Diagonal_path_clr_L2R(B, Sc, Dc)) ||
		(is_Diagonal_move(Sc, Dc) && is_Diagonal_path_clr_R2L(B, Sc, Dc)));
}

bool queen_legality(char** B, position Sc, position Dc)   
{
	return rook_legality(B, Sc, Dc) || bishop_legality(B, Sc, Dc);
}

bool king_legality(char** B, position Sc, position Dc)
{
	int delta_r = abs (Sc.ri-Dc.ri);
	int delta_c = abs(Sc.ci - Dc.ci);
	return queen_legality(B, Sc, Dc) && delta_r <= 1 && delta_c <= 1;
}

bool knight_legality(char** B, position Sc, position Dc)
{
	int delta_r = abs(Sc.ri - Dc.ri);
	int delta_c = abs(Sc.ci - Dc.ci);
	return ((delta_r == 2 && delta_c == 1) || (delta_r == 1 && delta_c == 2));

}

bool gold_general_legality(char** B, position Sc, position Dc, int turn)
{
	if (turn == white) {
		if (Dc.ri == Sc.ri + 1 && Dc.ci == Sc.ci + 1)
		{
			return false;
		}
		if (Dc.ri == Sc.ri + 1 && Dc.ci == Sc.ci - 1)
		{
			return false;
		}

		return king_legality(B, Sc, Dc);

	}

	if (turn == black) 
	{
		if (Dc.ri == Sc.ri - 1 && Dc.ci == Sc.ci + 1)
		{
			return false;
		}
		if (Dc.ri == Sc.ri - 1 && Dc.ci == Sc.ci - 1)
		{
			return false;
		}

		return king_legality(B, Sc, Dc);

	}

}

bool silver_general_legality(char** B, position Sc, position Dc, int turn)
{
	if (turn == white)
	{
		if ((Dc.ci == Sc.ci + 1 && Dc.ri == Sc.ri)  || (Dc.ci == Sc.ci - 1 && Dc.ri == Sc.ri) || (Dc.ri==Sc.ri+1 && Dc.ci==Sc.ci))
		{
			return false;
		}
		return  king_legality(B, Sc, Dc);
	}

	if (turn == black)
	{
		if ((Dc.ci == Sc.ci + 1 && Dc.ri == Sc.ri) || (Dc.ci == Sc.ci - 1 && Dc.ri == Sc.ri) || (Dc.ri == Sc.ri - 1 && Dc.ci == Sc.ci))
		{
			return false;
		}
		return  king_legality(B, Sc, Dc);
	}
}

bool lance_legality(char** B, position Sc, position Dc, int turn)
{
	if (turn == white) 
	{
		if ((Dc.ci == Sc.ci) && (Dc.ri < Sc.ri ) && is_Vertical_path_clr(B,Sc,Dc))
		{
			return true;
		}
		return false;
	}
	if (turn == black)
	{
		if( (Dc.ci == Sc.ci) && (Dc.ri > Sc.ri ) && is_Vertical_path_clr(B, Sc, Dc))
		{
			return true;
		}
		return false;
	}
}

bool pawn_legality(char** B, position Sc, position Dc, int turn)
{
	if (turn == white)
	{
		if ( (Dc.ci == Sc.ci) && (Dc.ri == Sc.ri - 1))
		{
			return true;
		}
		return false;
	}
	if (turn == black)
	{
		if ((Dc.ci == Sc.ci) && (Dc.ri == Sc.ri + 1))
		{
			return true;
		}
		return false;
	}
}

bool isLegal_Move(char** B, position Sc, position Dc, int dim,int turn )
{
	switch (B[Sc.ri][Sc.ci])
	{
	case 'R':
	case'r':
	{
		return rook_legality(B, Sc, Dc);
		break;
	}
	case 'B':
	case 'b':
	{
		return bishop_legality(B, Sc, Dc);
		break;
	}
	case 'K':
	case 'k':
	{
		return king_legality(B, Sc, Dc);
		break;
	}
	case 'N':
	case 'n':
	{
		return knight_legality(B, Sc, Dc);
		break;
	}
	case 'G':
	case 'g':
	case 'Z':
	case 'z':
	case 'A':
	case 'a':
	case 'C':
	case 'c':
	case 'D':
	case 'd':


	{
		return gold_general_legality(B, Sc, Dc, turn);
		break;
	}
	case 'S':
	case 's':
	{
		return silver_general_legality(B, Sc, Dc, turn);
		break;
	}
	case'L':
	case'l':
	{
		return lance_legality(B, Sc, Dc, turn);
		break;
	}
	case'P':
	case'p':
	{
		return pawn_legality(B, Sc, Dc, turn);
		break;
	}
	case'X':
	case'x':
	{
		return king_legality (B, Sc, Dc)|| bishop_legality(B, Sc, Dc);
	}

	case'Y':
	case'y':
	{
		return king_legality(B, Sc, Dc) || rook_legality(B, Sc, Dc);
	}
	default:
		return false;


	}

}


//              PROMOTION 
// QWE TYU
//     												pawns, lances : last row         
//		X = Promoted bishop							knights: 2nd last row                     
//		Y = Promoted rook							bishop, rook, silver gernal : optional					
//		Z = promoted silver gernal
//		A = promoted lawnce 
//		C = promoted  knight 
//      D = promoted pawn
//



void promotion(char**& B, position Sc, position Dc)
{
	switch (B[Sc.ri][Sc.ci])
	{
//                          WHITE	
// 
//	D = promoted pawn
	case'P':
	{
		if (Dc.ri == 0)
		{
			cout << "YOUR PAWN HAS BEEN PROMOTED!!!\n";
			B[Sc.ri][Sc.ci] = 'D';
		}
		if(Dc.ri == 1 || Dc.ri == 2)
		{
			cout << "DO YOU WANT TO PORMOTE YOUR CURRENT PIECE ...?\n";
			cout << "1 = Yes       2 = no \n";
			int option = 0;

			cin >> option;
			if (option == 1)
			{
				cout << "YOUR PAWN HAS BEEN PROMOTED !!!\n";
				B[Sc.ri][Sc.ci] = 'D';
			}
				
		}
		break;
	}

	//	A = promoted lawnce
	case 'L':
	{
		if (Dc.ri == 0)
		{
			cout << "YOUR LANCE HAS BEEN PROMOTED !!!\n";
			B[Sc.ri][Sc.ci] = 'A';
		}
		if (Dc.ri == 1 || Dc.ri == 2)
		{
			cout << "DO YOU WANT TO PORMOTE YOUR CURRENT PIECE ...?\n";
			cout << "1 = Yes       2 = no \n";
			int option = 0;

			cin >> option;
			if (option == 1)
			{
				cout << "YOUR LANCE HAS BEEN PROMOTED !!!\n";
				B[Sc.ri][Sc.ci] = 'A';
			}

		}
		break;
	}

//	C = promoted  knight
	case 'N':
	{

		if (Dc.ri == 0 || Dc.ri == 1)
		{
			cout << "YOUR KNIGHT HAS BEEN PROMOTED !!!\n";
			B[Sc.ri][Sc.ci] = 'C';
		}
		if (Dc.ri == 2)
		{
			cout << "DO YOU WANT TO PORMOTE YOUR CURRENT PIECE ...?\n";
			cout << "1 = Yes       2 = no \n";
			int option = 0;
			cin >> option;
			if (option == 1)
			{
				cout << "YOUR KNIGHT HAS BEEN PROMOTED !!!\n";
				B[Sc.ri][Sc.ci] = 'C';
			}
		}
		break;
	}

//	Z = promoted silver gernal
	case 'S':
	{
		if (Dc.ri == 0 || Dc.ri == 1 || Dc.ri == 2)
		{
			cout << "DO YOU WANT TO PORMOTE YOUR CURRENT PIECE ...?\n";
			cout << "1 = Yes       2 = no \n";
			int option = 0;
			cin >> option;
			if (option == 1)
			{
				cout << "YOUR SILVER GERNAL HAS BEEN PROMOTED !!!\n";
				B[Sc.ri][Sc.ci] = 'Z';
			}
		}
		break;
	}

//	X = Promoted bishop
	case'B':
	{
		if (Dc.ri == 0 || Dc.ri == 1 || Dc.ri == 2)
		{
			cout << "DO YOU WANT TO PORMOTE YOUR CURRENT PIECE ...?\n";
			cout << "1 = Yes       2 = no \n";
			int option = 0;
			cin >> option;
			if (option == 1)
			{
				cout << "YOUR PIECE HAS BEEN PROMOTED !!!\n";
				B[Sc.ri][Sc.ci] = 'X';
			}
		}
		break;
	}

	
//	Y = Promoted rook
	case'R':
	{
		if (Dc.ri == 0 || Dc.ri == 1 || Dc.ri == 2)
		{
			cout << "DO YOU WANT TO PORMOTE YOUR CURRENT PIECE ...?\n";
			cout << "1 = Yes       2 = no \n";
			int option = 0;
			cin >> option;
			if (option == 1)
			{
				cout << "YOUR PIECE HAS BEEN PROMOTED !!!\n";
				B[Sc.ri][Sc.ci] = 'Y';
			}
		}
		break;
	}
	
	//			BLACK
	//	d = promoted pawn

	case'p':
	
	{
		if (Dc.ri == 8)
		{
			cout << "YOUR PAWN HAS BEEN PROMOTED !!!\n";
			B[Sc.ri][Sc.ci] = 'd';
		}
		if (Dc.ri == 6 || Dc.ri == 7)
		{
			cout << "DO YOU WANT TO PORMOTE YOUR CURRENT PIECE ...?\n";
			cout << "1 = Yes       2 = no \n";
			int option = 0;
			cin >> option;
			if (option == 1)
			{
				cout << "YOUR PAWN HAS BEEN PROMOTED !!!\n";
				B[Sc.ri][Sc.ci] = 'd';
			}
		}
		break;
	}

	
//	c = promoted  knight

	case 'n':
	{

		if (Dc.ri == 7 || Dc.ri == 8)
		{
			cout << "YOUR KNIGHT HAS BEEN PROMOTED !!!\n";
			B[Sc.ri][Sc.ci] = 'c';
		}
		if (Dc.ri == 6)
		{
			cout << "DO YOU WANT TO PORMOTE YOUR CURRENT PIECE ...?\n";
			cout << "1 = Yes       2 = no \n";
			int option = 0;
			cin >> option;
			if (option == 1)
			{
				cout << "YOUR KNIGHT HAS BEEN PROMOTED !!!\n";
				B[Sc.ri][Sc.ci] = 'c';
			}
		}
		break;
	}
						
//		z = promoted silver gernal

	case 's':
	{
		if (Dc.ri == 6 || Dc.ri == 7 || Dc.ri == 8)
		{
			cout << "DO YOU WANT TO PORMOTE YOUR CURRENT PIECE ...?\n";
			cout << "1 = Yes       2 = no \n";
			int option = 0;
			cin >> option;
			if (option == 1)
			{
				cout << "YOUR SILVER GERNAL HAS BEEN PROMOTED !!!\n";
				B[Sc.ri][Sc.ci] = 'z';
			}
		}
		break;
	}


	

	//	x = Promoted bishop						
			

	case'b':
	{
		if (Dc.ri == 6 || Dc.ri == 7 || Dc.ri == 8)
		{
			cout << "DO YOU WANT TO PORMOTE YOUR CURRENT PIECE ...?\n";
			cout << "1 = Yes       2 = no \n";
			int option = 0;
			cin >> option;
			if (option == 1)
			{
				cout << "YOUR PIECE HAS BEEN PROMOTED !!!\n";
				B[Sc.ri][Sc.ci] = 'x';
			}
		}
		break;
	}


	
	//		y = Promoted rook

	case'r':
	{
		if (Dc.ri == 6 || Dc.ri == 7 || Dc.ri == 8)
		{
			cout << "DO YOU WANT TO PORMOTE YOUR CURRENT PIECE ...?\n";
			cout << "1 = Yes       2 = no \n";
			int option = 0;
			cin >> option;
			if (option == 1)
			{
				cout << "YOUR ROOK HAS BEEN PROMOTED !!!\n";
				B[Sc.ri][Sc.ci] = 'y';
			}
		}
		break;
	}




	}
}
	
// WIN LOSS          check kay bad say moves restrict, msg for check, highlight , undo, reply, graphicx,

position find_king(char** B, int dim , int turn)
{
	position Dc;
	Dc.ri = 0;  // due to error 
	Dc.ci = 0;

	if (turn == white)
	{
		for (int ri = 0; ri < dim; ri++)
		{
			for (int ci = 0; ci < dim; ci++)
			{
				if (B[ri][ci] == 'K')
				{
					Dc.ri = ri;
					Dc.ci = ci;
					return Dc;
				}
			}
		}
	}

	if (turn == black)
	{
		for (int ri = 0; ri < dim; ri++)
		{
			for (int ci = 0; ci < dim; ci++)
			{
				if (B[ri][ci] == 'k')
				{
					Dc.ri = ri;
					Dc.ci = ci;
					return Dc;
				}
			}
		}
	}
}



bool check(char** B, int dim, int &turn)
{
	position Dc = find_king(B, dim, turn);
	turn_Change(turn);
	position Sc;
	for (int ri = 0; ri < dim; ri++)
	{
		for (int ci = 0; ci < dim; ci++)
		{
			Sc.ri = ri;
			Sc.ci = ci;
			
			if (isValid_Selection(B, Sc, dim, turn) && isLegal_Move(B, Sc, Dc, dim, turn))
			{
				cout << "CHECK !!!\n\n";
				//CopyBord(copyB,B, dim);
				turn_Change(turn);
				return true;
			}
			
		}
	}
	return false;
}

bool self_check(char** B, int dim, int& turn)
{
	turn_Change(turn);
	return check(B, dim, turn);

}

bool checkmate(char** B, int dim, int& turn)
{
	if (check(B, dim, turn))
	{
		position Sc, Dc;
		for (int S_ri = 0; S_ri < dim; S_ri++)
		{
			for (int S_ci = 0; S_ci < dim; S_ci++)
			{
				Sc.ri = S_ri;
				Sc.ci = S_ci;
				if (isValid_Selection(B, Sc, dim, turn))
				{
					for (int D_ri = 0; D_ri < dim; D_ri++)
					{
						for (int D_ci = 0; D_ci < dim; D_ci++)
						{
							Dc.ri = D_ri;
							Dc.ci = D_ci;
							if (isValid_Drop(B, Dc, dim, turn) && isLegal_Move(B, Sc, Dc, dim, turn))
							{
								return false;
							}

						}
					}
				}
			}
		}
		return true;
	}
}


void CopyBord(char** B, char** B_Copy, int dim) {

	for (int r = 0; r < dim; r++)
	{
		for (int c = 0; c < dim; c++)
		{
			B_Copy[r][c] = B[r][c];
		}
	}
}

void SaveMove (char**B,int dim)
{
	
		for (int j = 0; j < dim; j++)
		{
			for (int z = 0; z < dim; z++)
			{
				moves[moveCount][j][z]=B[j][z];
			}
		}
		moveCount++;
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

void undoMove(char**& B , int dim) {

		for (int j = 0; j < dim; j++)
		{
			for (int z = 0; z < dim; z++)
			{
				
				B[j][z] = moves[moveCount][j][z];
			}
		}
	}

void save(int dim , char **B)
{
	MyFile.open("load.txt",ios::out);
	string savedata = "";
	for (int i = 0; i < dim; i++) {
			for (int j = 0; j < dim; j++) {
				savedata = savedata + B[i][j];
			}
			savedata = savedata + '\n';

	}
	MyFile <<dim<<endl;
	MyFile << savedata;
	MyFile.close();
}



int main()
{
	int dim, turn = white;
	char** B;
	string Pname[2];
	position Sc, Dc;
	Sc.ri = 0, Sc.ci = 0;
	Dc.ri = 0, Dc.ci = 0;

	cout << "1..NEW GAME ?\n";
	cout << "2..LOAD GAME ?\n";
	int choice = 0;
	cin >> choice;
	init(B, copyB, dim, Pname, turn, choice);

	draw_background(B,dim, sb_size, sb_size);
	while (1)
	{
		turn_msg(Pname, turn);
		do
		{
			do
			{
				do
				{
					do
					{
						do
						{
							//CopyBord(B, copyB, dim);
							select_position(B, Sc, dim, turn);
						} while (!isValid_Selection(B, Sc, dim, turn));
						
						select_desti(B, Dc, dim, turn);
					
					} while (!isValid_Drop(B, Dc, dim, turn));

				} while (!isLegal_Move(B, Sc, Dc, dim, turn));
				 
				 updateBoard(B, Sc, Dc);
			
		} while (check(B, dim, turn));
	} while (self_check(B, dim, turn));
		SaveMove(B,dim);
		turn_msg(Pname, turn);
		promotion(B, Sc, Dc);
		save(dim, B);
		draw_background(B,dim, sb_size, sb_size);
		//printMove(dim);
		//undoMove(B, dim);
		//draw_background(B, dim, sb_size, sb_size);

	}
}








