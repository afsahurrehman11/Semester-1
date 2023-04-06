#include <iostream>
#include <fstream>
#include <conio.h>
using namespace std;

struct Polynomials
{
    int d;
    int* Cs;
};

void LoadPs(const char* fname, int& size, Polynomials*& Ps)
{
    ifstream Rdr(fname);
    Rdr >> size;
    char ch;
    Ps = new Polynomials[size]{};
    for (int pi = 0; pi < size; pi++)
    {
        Rdr >> Ps[pi].d >> ch;
        int deg = Ps[pi].d;
        Ps[pi].Cs = new int[deg + 1];
        for (int vi = 0, ci = deg; vi < deg + 1; vi++, ci--)
        {
            Rdr >> Ps[pi].Cs[ci];
        }
    }
}

int coefficientAt(Polynomials P, int i)
{
    if (P.d >= i)
        return P.Cs[i];
    else
        return 0;
}

Polynomials Add(Polynomials P1, Polynomials P2)
{
    Polynomials R;
    R.d = max(P1.d, P2.d);
    R.Cs = new int[R.d + 1];

    for (int i = 0; i < R.d + 1; i++)
    {
        int P1_c = coefficientAt(P1, i);
        int P2_c = coefficientAt(P2, i);
        R.Cs[i] = P1_c + P2_c;
    }
    return R;
}

Polynomials Subtract(Polynomials P1, Polynomials P2)
{
    Polynomials R;
    R.d = max(P1.d, P2.d);
    R.Cs = new int[R.d + 1];

    for (int i = 0; i < R.d + 1; i++)
    {
        int P1_c = coefficientAt(P1, i);
        int P2_c = coefficientAt(P2, i);
        R.Cs[i] = P1_c - P2_c;
    }
    return R;
}

int Evaluate(Polynomials P1, int x)
{
    int R = 0;
    int deg = P1.d;

    for (int i = deg, d = deg; i >= 0; d--, i--)
    {
        int a = 1;
        int P1_c = coefficientAt(P1, i);
        for (int p = d; p > 0; p--)
        {
            a *= x;
        }
        R += P1_c * a;
    }
    return R;
}

Polynomials Derivative(Polynomials P1)
{
    Polynomials R;
    int deg = P1.d;
    R.d = deg;
    R.Cs = new int[deg + 1];
    for (int i = deg, d = deg; i >= 0; d--, i--)
    {
        int P1_c = coefficientAt(P1, i);
        R.Cs[i] = P1_c * d;
    }
    return R;
}

Polynomials Integral(Polynomials P1)
{
    Polynomials R;
    float a;
    int deg = P1.d;
    R.d = deg;
    R.Cs = new int[deg + 1];
    for (int i = deg, d = deg + 1; i >= 0; d--, i--)
    {
        int P1_c = coefficientAt(P1, i);
        a = P1_c / d;
        R.Cs[i] = a;
    }
    return R;
}

void print(Polynomials* Ps, int size, int count, int ch)
{
    for (int pi = 0; pi <= size; pi++)
    {
        if (count == 2)
        {
            if (pi != size)
            {
                cout << "P" << pi + 1 << "(X): ";
            }
            else
            {
                cout << endl;
                for (int i = 0; i < size; i++)
                {
                    cout << "P" << i + 1;
                    if (ch == 1)
                        if (i < size - 1)
                            cout << "+";
                    if (ch == 2)
                        if (i < size - 1)
                            cout << "-";

                }
                cout << ": ";
            }
        }
        else
            cout << "P" << pi + 1 << "(X): ";
        int deg = Ps[pi].d;
        for (int ci = 0, p = deg; ci < deg + 1; ci++, p--)
        {
            if (Ps[pi].Cs[p] > 0)
            {
                if (ci != 0)
                    cout << "+";
                if (Ps[pi].Cs[p] > 1)
                    cout << Ps[pi].Cs[p];
                if (p > 1)
                    cout << "X^" << p;
                else if (p > 0)
                    cout << "X";
            }
            else if (Ps[pi].Cs[p] < 0)
            {
                if (Ps[pi].Cs[p] < -1)
                    cout << Ps[pi].Cs[p];
                else if (Ps[pi].Cs[p] == -1)
                    cout << "-";
                if (p > 1)
                    cout << "X^" << p;
                else if (p > 0 && ch != 4)
                    cout << "X";
            }
        }
        cout << endl;
    }
}

