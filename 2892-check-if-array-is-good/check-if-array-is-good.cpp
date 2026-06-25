class Solution {
public:
    bool isGood(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int n= nums.size();
        int count =1;
        if(n==1 || n==0){
            return false;
        }
        for(int i=0; i<n-1; i++){
            if(nums[i]!=count) return false;
            count++;
        }
        if(nums[n-1]==nums[n-2] && n==nums[n-1]+1) return true;
        return false;
    }
};