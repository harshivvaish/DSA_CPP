#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
    int f2[10] = {0, 0, 1, 0, 2, 0, 1, 0, 3, 0};
    int f3[10] = {0, 0, 0, 1, 0, 0, 1, 0, 0, 2};
    int f5[10] = {0, 0, 0, 0, 0, 1, 0, 0, 0, 0};
    int f7[10] = {0, 0, 0, 0, 0, 0, 0, 1, 0, 0};

    inline int min_digits(int r2, int r3, int r5, int r7) {
        r2 = max(0, r2);
        r3 = max(0, r3);
        r5 = max(0, r5);
        r7 = max(0, r7);

        int count = r7 + r5;
        count += r3 / 2;
        int rem3 = r3 % 2;

        count += r2 / 3;
        int rem2 = r2 % 3;

        if (rem3 == 1 && rem2 == 1) count += 1;
        else if (rem3 == 1 && rem2 == 2) count += 2;
        else if (rem3 == 1 && rem2 == 0) count += 1;
        else if (rem3 == 0 && rem2 == 2) count += 1;
        else if (rem3 == 0 && rem2 == 1) count += 1;

        return count;
    }

    string fill_suffix(int rem_len, int r2, int r3, int r5, int r7) {
        string res = "";
        res.reserve(rem_len);
        for (int i = 0; i < rem_len; ++i) {
            for (int d = 1; d <= 9; ++d) {
                if (min_digits(r2 - f2[d], r3 - f3[d], r5 - f5[d], r7 - f7[d]) <= rem_len - 1 - i) {
                    r2 -= f2[d];
                    r3 -= f3[d];
                    r5 -= f5[d];
                    r7 -= f7[d];
                    res += (char)('0' + d);
                    break;
                }
            }
        }
        return res;
    }

public:
    string smallestNumber(string num, long long t) {
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        long long temp_t = t;
        int c2 = 0, c3 = 0, c5 = 0, c7 = 0;
        while (temp_t % 2 == 0) { temp_t /= 2; c2++; }
        while (temp_t % 3 == 0) { temp_t /= 3; c3++; }
        while (temp_t % 5 == 0) { temp_t /= 5; c5++; }
        while (temp_t % 7 == 0) { temp_t /= 7; c7++; }

        if (temp_t > 1) return "-1";

        int n = num.length();
        int first_zero = n;
        for (int i = 0; i < n; ++i) {
            if (num[i] == '0') {
                first_zero = i;
                break;
            }
        }

        // Check if num itself is valid
        if (first_zero == n) {
            int cur2 = 0, cur3 = 0, cur5 = 0, cur7 = 0;
            for (char ch : num) {
                int d = ch - '0';
                cur2 += f2[d]; cur3 += f3[d]; cur5 += f5[d]; cur7 += f7[d];
            }
            if (cur2 >= c2 && cur3 >= c3 && cur5 >= c5 && cur7 >= c7) {
                return num;
            }
        }

        // Prefix factor counts
        vector<int> pref2(n + 1, 0), pref3(n + 1, 0), pref5(n + 1, 0), pref7(n + 1, 0);
        for (int i = 0; i < first_zero; ++i) {
            int d = num[i] - '0';
            pref2[i + 1] = pref2[i] + f2[d];
            pref3[i + 1] = pref3[i] + f3[d];
            pref5[i + 1] = pref5[i] + f5[d];
            pref7[i + 1] = pref7[i] + f7[d];
        }

        // Try same length n
        int max_p = min(n - 1, first_zero);
        for (int p = max_p; p >= 0; --p) {
            int req2 = c2 - pref2[p];
            int req3 = c3 - pref3[p];
            int req5 = c5 - pref5[p];
            int req7 = c7 - pref7[p];

            int start_d = (p < n) ? (num[p] - '0' + 1) : 1;
            for (int d = start_d; d <= 9; ++d) {
                if (min_digits(req2 - f2[d], req3 - f3[d], req5 - f5[d], req7 - f7[d]) <= n - 1 - p) {
                    string ans = num.substr(0, p);
                    ans += (char)('0' + d);
                    ans += fill_suffix(n - 1 - p, req2 - f2[d], req3 - f3[d], req5 - f5[d], req7 - f7[d]);
                    return ans;
                }
            }
        }

        // Greater length needed
        int min_len_needed = min_digits(c2, c3, c5, c7);
        int target_len = max(n + 1, min_len_needed);
        return fill_suffix(target_len, c2, c3, c5, c7);
    }
};