void Print_Dev(Polynomials* Ps, int size, int ch)
{
    for (int pi = 0; pi < size; pi++)
    {
        cout << "f'" << pi + 1 << "(X): ";
        int deg = Ps[pi].d;
        for (int ci = 0, p = deg, uci = deg - 1; ci < deg + 1; ci++, p--, uci--)
        {
            if (Ps[pi].Cs[p] > 0)
            {
                if (ci != 0)
                    cout << "+";
                if (Ps[pi].Cs[p] > 1)
                    cout << Ps[pi].Cs[p];
                if (p == 0)
                    cout << Ps[pi].Cs[p];
                else if (uci > 1)
                    cout << "X^" << uci;
                else if (uci == 1)
                    cout << "X";
            }
            else if (Ps[pi].Cs[p] < 0)
            {
                if (Ps[pi].Cs[p] < -1)
                    cout << Ps[pi].Cs[p];
                else if (Ps[pi].Cs[p] == -1)
                    if (p == 1)
                        cout << Ps[pi].Cs[p];
                    else
                        cout << "-";
                if (p == 0)
                    cout << Ps[pi].Cs[p];
                else if (uci > 1)
                    cout << "X^" << uci;
                else if (uci == 1)
                    cout << "X";
            }
        }
        cout << endl;
    }
}

void Print_Int(Polynomials* Ps, int size, int ch)
{
    for (int pi = 0; pi < size; pi++)
    {
        cout << "f'" << pi + 1 << "(X): ";
        int deg = Ps[pi].d;
        for (int ci = 0, p = deg, uci = deg + 1; ci < deg + 1; ci++, p--, uci--)
        {
            if (Ps[pi].Cs[p] > 0)
            {
                if (ci != 0)
                    cout << "+";
                if (Ps[pi].Cs[p] > 1)
                    cout << Ps[pi].Cs[p];
                if (p == 0)
                    cout << "X";
                else if (uci > 1)
                    cout << "X^" << uci;
                else if (uci > 0)
                    cout << "X";
            }
            else if (Ps[pi].Cs[p] < 0)
            {
                if (Ps[pi].Cs[p] < -1)
                    cout << Ps[pi].Cs[p];
                else if (Ps[pi].Cs[p] == -1)
                    cout << "-";
                if (p == 0)
                    cout << "X";
                else if (uci > 1)
                    cout << "X^" << uci;
                else if (uci > 0)
                    cout << "X";
            }
        }
        cout << endl;
    }
}

int main()
{
    Polynomials* Ps;
    int size, count = 0;
    LoadPs("Text.txtt", size, Ps);
    count++;
    print(Ps, size - 1, count, choice);
    cout << endl << endl << endl;
    count++;
    for (int i = 0; i < size; i++)
    {
        Ps[size] = Add(Ps[i], Ps[size]);
    }
    print(Ps, size, count, choice);

    return _getch();
}

int main2(int choice)
{
    Polynomials* Ps;
    int size, count = 0;
    LoadPs("Text.txt", size, Ps);
    count++;
    print(Ps, size - 1, count, choice);
    cout << endl << endl << endl;
    count++;
    for (int i = 0; i < size; i++)
    {
        Ps[i + 1] = Subtract(Ps[i], Ps[i + 1]);
    }
    print(Ps, size, count, choice);

    return _getch();
}

int main3(int choice)
{
    Polynomials* Ps;
    int size, count = 0;
    LoadPs("Text.txt", size, Ps);
    count++;
    int x;
    cout << "Enter value of X: ";
    cin >> x;
    cout << endl;
    print(Ps, size - 1, count, choice);
    cout << endl << endl << endl;
    count++;
    for (int i = 0; i < size; i++)
    {
        int R = Evaluate(Ps[i], x);
        cout << "F" << i + 1 << "(" << x << ") : " << R << endl;
    }
    cout << endl << endl << endl;

    return _getch();
}

int main4(int choice)
{
    Polynomials* Ps;
    int size, count = 0;
    LoadPs("Text.txt", size, Ps);
    count++;
    print(Ps, size - 1, count, choice);
    cout << endl << endl << endl;
    count++;
    for (int i = 0; i < size; i++)
    {
        Ps[i] = Derivative(Ps[i]);
    }
    Print_Dev(Ps, size, choice);

    return _getch();
}

int main5(int choice)
{
    Polynomials* Ps;
    int size, count = 0;
    LoadPs("Text.txt", size, Ps);
    count++;
    print(Ps, size - 1, count, choice);
    cout << endl << endl << endl;
    count++;
    for (int i = 0; i < size; i++)
    {
        Ps[i] = Integral(Ps[i]);
    }
    Print_Int(Ps, size, choice);

    return _getch();
}

