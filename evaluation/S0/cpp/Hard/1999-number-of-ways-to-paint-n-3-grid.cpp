// Source: https://leetcode.com/problems/number-of-ways-to-paint-n-3-grid/   |   Difficulty: Hard
//
// Problem Description:
// You have a grid of size n x 3 and you want to paint each cell of the grid with exactly one of the three colors: Red, Yellow, or Green while making sure that no two adjacent cells have the same color (i.e., no two cells that share vertical or horizontal sides have the same color).
//
// Given n the number of rows of the grid, return the number of ways you can paint this grid. As the answer may grow large, the answer must be computed modulo 109 + 7.
//
// Example:
// Input: n = 1
// Output: 12
// Explanation: There are 12 possible way to paint the grid as shown.
//
// Constraints:
// n == grid.length
// 	1 <= n <= 5000
//

class Solution {
public:
    int numOfWays(int n) {
        const int MOD = 1e9 + 7;
        // a: patterns like ABA
        // b: patterns like ABC
        long long a = 6; // For n=1, there are 6 patterns of type ABA
        long long b = 6; // For n=1, there are 6 patterns of type ABC
        
        for (int i = 2; i <= n; i++) {
            long long newA = (3 * a + 2 * b) % MOD;
            long long newB = (2 * a + 2 * b) % MOD;
            a = newA;
            b = newB;
        }
        
        return (a + b) % MOD;           
    }
};
