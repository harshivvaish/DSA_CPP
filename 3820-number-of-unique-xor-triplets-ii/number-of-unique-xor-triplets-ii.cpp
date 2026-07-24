static const int _ = []() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    return 0;
}();

class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        int max_val = 0;
        for (int x : nums) {
            if (x > max_val) max_val = x;
        }
        
        // Find the smallest power of 2 greater than max_val to cap our bounds
        int limit = 1;
        while (limit <= max_val) limit <<= 1;
        
        // 1. Condense nums to only unique elements
        vector<char> present(limit, 0);
        for (int x : nums) {
            present[x] = 1;
        }
        
        vector<int> U;
        U.reserve(nums.size());
        for (int i = 0; i < limit; ++i) {
            if (present[i]) U.push_back(i);
        }
        
        // 2. Compute all unique pairwise XORs
        vector<char> pairs(limit, 0);
        int u_size = U.size();
        for (int i = 0; i < u_size; ++i) {
            int ui = U[i];
            for (int j = i; j < u_size; ++j) {
                pairs[ui ^ U[j]] = 1;
            }
        }
        
        // 3. Compute the triplet XORs by XORing the pairs with the unique values again
        vector<char> res(limit, 0);
        for (int i = 0; i < limit; ++i) {
            if (pairs[i]) {
                for (int c : U) {
                    res[i ^ c] = 1; // Pure write-operation (branchless) for SIMD vectorization
                }
            }
        }
        
        // 4. Count the distinct triplet values formed
        int count = 0;
        for (int i = 0; i < limit; ++i) {
            if (res[i]) count++;
        }
        
        return count;
    }
};