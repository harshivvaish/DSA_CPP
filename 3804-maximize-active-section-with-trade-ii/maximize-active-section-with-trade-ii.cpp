#pragma GCC optimize("O3", "unroll-loops")
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

// Standard I/O speedup for 0ms execution on LeetCode
static const int _ = []() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    return 0;
}();

// Sparse Table for O(1) Range Maximum Queries
struct SparseTable {
    int K;
    int N;
    vector<vector<int>> st;
    
    SparseTable() {}
    SparseTable(const vector<int>& arr) {
        N = arr.size();
        if (N == 0) return;
        K = 32 - __builtin_clz(N); // Fast log2
        st.assign(K, vector<int>(N));
        
        for (int i = 0; i < N; i++) st[0][i] = arr[i];
        
        for (int k = 1; k < K; k++) {
            int step = 1 << (k - 1);
            for (int i = 0; i + (step * 2) <= N; i++) {
                st[k][i] = max(st[k - 1][i], st[k - 1][i + step]);
            }
        }
    }
    
    int query(int L, int R) const {
        if (L > R) return 0;
        int len = R - L + 1;
        int k = 31 - __builtin_clz(len); // Fast O(1) interval size calculation
        return max(st[k][L], st[k][R - (1 << k) + 1]);
    }
};

class Solution {
public:
    vector<int> maxActiveSectionsAfterTrade(string s, vector<vector<int>>& queries) {
        int n = s.length();
        int total_ones = 0;
        
        for (char c : s) {
            if (c == '1') total_ones++;
        }
        
        // Step 1: Condense continuous '0' blocks
        vector<pair<int, int>> blocks;
        int i = 0;
        while (i < n) {
            if (s[i] == '0') {
                int start = i;
                while (i < n && s[i] == '0') i++;
                blocks.push_back({start, i - 1});
            } else {
                i++;
            }
        }
        
        int M = blocks.size();
        
        // Precalculate boundary intersections for O(1) lookup
        vector<int> first_intersect(n, -1);
        vector<int> last_intersect(n, -1);
        
        int ptr = 0;
        for(int j = 0; j < n; ++j) {
            while(ptr < M && blocks[ptr].second < j) ptr++;
            if (ptr < M) first_intersect[j] = ptr;
        }
        
        ptr = M - 1;
        for(int j = n - 1; j >= 0; --j) {
            while(ptr >= 0 && blocks[ptr].first > j) ptr--;
            if (ptr >= 0) last_intersect[j] = ptr;
        }
        
        vector<int> full_len(M);
        for(int j = 0; j < M; ++j) {
            full_len[j] = blocks[j].second - blocks[j].first + 1;
        }
        
        vector<int> pair_sum;
        if (M >= 2) {
            pair_sum.resize(M - 1);
            for(int j = 0; j < M - 1; ++j) {
                pair_sum[j] = full_len[j] + full_len[j+1];
            }
        }
        
        SparseTable st(pair_sum);
        
        // Helper lambda to get exact intersecting length of a block within window
        auto get_len = [&](int idx, int L, int R) {
            int start = max(L, blocks[idx].first);
            int end = min(R, blocks[idx].second);
            if (start > end) return 0;
            return end - start + 1;
        };
        
        vector<int> ans;
        ans.reserve(queries.size());
        
        // Step 2: O(1) query processing
        for (auto& q : queries) {
            int L = q[0], R = q[1];
            int fg = first_intersect[L];
            int lg = last_intersect[R];
            
            int max_gain = 0;
            
            // If at least two blocks intersect the query window
            if (fg != -1 && lg != -1 && fg < lg) {
                if (fg + 1 == lg) {
                    // Exactly two blocks intersecting
                    max_gain = get_len(fg, L, R) + get_len(lg, L, R);
                } else {
                    // Edge blocks (partially truncated by L or R) + inner blocks
                    max_gain = max(get_len(fg, L, R) + full_len[fg+1],
                                   full_len[lg-1] + get_len(lg, L, R));
                    
                    // Internal blocks completely encompassed by the window
                    if (lg - 2 >= fg + 1) {
                        max_gain = max(max_gain, st.query(fg + 1, lg - 2));
                    }
                }
            }
            
            ans.push_back(total_ones + max_gain);
        }
        
        return ans;
    }
};