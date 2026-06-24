class Solution {
public:
    vector<vector<int>> minimumAbsDifference(vector<int>& arr) {
        sort(arr.begin(), arr.end());
        vector<vector<int>> ans;
        int min_diff=INT_MAX;
        
        for(int i=0; i<=arr.size()-2; i++){
            int temp_min_diff = arr[i+1]-arr[i];
            if(temp_min_diff<min_diff){
                ans.clear();
                min_diff=temp_min_diff;
                ans.push_back({arr[i], arr[i+1]});
            }
            else if(temp_min_diff==min_diff){
                ans.push_back({arr[i], arr[i+1]});
            }
        }
        return ans;
    }
};