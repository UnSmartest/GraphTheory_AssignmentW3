#include <stdio.h>
#include <bits/stdc++.h>
using namespace std;

// for undirected graph


#include <bits/stdc++.h>
using namespace std;

class Eulerian {
    int V;
    vector<vector<int>> adj;
    vector<int> degree;

public:
    Eulerian(int n) : V(n), adj(n), degree(n, 0) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u); 
        degree[u]++;
        degree[v]++;
    }

    bool hasEulerianPath() {
        int oddCount = 0;
        for (int i = 1; i < V; i++) {  // start from 1 (numbering)
            if (degree[i] % 2 == 1) oddCount++;
        }
        return (oddCount == 0 || oddCount == 2);
    }

    int findStartNode() {
        // if eulerian path, start at odd-degree node (if it exists), else start at any
        for (int i = 1; i < V; i++) {
            if (degree[i] % 2 == 1) return i;
        }
        for (int i = 1; i < V; i++) {
            if (degree[i] > 0) return i;
        }
        return 1; 
    }

    vector<int> getEulerianPath() {
        if (!hasEulerianPath()) return {}; // return empty if doesn't exist

        vector<vector<int>> g = adj;
        stack<int> st;
        vector<int> path;

        st.push(findStartNode());

        while (!st.empty()) {
            int v = st.top();
            if (!g[v].empty()) {
                int u = g[v].back();
                g[v].pop_back();
                auto it = find(g[u].begin(), g[u].end(), v);
                if (it != g[u].end()) g[u].erase(it);
                st.push(u);
            } else {
                path.push_back(v);
                st.pop();
            }
        }

        reverse(path.begin(), path.end());
        return path;
    }
};

int main() {
    int V, E;
    cin >> V >> E;
    Eulerian g(V + 1);  // shift to 1-based numbering
    for (int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v); 
    }

    if (!g.hasEulerianPath()) {
        cout << "Euler path not found...\n";
    } else {
        auto path = g.getEulerianPath();
        for (int v : path) cout << v << " ";
        cout << "\n";
    }
}
