class Solution {
public:
    int zigZagArrays(int n, int l, int r) {
        if (n <= 0) return 0;
        int k = r - l + 1;
        if (k <= 0) return 0;
        if (n == 1) return k;

        long long MOD = 1000000007;

        std::vector<long long> dp_inc(k, 1);
        std::vector<long long> dp_dec(k, 1);

        for (int i = 2; i <= n; ++i) {
            std::vector<long long> next_inc(k, 0);
            std::vector<long long> next_dec(k, 0);

            long long sum_dec = 0;
            for (int j = 0; j < k; ++j) {
                next_inc[j] = sum_dec;
                sum_dec = (sum_dec + dp_dec[j]) % MOD;
            }

            long long sum_inc = 0;
            for (int j = k - 1; j >= 0; --j) {
                next_dec[j] = sum_inc;
                sum_inc = (sum_inc + dp_inc[j]) % MOD;
            }

            dp_inc = std::move(next_inc);
            dp_dec = std::move(next_dec);
        }

        long long total = 0;
        for (int j = 0; j < k; ++j) {
            total = (total + dp_inc[j] + dp_dec[j]) % MOD;
        }

        return total;
    }
};