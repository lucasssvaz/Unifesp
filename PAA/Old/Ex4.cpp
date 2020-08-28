#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <string>

using namespace std;

typedef struct {
	bool Mutator;
	char Op;
	int Count;
} Cell;

inline char isMutator(Cell Current)
{
	return Current.Mutator ? '*' : ' ';
}

void Print_Matrix(vector < vector<Cell> > Matrix, int M_Size, string Input, string Rev_Input){
	
	cout << "  |  |";

	for (int i = 0; i < M_Size-1; i++)
		cout << Input[i] << isMutator(Matrix[i+1][0]) << "|";

	cout << endl << "  |";

	for (int i = 0; i < M_Size; i++)
	{
		cout << "  |";
	}

	cout << endl;

	for (int i = 0; i < 3*(M_Size+1); ++i)
		cout << '-';

	cout << endl;

	for (int i = 0; i < M_Size; ++i)
	{
		
	}

}

void Search(vector < vector<Cell> > &Matrix, int x_pos, int y_pos, int &MaxCount, int &MaxMut, string &Result, string &Input)
{
	int Cur_Count = Matrix[x_pos][y_pos].Count;
	int Cur_Mut = 0;
	string Cur_Result;

	while (Matrix[x_pos][y_pos].Op != '*')
	{
		switch (Matrix[x_pos][y_pos].Op)
		{
			case '\\':
				if (Matrix[x_pos][y_pos].Mutator == true)
				{
					Cur_Mut++;
				}
				Cur_Result.append(Input,x_pos-1,1);
				x_pos-=1;
				y_pos-=1;
				break;

			case '-':
				x_pos-=1;
				break;

			case '|':
				y_pos-=1;
				break;
		}
	}

	if (Cur_Mut == MaxMut)
	{
		if (Cur_Count > MaxCount){
			MaxCount = Cur_Count;
			Result = Cur_Result;
		}

	}
	else if (Cur_Mut > MaxMut)
	{
		MaxMut = Cur_Mut;
		MaxCount = Cur_Count;
		Result = Cur_Result;
	}

}

int Solve(vector < vector<Cell> > &Matrix, int M_Size, string &Input, string &Rev_Input, int N)
{
	int MaxMut = 0;
	int MaxCount = 0;
	int x_pos, y_pos;
	string Result;

	for (int i = 1; i < M_Size; i++)
	{
		for (int j = 1; j < M_Size; j++)
		{
			if (Input[i-1] == Rev_Input[j-1])
			{
				Matrix[i][j].Count = Matrix[i-1][j-1].Count + 1;
				Matrix[i][j].Op = '\\';
			}
			else if (Matrix[i-1][j].Count >= Matrix[i][j-1].Count)
			{
				Matrix[i][j].Count = Matrix[i-1][j].Count;
				Matrix[i][j].Op = '|';
			}
			else
			{
				Matrix[i][j].Count = Matrix[i][j-1].Count;
				Matrix[i][j].Op = '-';
			}
		}
	}

	if (N == 0)
	{
		MaxCount = Matrix[M_Size-1][M_Size-1].Count;
	}
	else
	{
		for (int i = 1; i < M_Size; ++i)
		{
			x_pos = i;
			y_pos = M_Size-1;
			Search(Matrix, x_pos , y_pos, MaxCount, MaxMut, Result, Input);
		}

		for (int i = 1; i < M_Size-1; ++i)
		{
			x_pos = M_Size-1;
			y_pos = i;
			Search(Matrix, x_pos , y_pos, MaxCount, MaxMut, Result, Input);
		}
	}

	//cout << endl << Result << endl;

	return MaxCount;
}

int main()
{
	int N, M_Pos;
	string Input, Rev_Input;
	
	cin >> Input;
	cin >> N;

	Rev_Input = Input;
	reverse(Rev_Input.begin(), Rev_Input.end());

	//cout << endl << Input << endl << Rev_Input << endl;

	int M_Size = Input.length() + 1;

	vector < vector<Cell> > Matrix(M_Size, vector<Cell>(M_Size));

	for (int i = 0; i < M_Size; i++)
	{
		for (int j = 0; j < M_Size; j++)
		{
			Matrix[i][j].Mutator = false;
			Matrix[i][j].Op = '*';
			Matrix[i][j].Count = 0;
		}
	}

	for (int i = 0; i < N; i++)
	{
		cin >> M_Pos;
		
		for (int k = 1; k < M_Size ; ++k)
		{
			Matrix[M_Pos][k].Mutator = true;
		}

		for (int k = 1; k < M_Size ; ++k)
		{
			Matrix[k][M_Size-M_Pos].Mutator = true;
		}
	}

	cout << Solve(Matrix, M_Size, Input, Rev_Input, N) << endl;

	return 0;
}