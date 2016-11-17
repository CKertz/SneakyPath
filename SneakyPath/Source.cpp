#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;
#define INF = 99999;
struct holder {
	int hopCount;
};
void readData(vector<vector<int>>&edgeMatrix, vector<vector<int>>&flowMatrix)
{
	ifstream inputfile;
	char matrixType;
	int v1;
	int v2;
	int value3; // either trafficNumber or givenVectorance, depending on if going to E or F matrix
	string dummyLine;
	inputfile.open("inputFile.txt");
	getline(inputfile, dummyLine);
	while (inputfile)
	{
			inputfile >> matrixType;
			if (matrixType == 'E' || matrixType == 'F')
			{
				if (inputfile.peek() == ',')
					inputfile.ignore();
				inputfile >> v1;
				if (inputfile.peek() == ',')
					inputfile.ignore();
				inputfile >> v2;
				if (inputfile.peek() == ',')
					inputfile.ignore();
				inputfile >> value3;
				if (matrixType == 'E')
					edgeMatrix[v1-1][v2-1] = value3;
				if (matrixType == 'F')
					flowMatrix[v1-1][v2-1] = value3;	
			}
	}
}


void floydWarshall(vector<vector<int>>&givenVector)
{
	/* givenVector[][] will be the output matrix that will finally have the shortest
	givenVectorances between every pair of vertices */
	int i, j, k;

	/* Add all vertices one by one to the set of intermediate vertices.
	---> Before start of a iteration, we have shortest givenVectorances between all
	pairs of vertices such that the shortest givenVectorances consider only the
	vertices in set {0, 1, 2, .. k-1} as intermediate vertices.
	----> After the end of a iteration, vertex no. k is added to the set of
	intermediate vertices and the set becomes {0, 1, 2, .. k} */
	for (k = 0; k < givenVector.size(); k++)
	{
		// Pick all vertices as source one by one
		for (i = 0; i < givenVector.size(); i++)
		{
			// Pick all vertices as destination for the
			// above picked source
			for (j = 0; j < givenVector.size(); j++)
			{
				// If vertex k is on the shortest path from
				// i to j, then update the value of givenVector[i][j]
				if (givenVector[i][k] + givenVector[k][j] < givenVector[i][j])// Any path tracking code should be added here
				{
					givenVector[i][j] = givenVector[i][k] + givenVector[k][j];
					//givenVector[i][j]
				}

			}
		}
	}
	for (int m = 0; m < givenVector.size(); m++) // set the diagonals to zero, no shortest path to themselves necessary
		givenVector[m][m] = 0;
	// Print the shortest givenVectorance matrix
	//printSolution(givenVector);
}

/* A utility function to print solution */
//void printSolution()
//{
//	printf("Following matrix shows the shortest givenVectorances"
//		" between every pair of vertices \n");
//	for (int i = 0; i < V; i++)
//	{
//		for (int j = 0; j < V; j++)
//		{
//			if (givenVector[i][j] == INF)
//				printf("%7s", "INF");
//			else
//				printf("%7d", givenVector[i][j]);
//		}
//		printf("\n");
//	}
//}
int main()
{
	ifstream inputfile;
	vector<vector<int>>edgeMatrix; //using 2d vectors as my Matrix instead of arrays
	vector<vector<int>>flowMatrix;
	int n;
	int startPoint;
	int endPoint;
	
	inputfile.open("inputFile.txt");

	//takes the first 3 inputs in the .txt file
	inputfile >> n;
	if (inputfile.peek() == ',')
		inputfile.ignore();
	inputfile >> startPoint;
	if (inputfile.peek() == ',')
		inputfile.ignore();
	inputfile >> endPoint;
	if (inputfile.peek() == ',')
		inputfile.ignore();
	edgeMatrix.resize(n, vector<int>(n,99999)); // Assumption made we will not be using distances or traffic over 99999. This is "infinity", infinity cannot be used due to C++ restrictions
	flowMatrix.resize(n, vector<int>(n,99999));
	
	cout << "arrays initialized" << endl;
	readData(edgeMatrix, flowMatrix);
	floydWarshall(edgeMatrix);
	cout << "The shortest path from " << startPoint << " to " << endPoint << " is " 
		 << edgeMatrix[startPoint-1][endPoint-1] << endl;
	floydWarshall(flowMatrix);
	system("pause");
	return 0;
}