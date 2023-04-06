#include<iostream>
#include<fstream>
using namespace std;

const int capacity = 100;


// ------------------------------- KEY -------------------------------------
//    alpha = 27 : (26 alpha + 1 for space char)  
//    code = 12 : {hexa code(2) , binary code(8) , /0} 
//    binC = binary code , hexaC = hexa code

void noConv_b2H_and_alpha( char table[][capacity],int alpha ,int code, string input, string &hexa, string &Word)// reinitilize single word // si ei // check circulation 
{
	int si = 0, ei = 0;  

	while (true)
	{

		//--->>> reading every 8 elements 
		char Sw[8] = {};                        // Sw = single word 
		int idx_1 = 0;

		for (int i = si; i < ei; i++, idx_1++)
		{
			Sw[idx_1] = input[i];              // Sw = {0,1,0,1,0,1,0,1}
		}

		int target = 0;
		check_binC(table, Sw, alpha, code, target);    // no concern with T || F we just want target 

		// now we have that char index in target which binC was in Sw

		// to get hexaC and char for that binC in Sw
		hexa = table[target][0] + table[target][1];     // as 1st 2 idx have hexa code
		Word = table[target];

		// for circulation of code i.e to get hexa and char for entier input 
		if (ei == input.length()-1)   // due to /0 
		{
			return;
		}
		else
		{
			si = ei;
			ei = ei + 8;
		}
		
	}
	
}


bool check_binC(char table[][capacity], char Sw[8],int alpha, int code,int& target)
{
	//--->>> to detrmine which Bin code is inn Sw 
	int idx_2 = 0;
	bool flag;
	for (int i = 0; i < alpha; i++)
	{
		flag = true;
		for (int j = 2; j < code; j++, idx_2++)
		{
			if (Sw[idx_2] != table[i][j])
			{
				flag = false;
			}
		}

		if (flag == true)
		{
			target = i;
			return true;
		}

	}
	return false;

}




void alpha_to_hexa_bin_Conver(ASCII table[27], string input, string& hexa, string& bin_C)
{
	int target = 0;
	int idx = 0;
	char single_word = ' ';
	while (single_word != '/0')
	{
		target = 0;

		single_word = input[idx];
		// determing that letter 
		for (int i = 0; i < 27; i++)
		{
			if (table[i].S == single_word)
			{
				target = i;
			}
		}


		int j = 0;
		while (table[target].HexCode[j] != '/0')
		{
			hexa =table[target].HexCode[j];

		}

		int z = 0;
		while (table[target].BCode[z] != '/0')
		{
			bin_C =  table[target].BCode[z];

		}

	}
}






















void alpha_to_hexa_bin_Conver(char table[][capacity], int alpha, int code, string input, string& hexa, string &binC)
{
	char single_word = ' ';          // picking up one word each time 
	int idx = 0;
	while (single_word != '/ 0')
	{
		single_word=input[idx];
		
		// searching which letter is in single_word
		for (int i = 0; i < alpha; i++)
		{
			char sym_in_tab= table[i][0];
			if (single_word == sym_in_tab);
		}



	}


}




