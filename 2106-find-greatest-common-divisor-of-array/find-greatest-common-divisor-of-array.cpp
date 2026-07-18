class Solution {
public:
    int findGCD(vector<int>& nums) {
        int a=nums[0], b=nums[0];
        for(int i=1; i<nums.size(); i++){
            if(nums[i]>a){
                a=nums[i];
            }
            else if(nums[i]<b){
                b=nums[i];
            }
        }

        while(a>0 && b>0){
            if(a>b){
                a=a%b;
            }
            else{
                b=b%a;
            }
        }
        if(a==0)  return b;
        return a;
    }
};