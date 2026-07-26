class Solution {
public:
    void powerset(vector<int>& nums, vector<int>& ans, int i, vector<vector<int>>& fs){
        if(i==nums.size()){
            fs.push_back({ans});
            return;
        
        }
        //INCLUDE
        ans.push_back(nums[i]);
        powerset(nums, ans, i+1, fs);

        ans.pop_back(); // BACKTRACKING

        //exclude
        int idx=i+1;
        while(idx<nums.size() && nums[idx]==nums[idx-1]){
            idx++;
        }
        powerset(nums, ans, idx, fs);
        
    }
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<int> ans;
        vector<vector<int>> finalans;
        powerset(nums, ans, 0, finalans);
        return finalans;
    }
};

