#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

class Solution {
private:
    int memo[101][101];
    int suffixSum[101];
    int n;

    int helper(int i, int M) {
        // Base case: if we can take all remaining piles at once
        if (i + 2 * M >= n) {
            return suffixSum[i];
        }

        // Return memoized result if already computed
        if (memo[i][M] != 0) {
            return memo[i][M];
        }

        int maxStones = 0;

        // Try taking X piles where 1 <= X <= 2*M
        for (int X = 1; X <= 2 * M; X++) {
            // Player gets suffixSum[i] minus the maximum stones opponent can get on next turn
            int currentStones = suffixSum[i] - helper(i + X, max(M, X));
            maxStones = max(maxStones, currentStones);
        }

        return memo[i][M] = maxStones;
    }

public:
    int stoneGameII(vector<int>& piles) {
        n = piles.size();

        // Build suffix sum array from right to left
        suffixSum[n - 1] = piles[n - 1];
        for (int i = n - 2; i >= 0; i--) {
            suffixSum[i] = suffixSum[i + 1] + piles[i];
        }

        // Clear memoization table
        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= n; j++) {
                memo[i][j] = 0;
            }
        }

        return helper(0, 1);
    }
};