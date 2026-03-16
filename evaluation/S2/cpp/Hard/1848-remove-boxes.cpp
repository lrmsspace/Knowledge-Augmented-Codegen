// Source: https://leetcode.com/problems/remove-boxes/   |   Difficulty: Hard
//
// Problem Description:
// You are given several boxes with different colors represented by different positive numbers.
//
// You may experience several rounds to remove boxes until there is no box left. Each time you can choose some continuous boxes with the same color (i.e., composed of k boxes, k >= 1), remove them and get k * k points.
//
// Return the maximum points you can get.
//
// Example:
// Input: boxes = [1,3,2,2,2,3,4,3,1]
// Output: 23
// Explanation:
// [1, 3, 2, 2, 2, 3, 4, 3, 1] 
// ----> [1, 3, 3, 4, 3, 1] (3*3=9 points) 
// ----> [1, 3, 3, 3, 1] (1*1=1 points) 
// ----> [1, 1] (3*3=9 points) 
// ----> [] (2*2=4 points)
//
// Constraints:
// 1 <= boxes.length <= 100
// 	1 <= boxes[i] <= 100
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
    int removeBoxes(vector<int>& boxes) {
        int n = boxes.size();
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(n, 0)));
        
        for (int i = 0; i < n; ++i) {
            for (int k = 0; k <= i; ++k) {
                dp[i][i][k] = (k + 1) * (k + 1);
            }
        }
        
        for (int length = 2; length <= n; ++length) {
            for (int i = 0; i <= n - length; ++i) {
                int j = i + length - 1;
                for (int k = 0; k <= i; ++k) {
                    dp[i][j][k] = dp[i][j-1][0] + (k + 1) * (k + 1);
                    for (int m = i; m < j; ++m) {
                        if (boxes[m] == boxes[j]) {
                            dp[i][j][k] = max(dp[i][j][k], dp[i][m][k + 1] + dp[m + 1][j - 1][0]);
                        }
                    }
                }
            }
        }
        
        return dp[0][n - 1][0];         
    }
};
