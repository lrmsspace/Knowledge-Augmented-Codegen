// Source: https://leetcode.com/problems/guess-number-higher-or-lower-ii/   |   Difficulty: Medium
//
// Problem Description:
// We are playing the Guessing Game. The game will work as follows:
//
//
// 	I pick a number between 1 and n.
// 	You guess a number.
// 	If you guess the right number, you win the game.
// 	If you guess the wrong number, then I will tell you whether the number I picked is higher or lower, and you will continue guessing.
// 	Every time you guess a wrong number x, you will pay x dollars. If you run out of money, you lose the game.
//
//
// Given a particular n, return the minimum amount of money you need to guarantee a win regardless of what number I pick.
//
// Example:
// Input: n = 10
// Output: 16
// Explanation: The winning strategy is as follows:
// - The range is [1,10]. Guess 7.
//     - If this is my number, your total is $0. Otherwise, you pay $7.
//     - If my number is higher, the range is [8,10]. Guess 9.
//         - If this is my number, your total is $7. Otherwise, you pay $9.
//         - If my number is higher, it must be 10. Guess 10. Your total is $7 + $9 = $16.
//         - If my number is lower, it must be 8. Guess 8. Your total is $7 + $9 = $16.
//     - If my number is lower, the range is [1,6]. Guess 3.
//         - If this is my number, your total is $7. Otherwise, you pay $3.
//         - If my number is higher, the range is [4,6]. Guess 5.
//             - If this is my number, your total is $7 + $3 = $10. Otherwise, you pay $5.
//             - If my number is higher, it must be 6. Guess 6. Your total is $7 + $3 + $5 = $15.
//             - If my number is lower, it must be 4. Guess 4. Your total is $7 + $3 + $5 = $15.
//         - If my number is lower, the range is [1,2]. Guess 1.
//             - If this is my number, your total is $7 + $3 = $10. Otherwise, you pay $1.
//             - If my number is higher, it must be 2. Guess 2. Your total is $7 + $3 + $1 = $11.
// The worst case in all these scenarios is that you pay $16. Hence, you only need $16 to guarantee a win.
//
// Constraints:
// 1 <= n <= 200
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (matrix, array, dp-2d)
//   • When to use: Use this when you need to find a submatrix within a 2D array that yields the maximum or minimum possible sum of its elements. It's applicable when the problem can be reduced to multiple 1D maximum/minimum subarray sum problems.
//   • Idea: This technique extends the 1D maximum/minimum subarray sum problem to two dimensions. It typically involves iterating over all possible pairs of row (or column) boundaries, reducing the problem to a 1D array, and then applying a 1D dynamic programming approach like Kadane's algorithm, resulting in an O(N^3) time complexity for an N x N matrix.
//   • Invariants: For any fixed pair of top and bottom row indices (r1, r2), the temporary 1D array correctly represents the sum of elements in columns between r1 and r2.; Kadane's algorithm, when applied to the temporary 1D array, correctly finds the maximum/minimum subarray sum for that specific row range.
//   • Tips: Precompute prefix sums for rows to efficiently calculate column sums between fixed row boundaries.; The 2D problem can be reduced to multiple 1D problems by fixing two row indices and creating a temporary 1D array of column sums.
//   • Pitfalls: Incorrectly handling negative numbers when searching for maximum sum; Kadane's algorithm correctly handles this, but custom logic might fail.; Off-by-one errors when defining submatrix boundaries or calculating sums for the 1D reduction.
// - Linear Diophantine Equation (number, interval, enumeration)
//   • When to use: Use when you need to find or count all integer solutions (x, y) for a linear Diophantine equation ax + by = c, especially when solutions are constrained within specific intervals for x and y.
//   • Idea: This method finds all integer solutions to a linear Diophantine equation ax + by = c within given x and y intervals. It first finds a particular solution, then uses properties of the general solution to determine the valid range for x, and enumerates solutions in O(N) time where N is the number of solutions.
//   • Invariants: The current (x, y) pair always satisfies the linear Diophantine equation ax + by = c.; The current x value is an integer and satisfies the effective bounds l_x <= x <= r_x.
//   • Tips: Pre-divide coefficients a, b, c by gcd(a, b) to simplify the equation.; Use the Extended Euclidean Algorithm to find an initial particular solution (x0, y0).
//   • Pitfalls: Failing to check if c is divisible by gcd(a, b) before proceeding, leading to incorrect results.; Incorrectly applying the shifting logic for x and y bounds, resulting in an invalid solution range.
// - Games on arbitrary graphs (graph, array, dfs, game-theory)
//   • When to use: Use this algorithm to determine the outcome (win, lose, or draw) for every possible starting position in a two-player game played on a directed graph, assuming both players play optimally.
//   • Idea: This algorithm classifies each vertex in a directed graph as a winning, losing, or draw state for a two-player game. It iteratively applies rules based on neighbor states, optimized by a Depth-First Search on the reversed graph, achieving an O(M) time complexity.
//   • Invariants: A vertex `u` is a winning state if and only if it has at least one successor `v` that is a losing state.; A vertex `u` is a losing state if and only if all its successors `v` are winning states.
//   • Tips: Construct the reversed graph to efficiently propagate state classifications from successors to predecessors.; Initialize states for terminal vertices (those with no outgoing edges) as losing states.
//   • Pitfalls: Forgetting to account for draw states, which occur when neither winning nor losing conditions are met.; Incorrectly classifying terminal nodes; they are typically losing states in normal play games.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int getMoneyAmount(int n) {
        std::vector<std::vector<int>> dp(n + 2, std::vector<int>(n + 2, 0));
        
        for (int len = 2; len <= n; ++len) {
            for (int start = 1; start <= n - len + 1; ++start) {
                int end = start + len - 1;
                dp[start][end] = INT_MAX;
                for (int pivot = start; pivot <= end; ++pivot) {
                    int cost = pivot + std::max(dp[start][pivot - 1], dp[pivot + 1][end]);
                    dp[start][end] = std::min(dp[start][end], cost);
                }
            }
        }
        
        return dp[1][n];            
    }
};
