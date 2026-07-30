#include <string>
#include <iostream>

using namespace std;

class Solution {
public:
    int minimumPushes(string word) {
        // Fast I/O optimization for 0ms runtime
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        int n = word.length();
        int pushes = 0;

        // Group 1: 1 push each (Up to 8 characters)
        if (n <= 8) return n * 1;
        pushes += 8 * 1;

        // Group 2: 2 pushes each (Up to 8 more characters, 9-16)
        if (n <= 16) return pushes + (n - 8) * 2;
        pushes += 8 * 2;

        // Group 3: 3 pushes each (Up to 8 more characters, 17-24)
        if (n <= 24) return pushes + (n - 16) * 3;
        pushes += 8 * 3;

        // Group 4: 4 pushes each (Remaining characters, 25-26)
        return pushes + (n - 24) * 4;
    }
};