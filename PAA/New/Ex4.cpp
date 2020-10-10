#include <iostream>
#include <vector>
#include <iterator>

//#define DEBUG

#ifdef DEBUG
	#define P_DEBUG(x) x
#else
	#define P_DEBUG(x)
#endif

using namespace std;

int Calc_Cost(int N, vector<int> Houses, int Ant1, int Ant2, vector<int> &Result_Table, int Sum);

//==================================================================================================================================

int Calc_Cost(int N, vector<int> Houses, int Ant1, int Ant2, vector<int> &Result_Table, int Sum)
{
	vector<int> Aux;
	int Sum_Ant1, Sum_Ant2;

	if (Houses.empty())
		return 0;

	Aux = Houses;

	if (Result_Table[Houses.size()-1] != -1)
		Sum += Result_Table[Houses.size()-1];
	else
	{
		if (Houses.size() == 1)
		{
			Sum += Ant1;
			Result_Table[0] = Sum;
		}
		else
		{
			int Start = Aux[0];
			while(Aux[0] <= Start + Ant1)
			{
				Aux.erase(Aux.begin());
				if (Aux.empty())
					break;
			}

			Sum_Ant1 = Sum + Ant1 + Calc_Cost(N, Aux, Ant1, Ant2, Result_Table, Sum);
			
			Aux = Houses;
			while(Aux[0] <= Start + Ant2)
			{
				Aux.erase(Aux.begin());
				if (Aux.empty())
					break;
			}

			Sum_Ant2 = Sum + Ant2 + Calc_Cost(N, Aux, Ant1, Ant2, Result_Table, Sum);

			Sum = min(Sum_Ant1, Sum_Ant2);
			Result_Table[Houses.size()-1] = Sum;
		}
	}

	
	return Sum;
}

//==================================================================================================================================

int main()
{
	int N, St_Len, Ant1, Ant2, input;
	vector<int> Houses;
	vector<int> Result_Table (N, -1);

	cin >> N >> St_Len >> Ant1 >> Ant2;

	if (Ant1 > Ant2) swap(Ant1, Ant2);

	for (int i = 0; i < N; i++)
	{
		cin >> input;
		Houses.push_back(input);
	}

	int Result = Calc_Cost(N, Houses, Ant1, Ant2, Result_Table, 0);

	cout << Result << endl;

    return 0;
}
