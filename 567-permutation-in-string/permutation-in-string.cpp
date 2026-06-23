class Solution {
public:
    bool is_having_same_frequency(int a[], int b[]){
        for(int i=0; i<26; i++){
            if(a[i] != b[i]) return false;
        }
        return true;
    }
    bool checkInclusion(string s1, string s2) {
        int freq[26]={0};
        int window_size=s1.length();
        int n2=s2.length();
        for(int i=0; i<window_size; i++){
            freq[s1[i]-'a']++;
        }

        for(int i=0; i<n2; i++){
            int window_st=0, idx=i;
            int window_freq[26]={0};

            while(window_st<window_size && idx<n2){
                window_freq[s2[idx]-'a']++;
                window_st++;
                idx++;
            }
            if(is_having_same_frequency(window_freq, freq)){
                return true;
            } 
        }
        return false;
    }
};