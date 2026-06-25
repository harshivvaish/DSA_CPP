class Solution {
public:
    vector<int> separateDigits(vector<int>& nums) {
        vector<int> ans;
        int n= nums.size();
        for(int i=0; i<n; i++){
            vector<int> digits;
            int num = nums[i];
            while(num != 0){
                int lst_dig = num%10;
                digits.push_back(lst_dig);
                num=num/10;
            }
            for(int j=digits.size()-1; j>=0; j--){
                ans.push_back(digits[j]);
            }
        }
        return ans;
    }
};