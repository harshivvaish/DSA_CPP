#include <string>
#include <vector>
#include <numeric>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
private:
    // Computes multinomial coefficient: total! / (cnt[0]! * cnt[1]! * ...)
    // Capped at cap (k + 1) to avoid overflow
    long long countPermutations(const vector<int>& freq, long long cap) {
        int total = 0;
        for (int f : freq) total += f;
        
        long long ans = 1;
        int current_total = 0;
        
        for (int f : freq) {
            if (f <= 0) continue;
            for (int j = 1; j <= f; ++j) {
                current_total++;
                ans = ans * current_total / j;
                if (ans >= cap) return cap; // Cap early to avoid overflow
            }
        }
        return ans;
    }

public:
    string smallestPalindrome(string s, int k) {
        // Fast I/O execution boost
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        int n = s.length();
        int half_len = n / 2;

        // Step 1: Count frequency of characters in the first half
        vector<int> freq(26, 0);
        for (int i = 0; i < half_len; ++i) {
            freq[s[i] - 'a']++;
        }

        // Step 2: Check if there are enough palindromic permutations
        long long total_perms = countPermutations(freq, k + 1);
        if (total_perms < k) {
            return ""; // Fewer than k distinct permutations
        }

        // Step 3: Construct the first half lexicographically
        string half = "";
        half.reserve(half_len);

        for (int i = 0; i < half_len; ++i) {
            for (int c = 0; c < 26; ++c) {
                if (freq[c] == 0) continue;

                // Try placing character 'a' + c at this position
                freq[c]--;
                long long num_ways = countPermutations(freq, k + 1);

                if (k <= num_ways) {
                    // Character c belongs at this index
                    half.push_back('a' + c);
                    break;
                } else {
                    // Skip all permutations starting with 'a' + c
                    k -= num_ways;
                    freq[c]++; // Backtrack and try next character
                }
            }
        }

        // Step 4: Reconstruct full palindromic string from the half
        string res = half;
        if (n % 2 != 0) {
            res.push_back(s[half_len]); // Middle character for odd lengths
        }
        for (int i = half_len - 1; i >= 0; --i) {
            res.push_back(half[i]);
        }

        return res;
    }
};