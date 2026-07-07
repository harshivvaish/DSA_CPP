class Solution {
public:
    long long sumAndMultiply(int n) {
        long long temp_num=n;
        long long sum=0;
        if(n==0) return 0;
        string ans;
        while(temp_num != 0){
            int lst_dig=temp_num%10;
            if(lst_dig==0) {
                 temp_num/=10;
                 continue;
            }
            char lst_char= lst_dig + '0';
        
            ans.push_back(lst_char);
            sum += lst_dig;
            temp_num/=10;

        }  
        reverse(ans.begin(), ans.end());
        long long ans_int =stoll(ans);
        long long fin =sum*ans_int;
        return fin;
    }
};