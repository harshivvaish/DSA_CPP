class Solution {
public:
    bool findSafeWalk(vector<vector<int>>& grid, int health) {
        int m = grid.size();
        int n = grid[0].size();
        
        // Tracks the minimum health lost to reach each cell
        vector<vector<int>> min_loss(m, vector<int>(n, INT_MAX));
        
        // Deque for 0-1 BFS: stores {row, col}
        deque<pair<int, int>> dq;
        
        // Initialize base case at (0, 0)
        min_loss[0][0] = grid[0][0];
        dq.push_back({0, 0});
        
        // Direction vectors for moving Up, Down, Left, Right
        int dRow[] = {-1, 1, 0, 0};
        int dCol[] = {0, 0, -1, 1};
        
        while (!dq.empty()) {
            auto [r, c] = dq.front();
            dq.pop_front();
            
            // If we reached the destination, we can early exit if we want, 
            // but standard 0-1 BFS naturally processes shortest paths first.
            if (r == m - 1 && c == n - 1) break;
            
            for (int i = 0; i < 4; i++) {
                int newR = r + dRow[i];
                int newC = c + dCol[i];
                
                // Check boundaries
                if (newR >= 0 && newR < m && newC >= 0 && newC < n) {
                    int weight = grid[newR][newC];
                    
                    // Relaxation step: if we found a path with less health damage
                    if (min_loss[r][c] + weight < min_loss[newR][newC]) {
                        min_loss[newR][newC] = min_loss[r][c] + weight;
                        
                        // 0-1 BFS placement logic
                        if (weight == 0) {
                            dq.push_front({newR, newC}); // 0 weight -> Front
                        } else {
                            dq.push_back({newR, newC});  // 1 weight -> Back
                        }
                    }
                }
            }
        }
        
        // Total remaining health = starting health - minimum damage taken
        int remaining_health = health - min_loss[m - 1][n - 1];
        
        // Must reach the end with at least 1 health remaining
        return remaining_health >= 1;
    }
};