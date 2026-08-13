class Solution {
    public int[] longestRepeating(String s, String queryCharacters, int[] queryIndices) {
        int n = s.length();
        int m = 1;
        while (m < n) m <<= 1;
        
        int m2 = m << 1;
        int[] maxL = new int[m2];
        int[] preL = new int[m2];
        int[] sufL = new int[m2];
        int[] len = new int[m2];
        char[] preC = new char[m2];
        char[] sufC = new char[m2];
        
        for (int i = 0; i < n; i++) {
            int idx = m + i;
            maxL[idx] = preL[idx] = sufL[idx] = len[idx] = 1;
            preC[idx] = sufC[idx] = s.charAt(i);
        }
        for (int i = n; i < m; i++) {
            int idx = m + i;
            len[idx] = 1;
            preC[idx] = sufC[idx] = 'A';
        }
        
        for (int p = m - 1; p > 0; p--) {
            int l = p << 1;
            int r = l | 1;
            
            preC[p] = preC[l];
            sufC[p] = sufC[r];
            len[p] = len[l] + len[r];
            
            int ml = maxL[l], mr = maxL[r];
            maxL[p] = ml > mr ? ml : mr;
            
            preL[p] = preL[l];
            sufL[p] = sufL[r];
            
            if (sufC[l] == preC[r]) {
                int combine = sufL[l] + preL[r];
                if (combine > maxL[p]) maxL[p] = combine;
                
                if (preL[l] == len[l]) preL[p] += preL[r];
                if (sufL[r] == len[r]) sufL[p] += sufL[l];
            }
        }
        
        int k = queryIndices.length;
        int[] ans = new int[k];
        char[] qc = queryCharacters.toCharArray();
        
        for (int i = 0; i < k; i++) {
            int idx = m + queryIndices[i];
            char c = qc[i];
            
            if (preC[idx] != c) {
                preC[idx] = sufC[idx] = c;
                idx >>= 1;
                while (idx > 0) {
                    int l = idx << 1;
                    int r = l | 1;
                    
                    preC[idx] = preC[l];
                    sufC[idx] = sufC[r];
                    
                    int ml = maxL[l], mr = maxL[r];
                    maxL[idx] = ml > mr ? ml : mr;
                    
                    preL[idx] = preL[l];
                    sufL[idx] = sufL[r];
                    
                    if (sufC[l] == preC[r]) {
                        int combine = sufL[l] + preL[r];
                        if (combine > maxL[idx]) maxL[idx] = combine;
                        
                        if (preL[l] == len[l]) preL[idx] += preL[r];
                        if (sufL[r] == len[r]) sufL[idx] += sufL[l];
                    }
                    idx >>= 1;
                }
            }
            ans[i] = maxL[1];
        }
        
        return ans;
    }
}