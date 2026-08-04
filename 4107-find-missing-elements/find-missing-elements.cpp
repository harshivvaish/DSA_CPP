class Solution {
public:
    vector<int> findMissingElements(vector<int>& nums) {
        int maxx=INT_MIN;
        int minn=INT_MAX;
        unordered_set<int> ch;
        vector<int> ans;
        for(int i:nums){
            maxx=max(maxx,i);
            minn=min(minn,i);
            ch.insert(i);
        }
        for(int i=minn; i<=maxx; i++){
            if(ch.find(i)==ch.end()){
                ans.push_back(i);
            }
        }
        return ans;
    }
};