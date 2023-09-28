#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

// Function to insert vertices to adjacency list
void insert(std::vector<std::vector<int> > adj, int u, int v)
{
	// Insert a vertex v to vertex u
	adj[u].push_back(v);
	return;
}

// Function to display adjacency list
void printList(std::vector<std::vector<int> > adj, int N)
{
	for (int i = 0; i < N; i++) {
		std::cout << i;
		for (auto j : adj[i])
			std::cout << " --> " << j;
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

// Function to convert adjacency
// list to adjacency matrix
std::vector<std::vector<int> > convert(std::vector<std::vector<int> > adj, int N)
{
	// Initialize a matrix
	std::vector<std::vector<int> > matrix(N, std::vector<int>(N, 0));
	for (int i = 0; i < N; i++) {
		for (auto j : adj[i])
			matrix[i][j] = 1;
	}
	return matrix;
}

// Function to display adjacency matrix
void printMatrix(std::vector<std::vector<int> > adj, int V)
{
	for (int i = 0; i < V; i++) {
		for (int j = 0; j < V; j++) {
			std::cout << adj[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}


std::vector<std::vector<int> > readGraph(std::string filePath){
	std::vector<std::vector<int> > adjlist;
    std::ifstream file(filePath);
    std::string s; 

    while(getline(file, s)){
        std::stringstream ss(s);
        std::string token;
        double from, to;
        getline(ss, token, ' ');
        from = std::stof(token);
		std::cout<< "from : " << from << std::endl;
        getline(ss, token, ' ');
        to = std::stof(token);
		std::cout<< "to : " << to << std::endl;
        getline(ss, token, '\n');
		// insert(adjlist,from, to);
    }
    return adjlist;
}


// Driver code
int main()
{
	int V = 5;

	std::vector<int> adjList[V];
	std::vector<std::vector<int> > my_list = readGraph("../test/g1.txt");

	// Display adjacency list
	std::cout << "Adjacency List: \n";
	// for(auto el : my_list){
	// 	for(auto e : el)std::cout << e << " - ";
	// 	std::cout<<std::endl;	
	// }
	// std::cout<<std::endl;
	// printList(my_list, V);

	// Function call which returns
	// adjacency matrix after conversion
	// std::vector<std::vector<int> > adjMatrix
	// 	= convert(my_list, V);

	// // Display adjacency matrix
	// std::cout << "Adjacency Matrix: \n";
	// printMatrix(adjMatrix, V);

	return 0;
}
