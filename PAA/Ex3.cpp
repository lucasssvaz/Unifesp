#include <iostream>
#include <stack>
#include <vector>
#include <utility>
#include <iterator>

#define WALL 2
#define VISITED 1
#define UNVISITED 0

using namespace std;

int Next_Pos (stack < pair <int, int> > &P_Stack, pair <int, int> Current)
{
	pair <int, int> New_Pos;

	int Count = 0;

	New_Pos = make_pair(Current.first-2, Current.second-1);
	if ((New_Pos.first >= 0 && New_Pos.first < 10) && (New_Pos.second >= 0 && New_Pos.second <= 10)){
		P_Stack.push(New_Pos);
		Count++;
	}
	New_Pos = make_pair(Current.first-1, Current.second-2);
	if ((New_Pos.first >= 0 && New_Pos.first < 10) && (New_Pos.second >= 0 && New_Pos.second <= 10)){
		P_Stack.push(New_Pos);
		Count++;
	}
	New_Pos = make_pair(Current.first+1, Current.second-2);
	if ((New_Pos.first >= 0 && New_Pos.first < 10) && (New_Pos.second >= 0 && New_Pos.second <= 10)){
		P_Stack.push(New_Pos);
		Count++;
	}
	New_Pos = make_pair(Current.first+2, Current.second-1);
	if ((New_Pos.first >= 0 && New_Pos.first < 10) && (New_Pos.second >= 0 && New_Pos.second <= 10)){
		P_Stack.push(New_Pos);
		Count++;
	}
	New_Pos = make_pair(Current.first-2, Current.second+1);
	if ((New_Pos.first >= 0 && New_Pos.first < 10) && (New_Pos.second >= 0 && New_Pos.second <= 10)){
		P_Stack.push(New_Pos);
		Count++;
	}
	New_Pos = make_pair(Current.first-1, Current.second+2);
	if ((New_Pos.first >= 0 && New_Pos.first < 10) && (New_Pos.second >= 0 && New_Pos.second <= 10)){
		P_Stack.push(New_Pos);
		Count++;
	}
	New_Pos = make_pair(Current.first+1, Current.second+2);
	if ((New_Pos.first >= 0 && New_Pos.first < 10) && (New_Pos.second >= 0 && New_Pos.second <= 10)){
		P_Stack.push(New_Pos);
		Count++;
	}
	New_Pos = make_pair(Current.first+2, Current.second+1);
	if ((New_Pos.first >= 0 && New_Pos.first < 10) && (New_Pos.second >= 0 && New_Pos.second <= 10)){
		P_Stack.push(New_Pos);
		Count++;
	}

	return Count;
}

void Print_Matrix (vector< vector<int> > &M)
{
    int i;

    for (i = 0; i < 10; i++){
        copy(M[i].begin(), M[i].end(), ostream_iterator<int>(cout," "));
        cout << "\n";
    }

    cout << endl;
}

void Matrix_Trace (vector< vector<int> > &Matrix, vector< vector<int> > &Visited, stack < pair <int, int> > &P_Stack, int &C_Depth, int &Max_Depth)
{
	pair <int, int> Current;
	int i;

	Current = P_Stack.top();
	P_Stack.pop();

	if (Matrix[Current.first][Current.second] == WALL || Matrix[Current.first][Current.second] == VISITED)
	{
		return;
	}

    C_Depth++;

	Matrix[Current.first][Current.second] = VISITED;

	if (C_Depth > Max_Depth)
	{
        Visited = Matrix;
        Max_Depth = C_Depth;
	}

	int Count = Next_Pos(P_Stack, Current);

	for (i = 0; i < Count; i++)
	{
		Matrix_Trace(Matrix, Visited, P_Stack, C_Depth, Max_Depth);
	}

	Matrix[Current.first][Current.second] = UNVISITED;
	C_Depth--;

}

int Count_Unvisited (vector< vector<int> > &Visited)
{
    int Count = 0;
    int i, j;

    for (i = 0; i < 10; i++)
        for(j = 0; j < 11; j++)
            if (Visited[i][j] == 0)
                Count++;

    return Count;
}

int main()
{
    vector< vector<int> > Matrix(10, vector<int>(11, WALL));
    int C_Depth = 0, Max_Depth = 0;
    int row, i = 0, Line_End, Line_Begin;

    stack < pair <int, int> > P_Stack;

    pair <int, int> Pos (0, 0);

    P_Stack.push(Pos);

    cin >> row;

    do
    {
        cin >> Line_Begin >> Line_End;

        fill(Matrix[i].begin() + Line_Begin, Matrix[i].begin() + Line_Begin + Line_End, UNVISITED);

        i++;
    } while (i < row);

    vector< vector<int> > Visited = Matrix;

    //Print_Matrix(Matrix);

    Matrix_Trace(Matrix, Visited, P_Stack, C_Depth, Max_Depth);

    //Print_Matrix(Visited);

    cout << Count_Unvisited(Visited) << endl;

    return 0;
}
