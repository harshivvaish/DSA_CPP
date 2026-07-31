#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
public:
    int minimumPushes(string word) {
        // Fast I/O boost for LeetCode
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        // Step 1: Count letter frequencies (O(N))
        vector<int> freq(26, 0);
        for (char c : word) {
            freq[c - 'a']++;
        }

        // Step 2: Sort frequencies in descending order (O(26 log 26) = O(1))
        sort(freq.rbegin(), freq.rend());

        // Step 3: Calculate total pushes greedily
        int totalPushes = 0;
        for (int i = 0; i < 26; ++i) {
            if (freq[i] == 0) break; // No more characters left

            // Position 0-7 -> 1 push
            // Position 8-15 -> 2 pushes
            // Position 16-23 -> 3 pushes
            // Position 24-25 -> 4 pushes
            int pushCost = (i / 8) + 1;
            totalPushes += freq[i] * pushCost;
        }

        return totalPushes;
    }
};