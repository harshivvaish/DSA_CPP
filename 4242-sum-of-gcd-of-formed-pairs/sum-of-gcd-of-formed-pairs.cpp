class Solution {
public:
    long long gcdSum(vector<int>& nums) {
        int n = nums.size();
        vector<int> prefixGcd(n);
        
        int current_max = 0;
        for (int i = 0; i < n; ++i) {
            if (nums[i] > current_max) {
                current_max = nums[i];
            }
            prefixGcd[i] = std::gcd(nums[i], current_max);
        }

        sort(prefixGcd.begin(), prefixGcd.end());
        long long total_gcd_sum = 0;
        int l = 0;
        int r = n - 1;

        while (l < r) {
            total_gcd_sum += std::gcd(prefixGcd[l], prefixGcd[r]);
            l++;
            r--;
        }
        return total_gcd_sum;
    }
};