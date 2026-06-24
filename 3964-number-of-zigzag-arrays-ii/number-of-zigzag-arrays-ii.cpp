#include <vector>

using namespace std;

class Solution {
private:
    long long MOD = 1e9 + 7;

    // Helper function to multiply two matrices
    vector<vector<long long>> multiply(const vector<vector<long long>>& A, const vector<vector<long long>>& B, int S) {
        vector<vector<long long>> C(S, vector<long long>(S, 0));
        for (int i = 0; i < S; i++) {
            for (int k = 0; k < S; k++) {
                if (A[i][k] == 0) continue;
                for (int j = 0; j < S; j++) {
                    C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
                }
            }
        }
        return C;
    }

    // Helper function for binary matrix exponentiation
    vector<vector<long long>> power(vector<vector<long long>> A, long long p, int S) {
        vector<vector<long long>> res(S, vector<long long>(S, 0));
        for (int i = 0; i < S; i++) res[i][i] = 1; // Identity matrix
        
        while (p > 0) {
            if (p & 1) res = multiply(res, A, S);
            A = multiply(A, A, S);
            p >>= 1;
        }
        return res;
    }

public:
    int zigZagArrays(int n, int l, int r) {
        int M = r - l + 1;
        int S = 2 * M; // Total states (Each number can be reached via a DOWN or UP move)

        // T[u][v] represents transition from state u to state v
        // State encoding: 
        // 2 * i     -> element value i, last move went DOWN
        // 2 * i + 1 -> element value i, last move went UP
        vector<vector<long long>> T(S, vector<long long>(S, 0));

        for (int i = 0; i < M; i++) {
            for (int j = 0; j < M; j++) {
                if (i == j) continue;

                // From (i, DOWN), next must go UP (j > i) to stay ZigZag
                if (j > i) {
                    T[2 * i][2 * j + 1] = 1;
                }
                // From (i, UP), next must go DOWN (j < i) to stay ZigZag
                if (j < i) {
                    T[2 * i + 1][2 * j] = 1;
                }
            }
        }

        // We jump from length 2 to length n, which takes exactly (n - 2) transitions
        vector<vector<long long>> T_pow = power(T, n - 2, S);

        // Calculate initial counts for arrays of length 2
        vector<long long> initial(S, 0);
        for (int first = 0; first < M; first++) {
            for (int second = 0; second < M; second++) {
                if (first == second) continue;
                if (second > first) {
                    initial[2 * second + 1]++; // Valid UP transition
                } else {
                    initial[2 * second]++;     // Valid DOWN transition
                }
            }
        }

        // Multiply the initial row vector by the transitioned matrix to find total combinations
        long long total_valid_arrays = 0;
        for (int j = 0; j < S; j++) {
            long long final_state_count = 0;
            for (int i = 0; i < S; i++) {
                final_state_count = (final_state_count + initial[i] * T_pow[i][j]) % MOD;
            }
            total_valid_arrays = (total_valid_arrays + final_state_count) % MOD;
        }

        return total_valid_arrays;
    }
};