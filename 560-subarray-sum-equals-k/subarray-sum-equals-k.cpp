class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int n= nums.size();
        int count=0;
        vector<int> ps(n,0);
        ps[0]=nums[0];
        for(int i=1; i<n; i++){
            ps[i]=ps[i-1]+nums[i];
        }
        
        unordered_map<int,int> m;
        for(int j=0; j<n; j++){
            if(ps[j]==k) count++;
            int val= ps[j]-k;
            if(m.find(val) != m.end()){
                count += m[val];
            }
            if(m.find(ps[j]) == m.end()){
                m[ps[j]]=0;
            }
            m[ps[j]]++;
        }
        return count;
    }
};