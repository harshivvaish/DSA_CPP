class Solution {
public:
    int compress(vector<char>& chars) {
        int n = chars.size();
        int write_index = 0; // Tracks where we are writing the compressed data
        int i = 0;           // Reads through the array
        
        while (i < n) {
            char current_char = chars[i];
            int count = 0;
            
            // Count occurrences of the current character
            while (i < n && chars[i] == current_char) {
                count++;
                i++;
            }
            
            // 1. Write the character itself
            chars[write_index] = current_char;
            write_index++;

            
            // 2. If the character appeared more than once, write the count digits
            if (count > 1) {
                string count_str = to_string(count);
                for (char c : count_str) {
                    chars[write_index] = c;
                    write_index++;
                }
            }
        }
        
        // Return the new size of the compressed array boundary
        return write_index;
    }
};