#include <vector>
#include <string>

using namespace std;

// Allocate fixed-size scratch buffers outside the function body 
// to completely bypass heap allocation/deallocation overhead.
// Max string length constraint for this problem layout is typically 10^5.
constexpr int MAX_M = 100005;
constexpr int MOD = 1e9 + 7;

long long pow10_table[MAX_M];
long long pref_sum[MAX_M];
long long pref_val[MAX_M];
int non_zero_count[MAX_M];
bool initialized = false;

class Solution {
public:
    vector<int> sumAndMultiply(string s, vector<vector<int>>& queries) {
        // Tie performance to standard I/O optimizations
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        // Precompute base powers of 10 once across runtime life
        if (!initialized) {
            pow10_table[0] = 1;
            for (int i = 1; i < MAX_M; ++i) {
                pow10_table[i] = (pow10_table[i - 1] * 10) % MOD;
            }
            initialized = true;
        }

        int m = s.length();
        pref_sum[0] = 0;
        pref_val[0] = 0;
        non_zero_count[0] = 0;

        // Build rolling state using flat sequential pointers
        for (int i = 0; i < m; ++i) {
            int digit = s[i] - '0';
            pref_sum[i + 1] = pref_sum[i] + digit;
            
            if (digit != 0) {
                pref_val[i + 1] = (pref_val[i] * 10 + digit) % MOD;
                non_zero_count[i + 1] = non_zero_count[i] + 1;
            } else {
                pref_val[i + 1] = pref_val[i];
                non_zero_count[i + 1] = non_zero_count[i];
            }
        }

        int num_queries = queries.size();
        vector<int> answer(num_queries);

        // Process independent lookup blocks via tight index iterations
        for (int i = 0; i < num_queries; ++i) {
            int l = queries[i][0];
            int r = queries[i][1];

            long long current_sum = pref_sum[r + 1] - pref_sum[l];
            int c = non_zero_count[r + 1] - non_zero_count[l];

            // Branchless arithmetic subtraction adjustment
            long long x = (pref_val[r + 1] - (pref_val[l] * pow10_table[c])) % MOD;
            if (x < 0) x += MOD;

            answer[i] = (x * (current_sum % MOD)) % MOD;
        }

        return answer;
    }
};