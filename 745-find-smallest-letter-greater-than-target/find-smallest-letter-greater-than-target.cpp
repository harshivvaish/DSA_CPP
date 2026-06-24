#include <vector>

class Solution {
public:
    char nextGreatestLetter(std::vector<char>& letters, char target) {
        int low = 0;
        int high = letters.size() - 1;
        
        while (low <= high) {
            int mid = low + (high - low) / 2;
            
            if (letters[mid] <= target) {
                // If mid is less than or equal to target, 
                // the answer must be strictly to the right.
                low = mid + 1;
            } else {
                // If mid is greater than target, it's a candidate,
                // but we look left to see if there's a smaller valid one.
                high = mid - 1;
            }
        }
        
        // If low equals letters.size(), low % letters.size() wraps around to 0
        return letters[low % letters.size()];
    }
};