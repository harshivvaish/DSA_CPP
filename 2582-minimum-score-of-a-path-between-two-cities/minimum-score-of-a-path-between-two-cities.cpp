class Solution {
public:
    int minScore(int n, vector<vector<int>>& roads) {
        // Optimize standard I/O operations for performance
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        // 1. Build the adjacency list
        // Store pair<neighbor_city, road_distance>
        vector<vector<pair<int, int>>> adj(n + 1);
        for (const auto& road : roads) {
            int u = road[0];
            int v = road[1];
            int dist = road[2];
            adj[u].push_back({v, dist});
            adj[v].push_back({u, dist});
        }

        // 2. BFS to traverse the connected component of city 1
        queue<int> q;
        vector<bool> visited(n + 1, false);
        
        q.push(1);
        visited[1] = true;
        
        int min_score = 1e9; // Initialize with a large value

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (const auto& neighbor : adj[u]) {
                int v = neighbor.first;
                int dist = neighbor.second;

                // Track the minimum road distance seen in this component
                min_score = min(min_score, dist);

                if (!visited[v]) {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }

        return min_score;
    }
};