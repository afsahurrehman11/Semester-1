#include <iostream>
#include <fstream>
using namespace std;

void printArr(int** A, int rows, int columns)
{
    for (int i = 0; rows > i; i++)
    {
        if (A[i] == nullptr)
            continue;
        for (int j = 0; columns > j; j++)
        {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }
}

void printArr2(int** A, int rows, int columns)
{
    for (int i = 0; rows > i; i++)
    {
        for (int j = 0; columns > j; j++)
        {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }

}
int main()
{
    srand(time(0));
    int choice;
    cout << "Enter choice:" << endl;
    cin >> choice;
    if (choice == 1)
    {
        int col[100];
        int row, column;
        int** A;
        cout << "How many rows" << endl;
        cin >> row;
        A = new int* [row];
        for (int i = 0; row > i; i++)
        {
            cout << "How many cols " << endl;
            cin >> column;
            col[i] = column;
            A[i] = new int[column];
            for (int j = 0; column > j; j++)
            {
                A[i][j] = rand() % 100;
            }
        }
        for (int i = 0; row > i; i++)
        {
            for (int j = 0; col[i] > j; j++)
            {
                cout << A[i][j] << " ";
            }
            cout << endl;
        }
    }
    if (choice == 2)
    {
        int row, column;
        int** A;
        cout << "How many rows" << endl;
        cin >> row;
        cout << "How many columns" << endl;
        cin >> column;
        A = new int* [row];
        for (int i = 0; row > i; i++)
        {
            A[i] = new int[column];
            for (int j = 0; column > j; j++)
            {
                A[i][j] = rand() % 100;
            }
        }
        printArr(A, row, column);
        cout << endl;
        cout << "Del row number  " << endl;
        int delR; cin >> delR;
        delete[]A[delR];
        A[delR] = nullptr;
        printArr(A, row, column);
    }
    if (choice == 3)
    {
        int col[100];
        int row, column;
        int** A;
        cout << "How many rows" << endl;
        cin >> row;
        cout << "How many columns" << endl;
        cin >> column;
        for (int i = 0; row > i; i++)
        {
            col[i] = column;
        }
        A = new int* [row];
        for (int i = 0; row > i; i++)
        {
            A[i] = new int[column];
            for (int j = 0; column > j; j++)
            {
                A[i][j] = rand() % 100;
            }
        }
        printArr(A, row, column);
        int Dro, Dco;


        int count = 0;
        int col2[100];
        cout << "which to del rows" << endl;
        cin >> Dro;
        cout << "Which to del columns" << endl;
        cin >> Dco;
        int** a;
        a = new int* [row];

        for (int i = 0; row > i; i++)
        {
            if (i == Dro)
            {
                int g = col[i] - 1;
                col2[i] = g;
                a[i] = new int[g];
            }
            else
            {
                col2[i] = col[i];
                a[i] = new int[col[i]];
            }
            for (int j = 0; col[i] > j; j++)
            {
                if (i == Dro)
                {
                    if (i == Dro && j == Dco)
                    {
                        count++;
                    }
                    else if (count > 0)
                    {
                        a[i][j - 1] = A[i][j];
                    }
                    else
                        a[i][j] = A[i][j];
                }
                else
                {
                    a[i][j] = A[i][j];
                }
            }
        }
        for (int i = 0; row > i; i++)
        {
            for (int j = 0; col2[i] > j; j++)
            {
                cout << a[i][j] << " ";
            }
            cout << endl;
        }
    }
    if (choice == 4)
    {
        ofstream writer("Text.txt");
        int r, c;
        cout << "Enter row col "; cin >> r; cin >> c;
        writer << r << " " << c << endl;
        int** A;
        A = new int* [r];
        for (int i = 0; i < r; i++)
        {
            A[i] = new int[c];
        }
        for (int i = 0; i < r; i++)
        {
            for (int j = 0; j < c; j++)
            {
                A[i][j] = rand() % 10;
            }
        }
        for (int i = 0; i < r; i++)
        {
            for (int j = 0; j < c; j++)
            {
                writer << A[i][j] << " ";
            }
            writer << endl;
        }
    }
    if (choice == 5)
    {
        int r = 5;
        int c = 5, x = 5;
        int*** P;
        P = new int** [r];
        for (int i = 0; r > i; i++)
        {
            P[i] = new int* [c - i];
        }
        for (int i = 0; c > i; i++)
        {
            {
                for (int j = 0; x > j; j++)
                {
                    P[i][j] = new int[x - j];
                }
            }
        }
    }
}