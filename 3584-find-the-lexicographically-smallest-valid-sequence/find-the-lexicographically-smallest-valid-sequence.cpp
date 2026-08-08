#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    vector<int> validSequence(string word1, string word2) {
        int n = word1.length();
        int m = word2.length();

        // last[j] stores the maximum index in word1 to match word2[j...m-1] exactly
        vector<int> last(m + 1, -1);
        last[m] = n;

        // Precompute right-to-left exact match indices
        for (int i = n - 1, j = m - 1; i >= 0 && j >= 0; i--) {
            if (word1[i] == word2[j]) {
                last[j] = i;
                j--;
            }
        }

        vector<int> ans;
        ans.reserve(m);
        int i = 0;
        bool change_used = false;

        // Greedily pick the smallest valid index for each character of word2
        for (int k = 0; k < m; k++) {
            bool found = false;
            while (i < n) {
                if (word1[i] == word2[k]) {
                    ans.push_back(i);
                    i++;
                    found = true;
                    break;
                } else if (!change_used && i < last[k + 1]) {
                    change_used = true;
                    ans.push_back(i);
                    i++;
                    found = true;
                    break;
                }
                i++;
            }
            if (!found) return {};
        }

        return ans;
    }
};