#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <tr1/unordered_set>

//#define DEBUG

#ifdef DEBUG
	#define P_DEBUG(x) x
#else
	#define P_DEBUG(x)
#endif

using namespace std;
using tr1::unordered_set;

struct HashOperator {
    int operator()(const vector<int> &V) const {
        int hash = V.size();
        for(unsigned int i = 0; i < V.size(); i++) {
            hash += V[i] * ((hash >> 4) + (hash << 2));
        }
        //cout << hash << endl;
        return hash;
    }
};

unordered_set <vector <int>, HashOperator> hash;

bool Verify_Seq(vector<int> Proc_Seq, vector<int> &(Drv_Seq), unordered_set < vector<int> > &Folds);
vector<int> Fold_Array(vector<int> Proc_Array, int Index);
void Vector_Print(vector <int> const &a);

//==================================================================================================================================

void Vector_Print(vector <int> const &a) 
{
	cout << "The vector elements are : ";

	for(int i = 0; i < (int) a.size(); i++)
		cout << a.at(i) << ' ';

	cout << endl;
}

//-------------------------------------------------------------------------------------------------------------------

bool Verify_Seq(vector<int> Proc_Seq, vector<int> &(Drv_Seq), unordered_set < vector<int>, HashOperator > &Folds)
{
	Folds.insert(Proc_Seq);
	bool Result = false;

	if (Proc_Seq == Drv_Seq)
		return true;

	if (Proc_Seq.size() == 1)
		return false;

	for (int i = 0; i < (int) Proc_Seq.size() && Result == false; i++)
	{
		vector<int> Next_Array = Fold_Array(Proc_Seq, i);
		//Vector_Print(Next_Array);
		if (Folds.find(Next_Array) == Folds.end())
			Result = Result | Verify_Seq(Next_Array, Drv_Seq, Folds);
	}

	return Result;
}

//------------------------------------------------------------------------------------------------------------------------

vector<int> Fold_Array(vector<int> Proc_Array, int Index)
{
	vector<int> Second_Part, Res_Array;	
	int Diff;

	if (Proc_Array.size() == 1) 
		return Proc_Array;

	if (Index == 0 or Index == (int) Proc_Array.size())
		Res_Array = vector <int> (Proc_Array.rbegin(), Proc_Array.rend());

	vector<int> First_Part (Proc_Array.begin(), Proc_Array.begin()+Index);
	P_DEBUG(Vector_Print(First_Part));
	Second_Part = vector <int> (Proc_Array.rbegin(), Proc_Array.rend()-Index);
	P_DEBUG(Vector_Print(Second_Part));

	if (First_Part.size() >= Second_Part.size())
	{
		Diff = First_Part.size() - Second_Part.size();
		if (Diff > 0)
			Res_Array = vector<int> (First_Part.begin(), First_Part.begin() + Diff);
		for (int i = 0; i < (int) Second_Part.size(); i++)
			Res_Array.push_back(First_Part[i+Diff] + Second_Part[i]);
	}
	else
	{
		Diff = Second_Part.size() - First_Part.size();
		if (Diff > 0)
			Res_Array = vector<int> (Second_Part.begin(), Second_Part.begin() + Diff);
		for (int i = 0; i < (int) First_Part.size(); i++)
			Res_Array.push_back(First_Part[i] + Second_Part[i+Diff]);
	}

	return Res_Array;
}

//==================================================================================================================================

int main ()
{
	int Org_Size, Drv_Size;
	vector<int> Org_Seq, Drv_Seq;
	int Current_Input;
	unordered_set < vector<int>, HashOperator > Folds;

	cin >> Org_Size;
	for (int i = 0; i < Org_Size; i++)
	{
		cin >> Current_Input;
		Org_Seq.push_back(Current_Input);
	}

	cin >> Drv_Size;
	for (int i = 0; i < Drv_Size; i++)
	{
		cin >> Current_Input;
		Drv_Seq.push_back(Current_Input);
	}

	Verify_Seq(Org_Seq, Drv_Seq, Folds) ? printf("S\n") : printf("N\n");

    return 0;
}
