#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int removeCoveredIntervals(vector<vector<int>>& intervals) {
        // Optimize standard I/O channels for speed
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        int n = intervals.size();
        if (n <= 1) return n;

        // Pack [start, end] into a single 64-bit primitive value:
        // High 32 bits: start value (sorts ascending natively)
        // Low 32 bits: (1e5 - end) value (reverses sorting order -> descending end)
        vector<long long> packed(n);
        for (int i = 0; i < n; ++i) {
            long long start = intervals[i][0];
            long long end = intervals[i][1];
            packed[i] = (start << 32) | (100001LL - end);
        }

        // Blazing fast sort on primitive 64-bit integers
        sort(packed.begin(), packed.end());

        int remaining_count = 0;
        int max_end = -1;

        // Single linear pass over contiguous memory
        for (int i = 0; i < n; ++i) {
            // Unpack the real end value from the encoded lower 32 bits
            int current_end = 100001 - (packed[i] & 0xFFFFFFFFLL);

            if (current_end > max_end) {
                remaining_count++;
                max_end = current_end;
            }
        }

        return remaining_count;
    }
};