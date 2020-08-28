#include <iostream>
#include <utility>

//#define DEBUG

#ifdef DEBUG
	#define P_DEBUG(x) x
#else
	#define P_DEBUG(x)
#endif

using namespace std;

int Calc_Row(short int (&Matrix)[1025][1025], int X, int Dist);
int Calc_Column(short int (&Matrix)[1025][1025], int X, int Sq_Y_Start, int Sq_Y_End);
pair < pair <int, int>, int > Square_Sum(short int (&Matrix)[1025][1025], int Dist, int Max_X, int Max_Y);

//==================================================================================================================================

pair < pair <int, int>, int > Square_Sum(short int (&Matrix)[1025][1025], int Dist, int Max_X, int Max_Y)
{
    int Border_Start = Dist,
        Border_End =  1024 - Dist;
    int Final_X = 0, Final_Y = 0, Max_Sum = 0, Current_Sum = 0, Iter_Sum = 0;

    int Sq_X_Start = 0,
        Sq_X_End = Border_Start + Dist,
        Sq_Y_Start = 0,
        Sq_Y_End = Border_Start + Dist;

    for (int i = 0; i <= Sq_X_End; i++)
    {
        for (int j = 0; j <= Sq_Y_End; j++)
        {
            Current_Sum += Matrix[i][j];
        }
    }

    Max_Sum = Iter_Sum = Current_Sum;
    Final_X = Final_Y = Border_Start;

    for (int Pos_X = Border_Start; Pos_X <= Border_End; Pos_X++)
    {
        Sq_X_Start = Pos_X - Dist;
        Sq_X_End = Pos_X + Dist;


        if (Pos_X != Border_Start)
        {
            Current_Sum = Iter_Sum;

            Current_Sum -= Calc_Row(Matrix, Sq_X_Start-1, Dist);
            Current_Sum += Calc_Row(Matrix, Sq_X_End, Dist);

            Iter_Sum = Current_Sum;
        }

        if (Current_Sum > Max_Sum)
        {
            Max_Sum = Current_Sum;
            Final_X = Pos_X;
            Final_Y = Border_Start;
        }


        for (int Pos_Y = Border_Start + 1; Pos_Y <= Border_End; Pos_Y++)
        {
            
            Sq_Y_Start = Pos_Y - Dist,
            Sq_Y_End = Pos_Y + Dist;

            Current_Sum -= Calc_Column(Matrix, Sq_Y_Start-1, Sq_X_Start, Sq_X_End);
            Current_Sum += Calc_Column(Matrix, Sq_Y_End, Sq_X_Start, Sq_X_End);

            if (Current_Sum > Max_Sum)
            {
                Max_Sum = Current_Sum;
                Final_X = Pos_X;
                Final_Y = Pos_Y;
            }

            if (Pos_Y >= Max_Y) break;
            
        }

        if (Pos_X >= Max_X) break;
    }

    pair <int, int> Coord (Final_X, Final_Y);
    pair < pair <int, int>, int > Solution (Coord, Max_Sum);

    return Solution;

}

//----------------------------------------------------------------------------------------

int Calc_Row(short int (&Matrix)[1025][1025], int X, int Dist)
{
    int Sum = 0;
    for (int i = 0; i <= 2*Dist; i++)
    {
        Sum += Matrix[X][i];
    }

    return Sum;
}

//----------------------------------------------------------------------------------------

int Calc_Column(short int (&Matrix)[1025][1025], int Y, int Sq_X_Start, int Sq_X_End)
{
    int Sum = 0;
    for (int i = Sq_X_Start; i <= Sq_X_End; i++)
    {
        Sum += Matrix[i][Y];
    }

    return Sum;
}

//==================================================================================================================================

int main ()
{
	int Dist, i, Qty;
    int X, Y, Num, Max_X = 0, Max_Y = 0;
    short int Matrix[1025][1025];

	cin >> Dist;

    cin >> Qty;

    for (int i = 0; i < 1025; i++)
    {
        for (int j = 0; j < 1025; j++)
        {
            Matrix[i][j] = 0;
        }
    }

    pair <int, int> Pos (Dist, Dist);
    pair <int, int> Final (Dist, Dist);

    for (i=0; i < Qty; i++)
    {
        cin >> X >> Y >> Num;
        Matrix[X][Y] = Num;

        if (X > Max_X) Max_X = X;
        if (Y > Max_Y) Max_Y = Y;
    }

    pair< pair<int, int>, int > Result = Square_Sum(Matrix, Dist, Max_X, Max_Y);

    cout << Result.first.first << ' ' << Result.first.second << ' ' << Result.second << endl;

    return 0;
}
