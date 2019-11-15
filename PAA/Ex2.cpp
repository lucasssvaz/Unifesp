#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <iterator>

//#define DEBUG

#ifdef DEBUG
	#define P_DEBUG(x) x
#else
	#define P_DEBUG(x)
#endif

using namespace std;

class Graph
{
    vector< vector<int> > Adj_List;
    int N_Nodes;

    public:

    Graph (int N);
    inline void Insert_Edge (int S, int T);
    void Print_Graph ();
    void DFS_Rec(int V, vector<bool> &Visited, vector<int> &Sub);
    void Kosaraju ();
    Graph Transpose();
    void Fill_Stack(int V, vector<bool> &Visited, stack<int> &S);
};

//=============================================================================================================

Graph::Graph (int N)
{
    this->N_Nodes = N;
    Adj_List.resize(N);
}

//--------------------------------------------------------------------------------------------------

inline void Graph::Insert_Edge (int S, int T)
{
    if (S >= this->N_Nodes || T >= this->N_Nodes)
    {
        P_DEBUG(cout << "Error inserting edge " << S-1 << "->" << T-1 << ". Invalid Node Selected. Nodes must be greater than 0 and less than " << (this->N_Nodes) << "." << endl);
        exit(-1);
    }    
    else
        this->Adj_List[S].push_back(T);
}

//--------------------------------------------------------------------------------------------------

void Graph::DFS_Rec(int V, vector<bool> &Visited, vector<int> &Sub)
{
	Visited[V] = true;
	P_DEBUG(cout << V+1 << " ");
	Sub.push_back(V+1);
	
	vector<int>::iterator i; 
	for (i = this->Adj_List[V].begin(); i != this->Adj_List[V].end(); i++) 
		if (Visited[*i] == false)
			DFS_Rec(*i, Visited, Sub);
}

//---------------------------------------------------------------------------------------------------

void Graph::Fill_Stack(int V, vector<bool> &Visited, stack<int> &S)
{
	Visited[V] = true;

	vector<int>::iterator i; 
	for (i = this->Adj_List[V].begin(); i != this->Adj_List[V].end(); i++) 
		if (Visited[*i] == false)
			Fill_Stack(*i, Visited, S);

	S.push(V);
}

//---------------------------------------------------------------------------------------------------

void Graph::Kosaraju()
{
	stack<int> S;
	vector<bool> Visited;
	vector<int> Cycles, Sub;
	int i;

	Graph T = this->Transpose();

	Visited.resize(this->N_Nodes);
	fill(Visited.begin(), Visited.end(), false);

	for(i = 0; i < this->N_Nodes; i++) 
        if(Visited[i] == false) 
            Fill_Stack(i, Visited, S);

    fill(Visited.begin(), Visited.end(), false);

    P_DEBUG(cout <<  "Strongly Connected Components List:" << endl);

    while (!S.empty())
    {
    	int Current = S.top();
    	S.pop();

    	if (!Visited[Current])
    	{
    		Sub.clear();
    		T.DFS_Rec(Current, Visited, Sub);
    		P_DEBUG(cout << endl);
    		if (Sub.size() > 1)
    			Cycles.insert(Cycles.end(), Sub.begin(), Sub.end());
    	}
    }

    sort(Cycles.begin(), Cycles.end());

    P_DEBUG(cout << endl << "Answer:" << endl);

    copy(Cycles.begin(), Cycles.end(), ostream_iterator<int> (cout, " "));

    cout << endl;

}

//--------------------------------------------------------------------------------------------------

Graph Graph::Transpose()
{
	Graph T(this->N_Nodes);
	int i;

	for (i = 0; i < N_Nodes; i++)
	{
		T.Adj_List[this->Adj_List[i].front()].push_back(i);
	}

	P_DEBUG(cout << "Transposed Graph Adj. List:" << endl);
	P_DEBUG(T.Print_Graph());
	P_DEBUG(cout << endl);

	return T;
}

//-------------------------------------------------------------------------------------------------

void Graph::Print_Graph ()
{
    vector< vector<int> >::iterator i;
    vector<int>::iterator j;
    int C_Node = 0;

    for (i = this->Adj_List.begin(); i != this->Adj_List.end(); i++)
    {   
        cout << "L(" << C_Node+1 << ")";
        for (j = this->Adj_List[C_Node].begin(); j != this->Adj_List[C_Node].end(); j++)
        {
           cout << " -> " << (*j)+1;
        }
        cout << endl;
        C_Node++;
    }
}

//==================================================================================================================================

int main ()
{
	int V1, V2, N, i;
	cin >> N;

    Graph G(N);

    for (i = 0; i < N; i++)
    {
    	cin >> V1 >> V2;
    	G.Insert_Edge(V1-1, V2-1);
    }

    P_DEBUG(cout << endl << "Graph Adj. List:" << endl);
    P_DEBUG(G.Print_Graph());
    P_DEBUG(cout << endl);

    G.Kosaraju();

    return 0;
}
