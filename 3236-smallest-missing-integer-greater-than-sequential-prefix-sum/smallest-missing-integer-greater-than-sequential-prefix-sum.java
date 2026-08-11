class Solution {
    public int missingInteger(int[] nums) {
        // Step 1: Calculate the longest sequential prefix sum
        int sum = nums[0];
        int i = 1;
        while (i < nums.length && nums[i] == nums[i - 1] + 1) {
            sum += nums[i];
            i++;
        }
        
        // Step 2: Record occurrences of numbers in the array
        // Since 1 <= nums[i] <= 50, a boolean array of size 51 is sufficient
        boolean[] present = new boolean[51];
        for (int num : nums) {
            present[num] = true;
        }
        
        // Step 3: Find the smallest missing integer >= sum
        while (sum <= 50 && present[sum]) {
            sum++;
        }
        
        return sum;
    }
}