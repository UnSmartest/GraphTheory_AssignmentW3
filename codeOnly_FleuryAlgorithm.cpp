#include <stdio.h>
#include <bits/stdc++.h>
using namespace std;

/*
INPUT
4 4
0 1
0 2
1 2
2 3
*/

void eulerDFS(int currentNode, int nodeCount, int adjacencyMatrix[100][100], queue<int>& path){
    for(int neighborNode = 0; neighborNode < nodeCount; neighborNode++){
        if(adjacencyMatrix[currentNode][neighborNode] > 0){
            adjacencyMatrix[currentNode][neighborNode]--;
            adjacencyMatrix[neighborNode][currentNode]--;
            eulerDFS(neighborNode, nodeCount, adjacencyMatrix, path);
        }
    }
    path.push(currentNode);
};

int main(){
    int nodeCount, edgeCount;
    cout << "How many nodes and edges are there in your thing?\n";
    cin >> nodeCount >> edgeCount;
    int adjacencyMatrix[100][100] = {0};
    cout << "You inputed " << nodeCount << " nodes and " << edgeCount << " edges.\n";

    cout << "Input your edges :\n";
    for(int i = 0 ; i < edgeCount ; i++){
        int u,v;
        cin >> u >> v;
        adjacencyMatrix[u][v]++;
        adjacencyMatrix[v][u]++;
    }

    int amountofEdges[nodeCount] = {0};
    int odd[nodeCount], oddCount = 0;
    for(int i = 0 ; i < nodeCount ; i++){
        for(int j = 0 ; j < nodeCount ; j++){
            amountofEdges[i] += adjacencyMatrix[i][j];
        }
        if(amountofEdges[i]%2 == 1){
            odd[oddCount++] = i;
        }
    }

    if(oddCount != 0 && oddCount != 2){
        cout << "Euler path not found...";
        return 0;
    }

    int startingNode;
    if(oddCount == 2){
        startingNode = odd[0];
    } else if(oddCount == 0){
        startingNode = 0;
    }

    queue<int> path;

    eulerDFS(startingNode, nodeCount, adjacencyMatrix, path);

    while(!path.empty()){
        cout << path.front() << " ";
        path.pop();
    }

    return 0;

}