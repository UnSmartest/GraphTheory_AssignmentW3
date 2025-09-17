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

void findEulerPath(int start, vector<vector<int>>& adj, vector<int>& path) {
    stack<int> st;
    st.push(start);

    while (!st.empty()) {
        int v = st.top();
        if (!adj[v].empty()) {
            int u = adj[v].back();
            adj[v].pop_back();
            auto it = find(adj[u].begin(), adj[u].end(), v);
            if (it != adj[u].end()) adj[u].erase(it);
            st.push(u);
        } else {
            path.push_back(v);
            st.pop();
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n);
    vector<int> degree(n, 0);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        degree[u]++;
        degree[v]++;
    }

    int oddCount = 0, start = 0;
    for (int i = 0; i < n; i++) {
        if (degree[i] % 2 == 1) {
            oddCount++;
            start = i;
        }
    }

    if (!(oddCount == 0 || oddCount == 2)) {
        cout << "Euler path not found...\n";
        return 0;
    }

    vector<int> path;
    findEulerPath(start, adj, path);

    reverse(path.begin(), path.end());

    for (int v : path) cout << v << " ";
    cout << "\n";

    return 0;
}
