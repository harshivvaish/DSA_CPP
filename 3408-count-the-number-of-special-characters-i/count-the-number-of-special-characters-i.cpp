class Solution {
public:
    bool is_lower(char c){
        if(c>='a' && c<='z'){
            return true;
        }
        return false;
    }
    bool is_upper(char c){
        if(c>='A' && c<='Z') return true;
        return false;
    }
    int numberOfSpecialChars(string word) {
        unordered_set<char> check;
        unordered_set<char> check_upper;
        int count=0, n=word.length();
        for(int i=0; i<n; i++){
            if(is_lower(word[i])){
                check.insert(word[i]);
            }
        
            
        }
        for(int i=0; i<n; i++){
            if(is_upper(word[i])){
                if(check_upper.find(word[i])==check_upper.end() && check.find(tolower(word[i])) != check.end()){
                    count++;
                    check_upper.insert(word[i]);
                }
            }
        }
        return count;
    }
};