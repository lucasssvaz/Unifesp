#include <iostream>

//#define DEBUG

#ifdef DEBUG
	#define P_DEBUG(x) x
#else
	#define P_DEBUG(x)
#endif

using namespace std;

int MaxProfit (int *V, int N_Days, int Tax);

//==================================================================================================================================

int MaxProfit (int *V, int N_Days, int Tax)
{
	int Current_Sum = 0, Max_Sum = 0;

	for (int i = 0; i < N_Days; i++)
	{
		Current_Sum = Current_Sum + V[i] - Tax;

		if (Current_Sum > Max_Sum)
			Max_Sum = Current_Sum;

		if (Current_Sum < 0)
			Current_Sum = 0;

	}

	return Max_Sum;
}

//==================================================================================================================================

int main ()
{
	int N_Days, Tax;
	int *V;

	cin >> N_Days >> Tax;

	V = new (nothrow) int [N_Days];

	if (V == NULL) cout << "Allocation Error!" << endl;

	for (int i = 0; i < N_Days; i++)
		cin >> V[i];

	int Sum = MaxProfit(V, N_Days, Tax);

	cout << Sum << endl;

	delete[] V;
    return 0;
}
