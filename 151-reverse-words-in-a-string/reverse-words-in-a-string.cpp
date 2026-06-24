class Solution {
public:
    string reverseWords(string s) {
        
        string ans="";
        int n=s.length();

        int i=n-1;
        while(i>=0){
            if(s[i]==' '){
                i--;
                continue;
            }
            string word="";
            while(i>=0  && s[i] != ' '){
                word+=s[i];
                i--;
            }
            reverse(word.begin(), word.end());

            ans+= ' '+ word;

        }
        return ans.substr(1);
    }
};