class Solution {
public:
    int minimumPushes(string word) {
        int n=word.length();
        int pushes=0;
        if(n<=8) return n*1;
        pushes = pushes + (8*1);

        if(n<=16)return pushes+ (n-8)*2;
        pushes+=8*2;

        if(n<=24)return pushes+ (n-16)*3;
        pushes+=8*3;

        return pushes+ (n-24)*4;
    }
};