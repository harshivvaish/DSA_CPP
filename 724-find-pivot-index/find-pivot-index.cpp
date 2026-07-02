class Solution {
public:
    int pivotIndex(vector<int>& nums) {
        int n=nums.size();
        vector<int> ps(n,0);
        ps[0]=nums[0];
        for(int i=1; i<n; i++){
            ps[i]=ps[i-1]+nums[i];
        }
        if(ps[n-1]-ps[0]==0) return 0;
        for(int i=1; i<n-1; i++){
            if(ps[i-1]==ps[n-1]-ps[i]) return i;
        }
        
        if(ps[n-2]==0) return n-1;
        return -1;
    }
};