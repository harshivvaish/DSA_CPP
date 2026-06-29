#include <string>
#include <vector>
#include <numeric>

class Solution {
public:
    std::string convert(std::string s, int numRows) {
        // Edge case: If there's only 1 row or the string is shorter than the row count,
        // no zigzagging happens.
        if (numRows == 1 || numRows >= s.length()) {
            return s;
        }

        // Create a vector of strings, one for each row
        std::vector<std::string> rows(numRows);
        int currentRow = 0;
        bool goingDown = false;

        // Iterate through each character in the string
        for (char c : s) {
            rows[currentRow] += c;

            // Change direction when we hit the top or bottom row
            if (currentRow == 0 || currentRow == numRows - 1) {
                goingDown = !goingDown;
            }

            // Move to the next row based on the current direction
            currentRow += goingDown ? 1 : -1;
        }

        // Combine all rows into a single string
        std::string result;
        for (const std::string& row : rows) {
            result += row;
        }

        return result;
    }
};