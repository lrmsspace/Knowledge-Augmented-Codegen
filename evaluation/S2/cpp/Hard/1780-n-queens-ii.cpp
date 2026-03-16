// Source: https://leetcode.com/problems/n-queens-ii/   |   Difficulty: Hard
//
// Problem Description:
// The n-queens puzzle is the problem of placing n queens on an n x n chessboard such that no two queens attack each other.
//
// Given an integer n, return the number of distinct solutions to the n-queens puzzle.
//
// Example:
// Input: n = 4
// Output: 2
// Explanation: There are two distinct solutions to the 4-queens puzzle as shown.
//
// Constraints:
// 1 <= n <= 9
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
    int totalNQueens(int n) {
        int count = 0;
        vector<int> queens(n, -1); // queens[i] = j means a queen is placed at (i, j)
        solveNQueens(queens, 0, count);
        return count;           
    }
};
