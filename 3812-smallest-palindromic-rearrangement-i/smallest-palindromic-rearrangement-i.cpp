class Solution {
public:
    string smallestPalindrome(string s) {
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        int n = s.length();
        int halfLen = n / 2;

        int freq[26] = {0};
        for (int i = 0; i < halfLen; ++i) {
            freq[s[i] - 'a']++;
        }

        int idx = 0;
        for (int c = 0; c < 26; ++c) {
            while (freq[c] > 0) {
                s[idx++] = 'a' + c;
                freq[c]--;
            }
        }

        for (int i = 0; i < halfLen; ++i) {
            s[n - 1 - i] = s[i];
        }

        return s;
    }
};