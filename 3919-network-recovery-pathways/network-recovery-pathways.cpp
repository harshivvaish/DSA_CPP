#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

class Solution {
public:
    int findMaxPathScore(vector<vector<int>>& edges, vector<bool>& online, long long k) {
        int n = online.size();
        
        // 1. Build adjacency list and calculate in-degrees for topological sort
        vector<vector<pair<int, int>>> adj(n);
        vector<int> in_degree(n, 0);
        vector<int> unique_costs;
        unique_costs.reserve(edges.size());
        
        for (const auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            int cost = edge[2];
            adj[u].push_back({v, cost});
            in_degree[v]++;
            unique_costs.push_back(cost);
        }
        
        // 2. Compute Topological Sort (Kahn's Algorithm)
        queue<int> q;
        for (int i = 0; i < n; ++i) {
            if (in_degree[i] == 0) {
                q.push(i);
            }
        }
        
        vector<int> topo_order;
        topo_order.reserve(n);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            topo_order.push_back(u);
            for (const auto& neighbor : adj[u]) {
                int v = neighbor.first;
                if (--in_degree[v] == 0) {
                    q.push(v);
                }
            }
        }
        
        // Extract and sort unique edge costs for binary search
        sort(unique_costs.begin(), unique_costs.end());
        unique_costs.erase(unique(unique_costs.begin(), unique_costs.end()), unique_costs.end());
        
        // 3. Helper lambda to check feasibility of a given minimum edge cost X
        auto can_reach = [&](int X) -> bool {
            // Using long long for dp array to avoid overflow when adding costs
            vector<long long> dp(n, 1e18); 
            dp[0] = 0;
            
            for (int u : topo_order) {
                if (dp[u] == 1e18) continue;
                
                // If an intermediate node is offline, we cannot pass through it
                if (u != 0 && u != n - 1 && !online[u]) continue;
                
                for (const auto& neighbor : adj[u]) {
                    int v = neighbor.first;
                    int cost = neighbor.second;
                    
                    // We only use edges whose cost is >= X
                    if (cost >= X) {
                        // The target node must be online or be the final destination
                        if (v == n - 1 || online[v]) {
                            if (dp[u] + cost < dp[v]) {
                                dp[v] = dp[u] + cost;
                            }
                        }
                    }
                }
            }
            return dp[n - 1] <= k;
        };
        
        // 4. Binary search across the unique edge costs
        int low = 0;
        int high = unique_costs.size() - 1;
        int ans = -1;
        
        while (low <= high) {
            int mid = low + (high - low) / 2;
            int X = unique_costs[mid];
            
            if (can_reach(X)) {
                ans = X;        // X is achievable, look for a larger minimum bottleneck
                low = mid + 1;
            } else {
                high = mid - 1; // X is too restrictive, reduce the minimum threshold
            }
        }
        
        return ans;
    }
};