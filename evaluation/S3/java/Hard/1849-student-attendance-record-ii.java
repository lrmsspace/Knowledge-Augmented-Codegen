// Source: https://leetcode.com/problems/student-attendance-record-ii/   |   Difficulty: Hard
//
// Problem Description:
// An attendance record for a student can be represented as a string where each character signifies whether the student was absent, late, or present on that day. The record only contains the following three characters:
//
//
// 	'A': Absent.
// 	'L': Late.
// 	'P': Present.
//
//
// Any student is eligible for an attendance award if they meet both of the following criteria:
//
//
// 	The student was absent ('A') for strictly fewer than 2 days total.
// 	The student was never late ('L') for 3 or more consecutive days.
//
//
// Given an integer n, return the number of possible attendance records of length n that make a student eligible for an attendance award. The answer may be very large, so return it modulo 109 + 7.
//
// Example:
// Input: n = 2
// Output: 8
// Explanation: There are 8 records with length 2 that are eligible for an award:
// "PP", "AP", "PA", "LP", "PL", "AL", "LA", "LL"
// Only "AA" is not eligible because there are 2 absences (there need to be fewer than 2).
//
// Constraints:
// 1 <= n <= 105
//
// Helpful references (internal KB):
// - Placing Bishops on a Chessboard (array, matrix, dp-2d, recursion)
//   • When to use: Use this approach for counting arrangements of non-attacking pieces on a grid, particularly when piece movement is restricted to specific geometric lines like diagonals. It is effective when constraints allow for independent processing of subsets of the grid.
//   • Idea: This method employs 2D dynamic programming to count the number of ways to place bishops on a chessboard such that no two bishops attack each other. It leverages the property that bishops only attack along diagonals of the same color, processing diagonals iteratively to build up solutions in polynomial time.
//   • Invariants: All bishops placed on diagonals with index less than `i` do not attack each other.; The count `D[i][j]` correctly reflects all valid placements of `j` bishops on diagonals up to `i` of the same color.
//   • Tips: Exploit problem-specific constraints, such as bishop movement along diagonals, to simplify state definitions.; Decompose the problem by processing diagonals of the same color independently to avoid complex interactions.
//   • Pitfalls: Incorrectly handling diagonal numbering or miscalculating the number of squares in a diagonal.; Off-by-one errors when determining the number of available squares for placing a bishop on a diagonal.
// - Digit DP (array, number, digit-dp)
//   • When to use: Use Digit DP to count numbers within a given range [a, b] that satisfy a property based on their digits. It's effective when the property can be checked digit by digit.
//   • Idea: Digit DP is a dynamic programming technique to count numbers within a given range [A, B] that satisfy specific properties related to their digits. It typically involves a recursive function with memoization, building numbers digit by digit, and has a complexity roughly proportional to (number of digits * state space).
//   • Invariants: The `tight` parameter accurately reflects if the current prefix matches the upper bound's prefix.; The `is_leading_zero` parameter correctly indicates if all preceding digits chosen were zero.
//   • Tips: Define the DP state carefully, including index, tight constraint, and leading zero flag.; Handle leading zeros correctly, as they can affect properties like sum or count of digits.
//   • Pitfalls: Incorrectly handling the 'tight' constraint, leading to overcounting or undercounting.; Forgetting to account for leading zeros or mismanaging their impact on the property.
// - Placing Bishops on a Chessboard (array, counting, dp-2d)
//   • When to use: Use when counting non-attacking piece placements on a grid, especially when the problem can be decomposed into independent subproblems based on board properties like diagonals.
//   • Idea: This algorithm employs 2D dynamic programming to count the total number of ways to place non-attacking bishops on a chessboard. It leverages the independence of placements on black and white squares/diagonals, achieving a polynomial time complexity.
//   • Invariants: For any diagonal `i`, `D[i][j]` represents the number of ways to place `j` bishops on diagonal `i`.; Bishops placed on black diagonals do not attack bishops placed on white diagonals.
//   • Tips: Decompose the problem into independent subproblems for black and white squares/diagonals.; Identify the state for DP, typically `dp[diagonal_index][bishops_placed]`.
//   • Pitfalls: Incorrectly calculating the number of squares on each diagonal.; Overlapping bishops if diagonal definitions are not precise.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int checkRecord(int n) {
        int mod = 1000000007;
        long[][] dp = new long[n + 1][3];
        dp[0][0] = 1; // Base case: 0 days, 0 absences

        for (int i = 1; i <= n; i++) {
            // Case 1: Ending with 'P'
            dp[i][0] = (dp[i - 1][0] + dp[i - 1][1] + dp[i - 1][2]) % mod;

            // Case 2: Ending with 'A'
            dp[i][1] = (dp[i - 1][0] + dp[i - 1][1] + dp[i - 1][2]) % mod;

            // Case 3: Ending with 'L'
            dp[i][2] = (dp[i - 1][0] + dp[i - 1][2]) % mod;
        }

        long result = (dp[n][0] + dp[n][1] + dp[n][2]) % mod;
        return (int) result;            
    }
}
