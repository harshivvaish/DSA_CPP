class Solution {
public:
    int maxProduct(int n) {
        int num=n;
        if(n==0) return 0;
        int first=0;
        int sec = 0;
        while(num>0){
            int lst_dig=num%10;
            if(lst_dig>=first){
                sec=first;
                first=lst_dig;
            }
            else if(lst_dig>sec){
                sec=lst_dig;
            }
            num =num/10;
        }
        return first*sec;
    }
};