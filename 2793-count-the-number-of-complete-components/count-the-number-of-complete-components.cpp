#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    int countCompleteComponents(int n, vector<vector<int>>& edges) {
        // Optimize standard I/O streams for competitive programming speeds
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        // 1. Build adjacency list and track vertex degrees
        vector<vector<int>> adj(n);
        vector<int> degree(n, 0);
        for (const auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
            degree[u]++;
            degree[v]++;
        }

        vector<bool> visited(n, false);
        int complete_components_count = 0;

        // Reusable buffer to collect vertices of the current component during BFS
        vector<int> component_vertices;
        component_vertices.reserve(n); 

        // 2. Iterate through all nodes to discover components
        for (int i = 0; i < n; ++i) {
            if (visited[i]) continue;

            component_vertices.clear();
            queue<int> q;
            
            q.push(i);
            visited[i] = true;

            // Simple BFS to gather all vertices in the current connected component
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                component_vertices.push_back(u);

                for (int v : adj[u]) {
                    if (!visited[v]) {
                        visited[v] = true;
                        q.push(v);
                    }
                }
            }

            // 3. Check if the component is complete
            int component_size = component_vertices.size();
            bool is_complete = true;

            // In a complete graph, every node must have a degree exactly equal to (V - 1)
            for (int u : component_vertices) {
                if (degree[u] != component_size - 1) {
                    is_complete = false;
                    break;
                }
            }

            if (is_complete) {
                complete_components_count++;
            }
        }

        return complete_components_count;
    }
};