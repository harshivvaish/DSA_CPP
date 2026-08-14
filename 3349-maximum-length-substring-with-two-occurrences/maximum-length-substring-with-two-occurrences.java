class Solution {
    public int maximumLengthSubstring(String s) {
        char[] arr = s.toCharArray();
        int[] freq = new int[26];
        int maxLen = 0;
        int left = 0;
        
        for (int right = 0; right < arr.length; right++) {
            int idx = arr[right] - 'a';
            freq[idx]++;
            
            while (freq[idx] > 2) {
                freq[arr[left++] - 'a']--;
            }
            
            int len = right - left + 1;
            if (len > maxLen) {
                maxLen = len;
            }
        }
        
        return maxLen;
    }
}