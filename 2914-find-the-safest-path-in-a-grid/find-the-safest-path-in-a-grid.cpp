using namespace std;

class Solution {
public:
    int maximumSafenessFactor(vector<vector<int>>& grid) {
        int n = grid.size();

        if (grid[0][0] == 1 || grid[n - 1][n - 1] == 1) {
            return 0;
        }
        
        vector<vector<int>> safeness(n, vector<int>(n, -1));
        queue<pair<int, int>> q;
        
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                if (grid[r][c] == 1) {
                    safeness[r][c] = 0;
                    q.push({r, c});
                }
            }
        }
        
        int dr[] = {0, 0, 1, -1};
        int dc[] = {1, -1, 0, 0};
        
        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();
            
            for (int i = 0; i < 4; ++i) {
                int nr = r + dr[i];
                int nc = c + dc[i];
                
                if (nr >= 0 && nr < n && nc >= 0 && nc < n && safeness[nr][nc] == -1) {
                    safeness[nr][nc] = safeness[r][c] + 1;
                    q.push({nr, nc});
                }
            }
        }

        priority_queue<pair<int, pair<int, int>>> pq;
        vector<vector<bool>> visited(n, vector<bool>(n, false));
        
        pq.push({safeness[0][0], {0, 0}});
        visited[0][0] = true;
        
        while (!pq.empty()) {
            auto [current_safe, cell] = pq.top();
            int r = cell.first;
            int c = cell.second;
            pq.pop();
            
            if (r == n - 1 && c == n - 1) {
                return current_safe;
            }
            
            for (int i = 0; i < 4; ++i) {
                int nr = r + dr[i];
                int nc = c + dc[i];
                
                if (nr >= 0 && nr < n && nc >= 0 && nc < n && !visited[nr][nc]) {
                    visited[nr][nc] = true;

                    int next_safe = min(current_safe, safeness[nr][nc]);
                    pq.push({next_safe, {nr, nc}});
                }
            }
        }
        
        return 0;
    }
};