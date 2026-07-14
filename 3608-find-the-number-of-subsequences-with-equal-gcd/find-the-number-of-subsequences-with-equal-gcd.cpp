int dp[205][205];
int next_dp[205][205];
int gcd_cache[205][205];
bool cache_initialized = false;

class Solution {
public:
    int subsequencePairCount(vector<int>& nums) {
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        int max_val = 0;
        for (int v : nums) {
            if (v > max_val) max_val = v;
        }

        if (!cache_initialized) {
            for (int i = 0; i <= 200; ++i) {
                for (int j = 0; j <= 200; ++j) {
                    if (i == 0) gcd_cache[i][j] = j;
                    else if (j == 0) gcd_cache[i][j] = i;
                    else gcd_cache[i][j] = std::gcd(i, j);
                }
            }
            cache_initialized = true;
        }

        for (int i = 0; i <= max_val; ++i) {
            memset(dp[i], 0, (max_val + 1) * sizeof(int));
        }
        dp[0][0] = 1;

        const int MOD = 1e9 + 7;

        for (int v : nums) {
            for (int i = 0; i <= max_val; ++i) {
                memcpy(next_dp[i], dp[i], (max_val + 1) * sizeof(int));
            }

            for (int x = 0; x <= max_val; ++x) {
                for (int y = 0; y <= max_val; ++y) {
                    if (dp[x][y] == 0) continue;

                    int ways = dp[x][y];

                    int nx = gcd_cache[x][v];
                    int val_x = next_dp[nx][y] + ways;
                    if (val_x >= MOD) val_x -= MOD;
                    next_dp[nx][y] = val_x;

                    int ny = gcd_cache[y][v];
                    int val_y = next_dp[x][ny] + ways;
                    if (val_y >= MOD) val_y -= MOD;
                    next_dp[x][ny] = val_y;
                }
            }

            for (int i = 0; i <= max_val; ++i) {
                memcpy(dp[i], next_dp[i], (max_val + 1) * sizeof(int));
            }
        }

        long long total_pairs = 0;
        for (int g = 1; g <= max_val; ++g) {
            total_pairs += dp[g][g];
        }

        return total_pairs % MOD;
    }
};