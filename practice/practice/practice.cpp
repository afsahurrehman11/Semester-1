#include<iostream >
#include<Windows.h>
using namespace std;


int countLiveCells(int** data, int rows, int cols, int k, cord* xy)
{
	bool Notalive = false;
	int count = 0;
	for (int ri = 0; ri <= rows - k; ri++) //2
	{
		for (int ci = 0; ci <= cols - k; ci++)//1
		{
			int i = ci;
			for (; i < ci + k; i++) //0-2
			{
				if (data[ri][i] != 1) //r=0
				{
					Notalive = true;
				}
			}
			i--;//2
			int j = ri;//0
			for (; j < ri + k; j++)//0-2
			{
				if (data[j][i] != 1)
					Notalive = true;
			}
			j--;//2
			for (; i >= ci; i--) //2-0
			{	
				if (data[j][i] != 1)
					Notalive = true;
			}
			i++;//0
			for (; j >= ri; j--) //2-0
			{
				if (data[j][i] != 1)
					Notalive = true;
			}
			j++;//0
			if (!Notalive)
			{
				xy[count].r = j;
				xy[count].c = i;
				count++;
			}

			Notalive = false;
		}
	}
	return count;
}

int main()
{
	


}