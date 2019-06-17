#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;

int main(){
	int i,j, numCom=0;
	int idx1, idx2;
	FILE *net, *community, *stream;
	vector<int> comIndex;
	int error;

	community = fopen("community.dat", "r");
	if (community==0) {
		cout << "Arquivos nao encontrados: network.dat e community.dat\n\n";
		return 0;
	}

	while (!feof(community)){
		error = fscanf(community,"%d %d",&idx1, &idx2);
		if (error != -1){
			if (idx2>numCom) numCom = idx2; // armazena o nœmero de comunidades na rede;
			comIndex.push_back(idx2);
		}
	}
	fclose(community);


	stream = fopen("grafo.viz", "w+");

	fprintf(stream,"graph G \{\n");
	fprintf(stream,"     splines=\"true\"\n"); // curved, true
	fprintf(stream,"     K=2\n"); // curved, true
	fprintf(stream,"     overlap=\"false\"\n");
	fprintf(stream,"     style=\"invisible\"\n"); // filled

	cout << comIndex.size() << endl;

	for (j=1 ; j<=numCom ; j++) {
		fprintf(stream,"     node [style=\"filled\", shape=\"oval\", colorscheme=rdylgn%d, color=%d]; ",numCom,j);
		for (i=0 ; i<comIndex.size() ; i++){
			if (comIndex[i] == j) fprintf(stream, "%d; ",i+1);
		}
		fprintf(stream,"\n");
	}
	fprintf(stream,"\n\n");

	for (j=1 ; j<=numCom ; j++){
		fprintf(stream,"     subgraph cluster%d {\n",j);
		net = fopen("network.dat", "r");
		while (!feof(net)) {
			error = fscanf(net,"%d %d",&idx1, &idx2);
			if (error != -1){
				if ((comIndex[idx1-1] == comIndex[idx2-1]) && (comIndex[idx1-1] == j) && (idx1 < idx2)){
					fprintf(stream,"          %d -- %d;\n",idx1, idx2);
				}
			}
		}
		fprintf(stream,"     }\n\n");
		fclose(net);
	}

	fprintf(stream, "\n\n");

	// Liga›es Inter-Comunidades
	net = fopen("network.dat", "r");
	while (!feof(net)) {
		error = fscanf(net,"%d %d",&idx1, &idx2);
		if (error != -1){
			if ((comIndex[idx1-1] != comIndex[idx2-1]) && (idx1 < idx2)){
				fprintf(stream,"     %d -- %d;\n",idx1, idx2);
			}
		}
	}
	fclose(net);

	fprintf(stream,"}\n");
	fclose(stream);

	return 0;
}
	
