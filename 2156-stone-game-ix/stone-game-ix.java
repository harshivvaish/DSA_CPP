class Solution {
    public boolean stoneGameIX(int[] stones) {
        int c0 = 0, c1 = 0, c2 = 0;
        
        for (int s : stones) {
            int rem = s % 3;
            if (rem == 0) {
                c0++;
            } else if (rem == 1) {
                c1++;
            } else {
                c2++;
            }
        }
        
        if ((c0 & 1) == 0) {
            return c1 > 0 && c2 > 0;
        }
        
        return c1 - c2 > 2 || c2 - c1 > 2;
    }
}