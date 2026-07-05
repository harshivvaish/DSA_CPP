class Solution {
public:
    vector<int> pathsWithMaxScore(vector<string>& board) {
        // Optimize I/O operations
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        int n = board.size();
        const int MOD = 1e9 + 7;

        // DP tables initialized to -1 (representing unreachable state)
        vector<vector<int>> max_score(n, vector<int>(n, -1));
        vector<vector<int>> path_count(n, vector<int>(n, 0));

        // Base case: Starting point 'S' at the bottom-right corner
        max_score[n - 1][n - 1] = 0;
        path_count[n - 1][n - 1] = 1;

        // Direction vectors for moving down, right, and down-right diagonal
        // (Looking backward at where a path could have come from)
        int dr[] = {1, 0, 1};
        int dc[] = {0, 1, 1};

        // Process the grid from bottom to top, right to left
        for (int r = n - 1; r >= 0; --r) {
            for (int c = n - 1; c >= 0; --c) {
                // Skip obstacles and the absolute starting point
                if (board[r][c] == 'X' || (r == n - 1 && c == n - 1)) continue;

                int current_val = (board[r][c] >= '1' && board[r][c] <= '9') ? (board[r][c] - '0') : 0;
                int best_prev_score = -1;
                int paths_to_best = 0;

                // Check all 3 potential previous positions
                for (int i = 0; i < 3; ++i) {
                    int prev_r = r + dr[i];
                    int prev_c = c + dc[i];

                    // Check bounds and make sure the previous cell was reachable
                    if (prev_r < n && prev_c < n && max_score[prev_r][prev_c] != -1) {
                        int score_from_prev = max_score[prev_r][prev_c];

                        if (score_from_prev > best_prev_score) {
                            best_prev_score = score_from_prev;
                            paths_to_best = path_count[prev_r][prev_c];
                        } else if (score_from_prev == best_prev_score) {
                            paths_to_best = (paths_to_best + path_count[prev_r][prev_c]) % MOD;
                        }
                    }
                }

                // If at least one valid preceding neighbor was reachable, update current cell
                if (best_prev_score != -1) {
                    max_score[r][c] = best_prev_score + current_val;
                    path_count[r][c] = paths_to_best;
                }
            }
        }

        // Return [0, 0] if 'E' at (0, 0) is unreachable
        if (max_score[0][0] == -1) {
            return {0, 0};
        }

        return {max_score[0][0], path_count[0][0]};
    }
};