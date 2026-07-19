class Solution {
public:
    string smallestSubsequence(string s) {
        int count[26] = {0};
        bool visited[26] = {false};

        for (char c : s) {
            count[c - 'a']++;
        }

        string result = "";
        for (char c : s) {

            count[c - 'a']--;

            if (visited[c - 'a']) {
                continue;
            }
            while (!result.empty() && result.back() > c && count[result.back() - 'a'] > 0) {
                visited[result.back() - 'a'] = false;
                result.pop_back();
            }

            result.push_back(c);
            visited[c - 'a'] = true;
        }

        return result;
    }
};