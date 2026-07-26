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
        powerset(nums, ans, i+1, fs);
        
    }
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<int> ans;
        vector<vector<int>> finalans;
        powerset(nums, ans, 0, finalans);
        return finalans;
    }
};