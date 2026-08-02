#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
public:
    bool predictTheWinner(vector<int>& nums) {
        // Fast I/O optimization
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        int n = nums.size();
        // If array size is even, Player 1 can always guarantee a win or draw
        if (n % 2 == 0) return true;

        // dp[j] stores the max score difference Player 1 can secure on subarray [i...j]
        vector<int> dp(nums);

        // Fill DP table bottom-up
        for (int i = n - 2; i >= 0; --i) {
            for (int j = i + 1; j < n; ++j) {
                int pickLeft = nums[i] - dp[j];
                int pickRight = nums[j] - dp[j - 1];
                dp[j] = max(pickLeft, pickRight);
            }
        }

        // If net relative score >= 0, Player 1 wins or ties
        return dp[n - 1] >= 0;
    }
};