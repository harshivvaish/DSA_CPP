class Solution {
public:
    vector<bool> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
        // Fast I/O for competitive programming environments
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);
        
        int current_comp = 0;
        int prev_num = nums[0];
        
        // Overwrite the first element with its component ID (0)
        nums[0] = 0; 
        
        for (int i = 1; i < n; ++i) {
            int current_num = nums[i];
            
            // Cast to long long to prevent integer overflow
            if ((long long)current_num - prev_num > maxDiff) {
                current_comp++;
            }
            
            prev_num = current_num;
            
            // Overwrite the current index in nums with its component ID
            nums[i] = current_comp; 
        }
        
        // Process queries
        int q = queries.size();
        vector<bool> answer(q);
        for (int i = 0; i < q; ++i) {
            // Since nums now holds component IDs, just check if they match
            answer[i] = (nums[queries[i][0]] == nums[queries[i][1]]);
        }
        
        return answer;
    }
};