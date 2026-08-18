class Solution {
    public int largestInteger(int[] nums, int k) {
        int n = nums.length;
        if (k == n) {
            int max = -1;
            for (int x : nums) {
                if (x > max) {
                    max = x;
                }
            }
            return max;
        }
        
        if (k == 1) {
            int[] count = new int[51];
            for (int x : nums) {
                count[x]++;
            }
            for (int i = 50; i >= 0; i--) {
                if (count[i] == 1) {
                    return i;
                }
            }
            return -1;
        }
        
        int countFirst = 0;
        int countLast = 0;
        for (int x : nums) {
            if (x == nums[0]) countFirst++;
            if (x == nums[n - 1]) countLast++;
        }
        
        int ans = -1;
        if (countFirst == 1) ans = nums[0];
        if (countLast == 1 && nums[n - 1] > ans) ans = nums[n - 1];
        
        return ans;
    }
}