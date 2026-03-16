// Source: https://leetcode.com/problems/find-the-number-of-distinct-colors-among-the-balls/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer limit and a 2D array queries of size n x 2.
//
// There are limit + 1 balls with distinct labels in the range [0, limit]. Initially, all balls are uncolored. For every query in queries that is of the form [x, y], you mark ball x with the color y. After each query, you need to find the number of colors among the balls.
//
// Return an array result of length n, where result[i] denotes the number of colors after ith query.
//
// Note that when answering a query, lack of a color will not be considered as a color.
//
// Example:
// Input: limit = 4, queries = [[1,4],[2,5],[1,3],[3,4]]
//
// Output: [1,2,2,3]
//
// Explanation:
//
//
//
//
// 	After query 0, ball 1 has color 4.
// 	After query 1, ball 1 has color 4, and ball 2 has color 5.
// 	After query 2, ball 1 has color 3, and ball 2 has color 5.
// 	After query 3, ball 1 has color 3, ball 2 has color 5, and ball 3 has color 4.
//
// Constraints:
// 1 <= limit <= 109
// 	1 <= n == queries.length <= 105
// 	queries[i].length == 2
// 	0 <= queries[i][0] <= limit
// 	1 <= queries[i][1] <= 109
//
// Helpful references (internal KB):
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - Sparse Table (array, sparse-table, enumeration)
//   • When to use: Use when you need to perform many range queries on a static array, especially when the query operation is associative and idempotent, allowing for O(1) query time after O(N log N) precomputation.
//   • Idea: A Sparse Table is a data structure that precomputes answers for all possible range queries of power-of-two lengths. It allows O(1) query time for idempotent operations like min/max/gcd and O(log N) for non-idempotent associative operations, after an O(N log N) build time.
//   • Invariants: After precomputation, dp[k][i] stores the result for the range [i, i + 2^k - 1].; For any k > 0, dp[k][i] is the result of combining dp[k-1][i] and dp[k-1][i + 2^(k-1)].
//   • Tips: Precompute log2 values for faster range length calculations.; Store dp[k][i] as the result for range [i, i + 2^k - 1].
//   • Pitfalls: Does not support updates to array elements efficiently.; Requires O(N log N) space, which can be significant for large N.
// - Placing Bishops on a Chessboard (array, matrix, dp-2d, recursion)
//   • When to use: Use this approach for counting arrangements of non-attacking pieces on a grid, particularly when piece movement is restricted to specific geometric lines like diagonals. It is effective when constraints allow for independent processing of subsets of the grid.
//   • Idea: This method employs 2D dynamic programming to count the number of ways to place bishops on a chessboard such that no two bishops attack each other. It leverages the property that bishops only attack along diagonals of the same color, processing diagonals iteratively to build up solutions in polynomial time.
//   • Invariants: All bishops placed on diagonals with index less than `i` do not attack each other.; The count `D[i][j]` correctly reflects all valid placements of `j` bishops on diagonals up to `i` of the same color.
//   • Tips: Exploit problem-specific constraints, such as bishop movement along diagonals, to simplify state definitions.; Decompose the problem by processing diagonals of the same color independently to avoid complex interactions.
//   • Pitfalls: Incorrectly handling diagonal numbering or miscalculating the number of squares in a diagonal.; Off-by-one errors when determining the number of available squares for placing a bishop on a diagonal.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    vector<int> queryResults(int limit, vector<vector<int>>& queries) {
        unordered_map<int, int> ballColor; // ball -> color
        unordered_map<int, int> colorCount; // color -> count of balls with this color
        int distinctColors = 0;
        vector<int> results;
        results.reserve(queries.size());

        for (const auto& q : queries) {
            int ball = q[0];
            int color = q[1];

            // If the ball already has a color, decrement the count of that color
            if (ballColor.find(ball) != ballColor.end()) {
                int oldColor = ballColor[ball];
                colorCount[oldColor]--;
                if (colorCount[oldColor] == 0) {
                    distinctColors--;
                    colorCount.erase(oldColor);
                }
            }

            // Assign the new color to the ball
            ballColor[ball] = color;
            colorCount[color]++;
            if (colorCount[color] == 1) {
                distinctColors++;
            }

            results.push_back(distinctColors);
        }

        return results;         
    }
};
