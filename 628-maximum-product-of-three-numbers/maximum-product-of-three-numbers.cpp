#include <cmath>
class Solution {
public:
    int maximumProduct(vector<int>& nums) {
        // Sort the array in ascending order
        std::sort(nums.begin(), nums.end());
        
        int n = nums.size();
        
        // Option 1: Product of the three largest numbers
        int option1 = nums[n - 1] * nums[n - 2] * nums[n - 3];
        
        // Option 2: Product of the two smallest numbers (most negative) and the largest number
        int option2 = nums[0] * nums[1] * nums[n - 1];
        
        return std::max(option1, option2);
    }
};