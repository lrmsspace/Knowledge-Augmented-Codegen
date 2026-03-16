// Source: https://leetcode.com/problems/manhattan-distances-of-all-arrangements-of-pieces/   |   Difficulty: Hard
//
// Problem Description:
// You are given three integers m, n, and k.
//
// There is a rectangular grid of size m × n containing k identical pieces. Return the sum of Manhattan distances between every pair of pieces over all valid arrangements of pieces.
//
// A valid arrangement is a placement of all k pieces on the grid with at most one piece per cell.
//
// Since the answer may be very large, return it modulo 109 + 7.
//
// The Manhattan Distance between two cells (xi, yi) and (xj, yj) is |xi - xj| + |yi - yj|.
//
// Example:
// Input: m = 2, n = 2, k = 2
//
// Output: 8
//
// Explanation:
//
// The valid arrangements of pieces on the board are:
//
//
//
//
// 	In the first 4 arrangements, the Manhattan distance between the two pieces is 1.
// 	In the last 2 arrangements, the Manhattan distance between the two pieces is 2.
//
//
// Thus, the total Manhattan distance across all valid arrangements is 1 + 1 + 1 + 1 + 2 + 2 = 8.
//
// Constraints:
// 1 <= m, n <= 105
// 	2 <= m * n <= 105
// 	2 <= k <= m * n
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int distanceSum(int m, int n, int k) {
        const int MOD = 1e9 + 7;
        long long totalDistance = 0;
        long long arrangements = 1;

        for (int i = 0; i < k; ++i) {
            arrangements = arrangements * (m * n - i) % MOD;
        }

        for (int i = 0; i < k; ++i) {
            totalDistance = (totalDistance + arrangements * (k - 1 - 2 * i) % MOD) % MOD;
            arrangements = arrangements * (m * n - k + i + 1) % MOD;
            arrangements = arrangements * modInverse(m * n - i, MOD) % MOD;
        }

        return totalDistance;           
    }
};
