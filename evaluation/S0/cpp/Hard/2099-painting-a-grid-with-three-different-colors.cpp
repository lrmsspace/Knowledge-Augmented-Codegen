// Source: https://leetcode.com/problems/painting-a-grid-with-three-different-colors/   |   Difficulty: Hard
//
// Problem Description:
// You are given two integers m and n. Consider an m x n grid where each cell is initially white. You can paint each cell red, green, or blue. All cells must be painted.
//
// Return the number of ways to color the grid with no two adjacent cells having the same color. Since the answer can be very large, return it modulo 109 + 7.
//
// Example:
// Input: m = 1, n = 1
// Output: 3
// Explanation: The three possible colorings are shown in the image above.
//
// Constraints:
// 1 <= m <= 5
// 	1 <= n <= 1000
//

class Solution {
public:
    int colorTheGrid(int m, int n) {
        const int MOD = 1e9 + 7;
        vector<int> patterns;
        
        // Generate all valid patterns for a single column
        function<void(int, int)> generatePatterns = [&](int pattern, int length) {
            if (length == m) {
                patterns.push_back(pattern);
                return;
            }
            for (int color = 0; color < 3; color++) {
                if (length == 0 || (pattern / (int)pow(3, length - 1)) % 3 != color) {
                    generatePatterns(pattern + color * (int)pow(3, length), length + 1);
                }
            }
        };
        
        generatePatterns(0, 0);
        
        // Precompute compatibility between patterns
        int pSize = patterns.size();
        vector<vector<int>> compat(pSize);
        
        for (int i = 0; i < pSize; i++) {
            for (int j = 0; j < pSize; j++) {
                bool valid = true;
                for (int row = 0; row < m; row++) {
                    int color1 = (patterns[i] / (int)pow(3, row)) % 3;
                    int color2 = (patterns[j] / (int)pow(3, row)) % 3;
                    if (color1 == color2) {
                        valid = false;
                        break;
                    }
                }
                if (valid) {
                    compat[i].push_back(j);
                }
            }
        }
        
        // DP to count ways to fill the grid
        vector<long long> dp(pSize, 1);
        
        for (int col = 1; col < n; col++) {
            vector<long long> newDp(pSize, 0);
            for (int i = 0; i < pSize; i++) {
                for (int j : compat[i]) {
                    newDp[j] = (newDp[j] + dp[i]) % MOD;
                }
            }
            dp = newDp;
        }
        
        long long result = 0;
        for (long long count : dp) {
            result = (result + count) % MOD;
        }
        
        return (int)result;         
    }
};
