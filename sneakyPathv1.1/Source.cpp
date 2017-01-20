#include "Header.h"


// To store shortest path distances
Distance ** dist;
Distance ** flowDist; 

Distance ** updatedFlowDist; // This will hold combined traffic load on each edge.  


int ** parent;// To store the path and corresponding parents 
int ** flowParent;// To store the path and corresponding parents of the updatedFlowdist array.
void f()
{
	//used in reference from cppreference.com, solely used to clock speed
	volatile double d = 0;
	for (int n = 0; n<10000; ++n)
		for (int m = 0; m<10000; ++m)
			d += d*n*m;
}
template <typename T>
T StringToNumber(const string &Text)//Text not by const reference so that the function can be used with a 
{                               //character array as argument
	stringstream ss(Text);
	T result;
	return ss >> result ? result : 0;
}

// Recursive functions to obtain the path as a string

string obtainSneakyPath(int i, int j, int &count)
{
	if (updatedFlowDist[i][j].isInfinite())
	{
		count++;
		return " no path to ";
	}


	if (flowParent[i][j] == i)
	{
		count++;
		return " ";
	}

	else
	{
		count++;
		return obtainSneakyPath(i, flowParent[i][j],count) + to_string(flowParent[i][j] + 1) + obtainSneakyPath(flowParent[i][j], j,count);
	}

}
string obtainPath(int i, int j)
{
	if (dist[i][j].isInfinite())
		return " no path to ";

	if (parent[i][j] == i)
		return " ";
	else
		return obtainPath(i, parent[i][j]) + to_string(parent[i][j] + 1) + obtainPath(parent[i][j], j);
}
void transferFlowData(vector<vector<int>>updatedFlowMatrix)
{
	//moves data into an array, makes it more accessible 
	for (size_t i = 0; i < updatedFlowMatrix.size(); ++i)
	{
		for (size_t j = 0; j < updatedFlowMatrix.size(); ++j)
		{
			updatedFlowDist[i][j].setWeight(updatedFlowMatrix[i][j]);
		}
	}
}
void updateTraffic(vector<int>given, vector<vector<int>>&flowData, int &count)
{
	
	if (given.size() <= 2 && given.front() == given.back()) // excludes all diagonals
		return;
	int firstHolder;
	int secondHolder;

	//The loop takes the pairs of the path 2 by 2.
	//Example: if given = {0,1,5,3} for indices 0-3, it compares 0,1 first, then 1,5, etc.
	for (size_t i = 0; i < given.size()-1; ++i)
	{
		firstHolder = given[i];
		secondHolder = given[i + 1];

		if (firstHolder == given.front() && secondHolder == given.back())
		{
			count++;
			break;
		}

		else
		{
			flowData[firstHolder][secondHolder] += flowData[given.front()][given.back()];//at the i and i+1 positions in vector, add the values of flow on top of what is already there
			count++;
		}


	}
}
void getAverageSneakyPath(int i, int j, vector<vector<int>>updatedFlowDist,int &count)
{
	int n;
	vector<int>holdValues;
	vector<int>minHolder;
	string dummy;
	dummy = obtainSneakyPath(i - 1, j - 1,count);
	stringstream stream(dummy);
	holdValues.push_back(i);
	while (stream >> n)
		holdValues.push_back(n);

	
	holdValues.push_back(j);//  vector now contains integer values of all members of sneakyPath
	if (holdValues.size() == 0)
	{
		cout << "The average traffic on each node in the sneaky path is 0.00" << endl << endl;
		return;
	}

	int firstHolder;
	int secondHolder;

	for (size_t i = 0; i < holdValues.size() - 1; ++i)
	{
		firstHolder = holdValues[i];
		secondHolder = holdValues[i + 1];
		if (firstHolder == holdValues.front() && secondHolder == holdValues.back())
			break;
		else
			minHolder.push_back(updatedFlowDist[firstHolder - 1][secondHolder - 1]);
	}
	double sum = 0;
	double average = 0;
	for (size_t i = 0; i < minHolder.size(); ++i)
		sum += minHolder[i];
	if (sum > 0)
	{
		average = sum / minHolder.size();
		cout << fixed << setprecision(2) << "The average traffic of your paths in the sneaky path from your desired points " <<
			i << " and " << j << " is " << average << endl << endl;
	}

}
void getMaxSneakyPath(int i, int j, vector<vector<int>>updatedFlowDist, int &count)
{
	int n;
	vector<int>holdValues;
	vector<int>minHolder;
	string dummy;
	dummy = obtainSneakyPath(i - 1, j - 1, count);
	stringstream stream(dummy);
	holdValues.push_back(i);
	while (stream >> n)
		holdValues.push_back(n);

	holdValues.push_back(j); //  vector now contains integer values of all members of sneakyPath
	int firstHolder;
	int secondHolder;

	for (size_t i = 0; i < holdValues.size() - 1; ++i)
	{

		firstHolder = holdValues[i];
		secondHolder = holdValues[i + 1];
			if (firstHolder == holdValues.front() && secondHolder == holdValues.back())
				break;
			else
				minHolder.push_back(updatedFlowDist[firstHolder - 1][secondHolder - 1]);
	}
	if (minHolder.size() > 0)
	{
		cout << "The highest traffic path in the sneaky path from your desired points " <<
			i << " and " << j << " is " << *max_element(minHolder.begin(), minHolder.end()) << endl << endl;
		return;
	}
	cout << "The highest traffic path in the sneaky path from your desired points " <<
		i << " and " << j << " is 0, there is no traffic between them." << endl << endl;
}
void getMinSneakyPath(int i, int j, vector<vector<int>>updatedFlowDist, int &count)//i being startNode, j being endNode
{
	int n;
	vector<int>holdValues;
	vector<int>minHolder;
	string dummy;
	dummy = obtainSneakyPath(i-1, j-1, count);
	stringstream stream(dummy);
	holdValues.push_back(i);
	while (stream >> n)
		holdValues.push_back(n);

	holdValues.push_back(j); //  vector now contains integer values of all members of sneakyPath
	int firstHolder;
	int secondHolder;

	for (size_t i = 0; i < holdValues.size() - 1; ++i)
	{

		firstHolder = holdValues[i];
		secondHolder = holdValues[i + 1];
		
		if (firstHolder == holdValues.front() && secondHolder == holdValues.back())
			break;
		else
			minHolder.push_back(updatedFlowDist[firstHolder-1][secondHolder-1]);

	}
	if (minHolder.size() > 0)
	{
	cout << "The lowest traffic path in the sneaky path from your desired points " <<
		i << " and " << j << " is " << *min_element(minHolder.begin(), minHolder.end()) << endl << endl;
	return;
	}
	cout << "The lowest traffic path in the sneaky path from your desired points " <<
		i << " and " << j << " is 0, there is no traffic between them." << endl << endl;
}
void readData(vector<vector<int>>&flowMatrix,vector<vector<int>>&edgeMatrix, int &count)
{
	//parses input file, stores values
	int n;
	int startPoint;
	int endPoint;
	ifstream inputfile;
	

	inputfile.open("ifile.txt");
	inputfile >> n;
	if (inputfile.peek() == ',')
		inputfile.ignore();
	inputfile >> startPoint;
	if (inputfile.peek() == ',')
		inputfile.ignore();
	inputfile >> endPoint;
	if (inputfile.peek() == ',')
		inputfile.ignore();
	
	flowMatrix.resize(n, vector<int>(n, 0));

	inputfile.close();
	
	char matrixType;
	int v1;
	int v2;
	int value3;
	string dummyLine;
	inputfile.open("ifile.txt");
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
			if (matrixType == 'F')
				flowMatrix[v1 - 1][v2 - 1] = value3;
			if (matrixType == 'F')
				flowMatrix[v1 - 1][v2 - 1] = value3;
		}
		count++;
	}
}
void floydWarshall(Distance **& dist, int V, int **& parent, int &count)
{
	for (int k = 0; k<V; k++)
	{
		for (int i = 0; i<V; i++)
		{
			for (int j = 0; j<V; j++)
			{
				if (dist[i][j] > dist[i][k] + dist[k][j])
				{
					dist[i][j] = dist[i][k] + dist[k][j];
					parent[i][j] = parent[k][j];
				}
				count++;
			}
		}
	}

}
int checkNegativeCycles(Distance **& dist, int V)
{
	for (int i = 0; i<V; i++)
	{
		if (!dist[i][i].isZero())
		{
			cout << "Negative cycle at : " << i + 1 << endl;
			return 0;
		}
	}
	return 0;
}
int main()
{
	int readDataCount = 0;
	int floydWarshallCount = 0;
	int sneakyPathCount = 0;
	int updateTrafficCount = 0;

	ifstream ifile;
	ifile.open("ifile.txt");

	if (!ifile)
	{
		cout << "File not found." << endl;
		exit(-1);
	}
	// number of vertices and edges
	int startNode, endNode;
	int E = 0;
	int F = 0;
	int V;
	int i, j, u, v, w;
	char matrixType;

	ifile >> V;
	if (ifile.peek() == ',')
		ifile.ignore();
	ifile >> startNode;
	if (ifile.peek() == ',')
		ifile.ignore();
	ifile >> endNode;
	if (ifile.peek() == ',')
		ifile.ignore();
	
	// Matrices declared and initialised to infinity and zero respectively
	dist = new Distance *[V];
	for (int i = 0; i < V; i++)
		dist[i] = new Distance[V];

	flowDist = new Distance *[V];
	for (int i = 0; i < V; i++)
		flowDist[i] = new Distance[V];

	updatedFlowDist = new Distance *[V];
	for (int i = 0; i < V; i++)
		updatedFlowDist[i] = new Distance[V];

	parent = new int *[V];
	for (int i = 0; i < V; i++)
		parent[i] = new int[V];

	flowParent = new int *[V];
	for (int i = 0; i < V; i++)
		flowParent[i] = new int[V];



	while (ifile)
	{
		ifile >> matrixType;
		if (matrixType == 'E' || matrixType == 'F')
		{
			if (ifile.peek() == ',')
				ifile.ignore();
			ifile >> u;
			if (ifile.peek() == ',')
				ifile.ignore();
			ifile >> v;
			if (ifile.peek() == ',')
				ifile.ignore();
			ifile >> w;
			if (matrixType == 'E')
			{
				dist[u - 1][v - 1].setWeight(w);
				parent[u - 1][v - 1] = u - 1;
			}
			if (matrixType == 'F')
			{
				flowDist[u - 1][v - 1].setWeight(w);
				flowParent[u - 1][v - 1] = u - 1;
			}
		}
	}

	ifile.close();

	// Path from vertex to itself is set
	for (i = 0; i<V; i++)
	{
		dist[i][i].setWeight(0);
		parent[i][i] = i;
		flowParent[i][i] = i;
	}
	floydWarshall(dist, V, parent,floydWarshallCount); 
	checkNegativeCycles(dist, V);
	vector<vector<int>>updatedTraffic;
	vector<vector<int>>edgeMatrix;
	readData(updatedTraffic,edgeMatrix,readDataCount);


	string dummy;
	updatedFlowDist = flowDist;
	vector<int>holdValues;
	int n;

	for (i = 0; i<V; i++)
	{
		for (j = 0; j<V; j++)
		{
			dummy = obtainPath(i, j);
			stringstream stream(dummy);
			holdValues.push_back(i);
			while (stream >> n)
				holdValues.push_back(n-1);

			holdValues.push_back(j);
			//we now have the shortest path in int form sitting in holdValues. 
			//take this vector, and add traffic values to it when a path different path contains it. 
			updateTraffic(holdValues, updatedTraffic,updateTrafficCount);
			holdValues.clear();
		}
	}
	transferFlowData(updatedTraffic); // Move data into an easier to access vector
	floydWarshall(updatedFlowDist, V, flowParent,floydWarshallCount);

	//displaying output
	cout << "Now calculating the Sneaky Path for nodes " << startNode << " to " << endNode << "...." << endl;
	cout << "Using a Floyd Warshall algorithm, the shortest path from your start to end node is: " << endl;
	cout << startNode << obtainPath(startNode - 1, endNode - 1) << endNode << " which is a distance of " << dist[startNode - 1][endNode - 1].getWeight() << endl << endl;
	cout << "Adjusting flow matrix to account for other flows using the same shortest path..." << endl;
	cout << "The adjusted flow on your desired path (after calculating other paths that encounter your start and endpoints) is: " 
		 << updatedTraffic[startNode - 1][endNode - 1] << endl << endl;
	cout << "The sneaky path from your start to end node is: " << endl;
	cout << startNode << " " << obtainSneakyPath(startNode - 1, endNode - 1, sneakyPathCount) << " " << endNode << " which is a distance of: " << flowDist[startNode - 1][endNode - 1].getWeight() << endl << endl; 
	getMinSneakyPath(startNode, endNode, updatedTraffic,sneakyPathCount);
	getMaxSneakyPath(startNode, endNode, updatedTraffic,sneakyPathCount);
	getAverageSneakyPath(startNode, endNode, updatedTraffic,sneakyPathCount);


	//clocking used in reference from cppreference.com 
	clock_t c_start = std::clock();
	auto t_start = chrono::high_resolution_clock::now();
	thread t1(f);
	thread t2(f); // f() is called on two threads
	t1.join();
	t2.join();
	std::clock_t c_end = std::clock();
	auto t_end = chrono::high_resolution_clock::now();

	cout << fixed << setprecision(2) << "CPU time used: "
		<< 1000.0 * (c_end - c_start) / CLOCKS_PER_SEC << " ms\n";

	system("pause");
	return 0;
}
