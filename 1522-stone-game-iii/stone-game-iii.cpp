class Solution {
public:
    string stoneGameIII(vector<int>& stoneValue) {
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        int n = stoneValue.size();
        int dp[4] = {0, 0, 0, 0};

        for (int i = n - 1; i >= 0; --i) {
            int maxDiff = -1000000000;
            int currentTakeSum = 0;

            for (int k = 1; k <= 3 && i + k <= n; ++k) {
                currentTakeSum += stoneValue[i + k - 1];
                int opponentDiff = dp[(i + k) % 4];
                int diff = currentTakeSum - opponentDiff;
                if (diff > maxDiff) {
                    maxDiff = diff;
                }
            }

            dp[i % 4] = maxDiff;
        }

        int aliceDiff = dp[0];

        if (aliceDiff > 0) return "Alice";
        if (aliceDiff < 0) return "Bob";
        return "Tie";
    }
};