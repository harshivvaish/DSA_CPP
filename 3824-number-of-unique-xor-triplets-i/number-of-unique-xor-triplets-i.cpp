static const int _ = []() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    return 0;
}();

class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        int n = nums.size();
        
        // Edge cases where the combinatorics don't provide enough numbers to reach the power of 2 upper-bound
        if (n == 1) return 1;
        if (n == 2) return 2;
        
        // For n >= 3, the number of unique XOR values is exactly the smallest power of 2 strictly greater than n.
        // __builtin_clz gives the number of leading zeros. 
        // 32 - __builtin_clz(n) calculates the number of bits required to represent n.
        return 1 << (32 - __builtin_clz(n));
    }
};