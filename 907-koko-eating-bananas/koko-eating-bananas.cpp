
class Solution {
public:
        long long target(vector<int>arr,int mid, int n){
            long long hours=0;
            for(int i=0; i<n; i++){
                hours += (arr[i] + mid - 1LL) / mid;
            }
            return hours;
        }
        
    int minEatingSpeed(vector<int>& piles, int h) {
        int n=piles.size();
        int end= *max_element(piles.begin(), piles.end());
        int st=1;
        int ans=end;
        while(st<=end){
            int mid= st+(end-st)/2;
            long long hours= target(piles, mid, n);
            if(hours<=h){
                ans=mid;
                end=mid-1;
            }
            else{
                st=mid+1;
            }
        }
        return ans;
    }
};