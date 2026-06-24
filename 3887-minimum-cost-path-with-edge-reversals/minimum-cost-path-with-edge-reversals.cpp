class Solution {
public:
    int minCost(int n, vector<vector<int>>& edges) {
        
        struct Edge {
            int to;
            int weight;
            bool is_reversed;
        };
        
   
        vector<vector<Edge>> adj(n);
        for (const auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            int w = edge[2];
            

            adj[u].push_back({v, w, false});

            adj[v].push_back({u, w, true});
        }
        

        vector<vector<long long>> dist(n, vector<long long>(2, -1));
        

        priority_queue<tuple<long long, int, int>, 
                       vector<tuple<long long, int, int>>, 
                       greater<tuple<long long, int, int>>> pq;

        pq.push({0, 0, 0});
        dist[0][0] = 0;
        
        while (!pq.empty()) {
            auto [current_cost, u, switch_used] = pq.top();
            pq.pop();

            if (u == n - 1) return current_cost;
            

            if (dist[u][switch_used] != -1 && current_cost > dist[u][switch_used]) {
                continue;
            }
            
            for (const auto& edge : adj[u]) {
                if (!edge.is_reversed) {

                    long long next_cost = current_cost + edge.weight;

                    if (dist[edge.to][0] == -1 || next_cost < dist[edge.to][0]) {
                        dist[edge.to][0] = next_cost;
                        pq.push({next_cost, edge.to, 0});
                    }
                } else if (switch_used == 0) {
        
                    long long next_cost = current_cost + 2LL * edge.weight;
                    

                    if (dist[edge.to][0] == -1 || next_cost < dist[edge.to][0]) {
                        dist[edge.to][0] = next_cost;
                        pq.push({next_cost, edge.to, 0});
                    }
                }
            }
        }

        return -1;
    }
};