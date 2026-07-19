class Solution {
public:
    string smallestSubsequence(string s) {
        int count[26] = {0};
        unsigned int visited = 0;

        for (char c : s) {
            count[c - 'a']++;
        }

        string result = "";
        result.reserve(26);

        for (char c : s) {
            int idx = c - 'a';
            count[idx]--;

            if ((visited >> idx) & 1) {
                continue;
            }

            while (!result.empty() && result.back() > c && count[result.back() - 'a'] > 0) {
                visited &= ~(1 << (result.back() - 'a'));
                result.pop_back();
            }

            result.push_back(c);
            visited |= (1 << idx);
        }

        return result;
    }
};