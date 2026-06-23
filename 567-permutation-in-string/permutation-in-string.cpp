class Solution {
public:
    
    bool checkInclusion(string s1, string s2) {
        int freq[26]={0};
        int window_freq[26]={0};
        int wind_size=s1.length();
        int n2=s2.length();
        if(wind_size>n2) return false;
        for(int i=0; i<wind_size; i++){
            freq[s1[i]-'a']++;
            window_freq[s2[i]-'a']++;
        }
        if(equal(begin(freq), end(freq), begin(window_freq))) return true;

        for(int i=1; i<=n2-wind_size; i++){
            window_freq[s2[i-1]-'a']--;
            window_freq[s2[i+wind_size-1]-'a']++;

            if(equal(begin(freq), end(freq), begin(window_freq))) return true;
        }
        return false;
    }
};