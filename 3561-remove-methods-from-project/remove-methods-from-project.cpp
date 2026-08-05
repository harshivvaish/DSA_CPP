class Solution {
public:
    vector<int> remainingMethods(int n, int k, vector<vector<int>>& invocations) {
        // Step 1: Build the adjacency list
        vector<vector<int>> adj(n);
        for (const auto& inv : invocations) {
            adj[inv[0]].push_back(inv[1]);
        }
        
        // Step 2: Identify all suspicious methods using iterative DFS
        // We use vector<char> because vector<bool> has bit-manipulation overhead
        vector<char> suspicious(n, 0);
        suspicious[k] = 1;
        
        vector<int> stack;
        stack.reserve(n); 
        stack.push_back(k);
        
        while (!stack.empty()) {
            int curr = stack.back();
            stack.pop_back();
            
            for (int neighbor : adj[curr]) {
                if (!suspicious[neighbor]) {
                    suspicious[neighbor] = 1;
                    stack.push_back(neighbor);
                }
            }
        }
        
        // Step 3: Verify if any non-suspicious method invokes a suspicious one
        bool canRemove = true;
        for (const auto& inv : invocations) {
            if (!suspicious[inv[0]] && suspicious[inv[1]]) {
                canRemove = false;
                break;
            }
        }
        
        // Step 4: Collect and return the remaining methods
        vector<int> ans;
        ans.reserve(n); // Pre-allocate memory to speed up insertions
        
        if (!canRemove) {
            // Cannot remove the group; return all methods 0 to n-1
            for (int i = 0; i < n; ++i) {
                ans.push_back(i);
            }
        } else {
            // Safe to remove; return only the non-suspicious ones
            for (int i = 0; i < n; ++i) {
                if (!suspicious[i]) {
                    ans.push_back(i);
                }
            }
        }
        
        return ans;
    }
};