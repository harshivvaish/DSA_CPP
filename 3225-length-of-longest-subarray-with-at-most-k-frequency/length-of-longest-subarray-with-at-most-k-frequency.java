class Solution {
    public int maxSubarrayLength(int[] nums, int k) {
        int[] keys = new int[524288];
        int[] freqs = new int[524288];
        int mask = 524287;
        
        int maxLen = 0;
        int left = 0;
        
        for (int right = 0; right < nums.length; right++) {
            int num = nums[right];
            int pos = (num ^ (num >>> 16)) & mask;
            
            while (keys[pos] != 0 && keys[pos] != num) {
                pos = (pos + 1) & mask;
            }
            keys[pos] = num;
            freqs[pos]++;
            
            while (freqs[pos] > k) {
                int leftNum = nums[left++];
                int leftPos = (leftNum ^ (leftNum >>> 16)) & mask;
                
                while (keys[leftPos] != leftNum) {
                    leftPos = (leftPos + 1) & mask;
                }
                freqs[leftPos]--;
            }
            
            int len = right - left + 1;
            if (len > maxLen) {
                maxLen = len;
            }
        }
        
        return maxLen;
    }
}