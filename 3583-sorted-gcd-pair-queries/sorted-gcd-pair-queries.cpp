long long cnt[100005];
long long exact_gcd_cnt[100005];
long long pref[100005];

class Solution {
public:
    vector<int> gcdValues(vector<int>& nums, vector<long long>& queries) {
        int max_val = 0;
        for (int x : nums) {
            if (x > max_val) max_val = x;
        }

        for (int i = 0; i <= max_val; ++i) {
            cnt[i] = 0;
            exact_gcd_cnt[i] = 0;
        }

        for (int x : nums) {
            cnt[x]++;
        }
        for (int i = max_val; i >= 1; --i) {
            long long multiples_count = 0;
            for (int j = i; j <= max_val; j += i) {
                multiples_count += cnt[j];
            }
            long long total_pairs = (multiples_count * (multiples_count - 1)) / 2;

            for (int j = 2 * i; j <= max_val; j += i) {
                total_pairs -= exact_gcd_cnt[j];
            }

            exact_gcd_cnt[i] = total_pairs;
        }
        pref[0] = 0;
        for (int i = 1; i <= max_val; ++i) {
            pref[i] = pref[i - 1] + exact_gcd_cnt[i];
        }

        int q_size = queries.size();
        vector<int> ans(q_size);

        for (int i = 0; i < q_size; ++i) {
            long long target = queries[i];
 
            int low = 1, high = max_val, res = max_val;
            while (low <= high) {
                int mid = low + (high - low) / 2;
                if (pref[mid] > target) {
                    res = mid;
                    high = mid - 1;
                } else {
                    low = mid + 1;
                }
            }
            ans[i] = res;
        }

        return ans;
    }
};