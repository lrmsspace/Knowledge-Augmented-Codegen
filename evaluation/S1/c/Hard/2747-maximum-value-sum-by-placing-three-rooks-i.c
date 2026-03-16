// Source: https://leetcode.com/problems/maximum-value-sum-by-placing-three-rooks-i/   |   Difficulty: Hard
//
// Problem Description:
// You are given a m x n 2D array board representing a chessboard, where board[i][j] represents the value of the cell (i, j).
//
// Rooks in the same row or column attack each other. You need to place three rooks on the chessboard such that the rooks do not attack each other.
//
// Return the maximum sum of the cell values on which the rooks are placed.
//
// Example:
// Input: board = [[-3,1,1,1],[-3,1,-3,1],[-3,2,1,1]]
//
// Output: 4
//
// Explanation:
//
//
//
// We can place the rooks in the cells (0, 2), (1, 3), and (2, 1) for a sum of 1 + 1 + 2 = 4.
//
// Constraints:
// 3 <= m == board.length <= 100
// 	3 <= n == board[i].length <= 100
// 	-109 <= board[i][j] <= 109
//
// Helpful references (internal KB):
// - Knapsack Problem (array, knapsack, dp-1d, enumeration)
//   • When to use: Use when selecting items from a set to maximize or minimize a value under a capacity constraint. It's also applicable for partitioning problems with a fixed budget.
//   • Idea: This algorithm finds the maximum value that can be obtained by selecting a subset of items, each with a weight and a value, such that their total weight does not exceed a given capacity. It typically uses dynamic programming with a time complexity of O(N*W), where N is the number of items and W is the capacity.
//   • Invariants: After processing item `i`, `dp[w]` stores the maximum value for capacity `w` using items up to `i`.; For each item, `dp[w]` is updated considering either including or excluding the current item.
//   • Tips: Use a 2D DP table `dp[i][w]` for item `i` and weight `w` for clarity, then optimize to 1D.; When optimizing to 1D, iterate weights downwards to avoid using an item multiple times.
//   • Pitfalls: Incorrectly initializing the DP table can lead to wrong results or infinite loops.; Forgetting to iterate weights downwards in 1D DP can lead to items being picked multiple times (unbounded knapsack).
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Placing Bishops on a Chessboard (array, matrix, dp-2d, recursion)
//   • When to use: Use this approach for counting arrangements of non-attacking pieces on a grid, particularly when piece movement is restricted to specific geometric lines like diagonals. It is effective when constraints allow for independent processing of subsets of the grid.
//   • Idea: This method employs 2D dynamic programming to count the number of ways to place bishops on a chessboard such that no two bishops attack each other. It leverages the property that bishops only attack along diagonals of the same color, processing diagonals iteratively to build up solutions in polynomial time.
//   • Invariants: All bishops placed on diagonals with index less than `i` do not attack each other.; The count `D[i][j]` correctly reflects all valid placements of `j` bishops on diagonals up to `i` of the same color.
//   • Tips: Exploit problem-specific constraints, such as bishop movement along diagonals, to simplify state definitions.; Decompose the problem by processing diagonals of the same color independently to avoid complex interactions.
//   • Pitfalls: Incorrectly handling diagonal numbering or miscalculating the number of squares in a diagonal.; Off-by-one errors when determining the number of available squares for placing a bishop on a diagonal.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

long long maximumValueSum(int** board, int boardSize, int* boardColSize) {
    int m = boardSize;
    int n = boardColSize[0];
    int diagCount = m + n - 1;

    /* Separate diagonals into two colors based on (i + j) % 2 */
    int blackDiagCount = (diagCount + 1) / 2;
    int whiteDiagCount = diagCount / 2;

    /* Count available squares in each diagonal */
    int blackSquares[blackDiagCount];
    int whiteSquares[whiteDiagCount];
    memset(blackSquares, 0, sizeof(blackSquares));
    memset(whiteSquares, 0, sizeof(whiteSquares));

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            int diagIndex = i + j;
            if (diagIndex % 2 == 0) {
                blackSquares[diagIndex / 2]++;
            } else {
                whiteSquares[diagIndex / 2]++;
            }
        }
    }

    /* DP arrays for counting placements */
    long long blackDP[blackDiagCount + 1][4];
    long long whiteDP[whiteDiagCount + 1][4];
    memset(blackDP, 0, sizeof(blackDP));
    memset(whiteDP, 0, sizeof(whiteDP));

    blackDP[0][0] = 1;
    for (int i = 1; i <= blackDiagCount; i++) {
        for (int j = 0; j <= 3; j++) {
            blackDP[i][j] = blackDP[i - 1][j];
            if (j > 0 && blackSquares[i - 1] > 0) {
                blackDP[i][j] += blackDP[i - 1][j - 1] * blackSquares[i - 1];
            }
        }
    }

    whiteDP[0][0] = 1;
    for (int i = 1; i <= whiteDiagCount; i++) {
        for (int j = 0; j <= 3; j++) {
            whiteDP[i][j] = whiteDP[i - 1][j];
            if (j > 0 && whiteSquares[i - 1] > 0) {
                whiteDP[i][j] += whiteDP[i - 1][j - 1] * whiteSquares[i - 1];
            }
        }
    }
    /* Collect cell values for each diagonal */
    long long blackValues[blackDiagCount][100];
    long long whiteValues[whiteDiagCount][100];
    memset(blackValues, 0, sizeof(blackValues));
    memset(whiteValues, 0, sizeof(whiteValues));
    int blackCounts[blackDiagCount];
    int whiteCounts[whiteDiagCount];
    memset(blackCounts, 0, sizeof(blackCounts));
    memset(whiteCounts, 0, sizeof(whiteCounts));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            int diagIndex = i + j;
            if (diagIndex % 2 == 0) {
                blackValues[diagIndex / 2][blackCounts[diagIndex / 2]++] = board[i][j];
            } else {
                whiteValues[diagIndex / 2][whiteCounts[diagIndex / 2]++] = board[i][j];
            }
        }
    }
    /* Sort values in descending order */
    for (int i = 0; i < blackDiagCount; i++) {
        qsort(blackValues[i], blackCounts[i], sizeof(long long), [](const void* a, const void* b) {
            long long valA = *(long long*)a;
            long long valB = *(long long*)b;
            return (valA < valB) ? 1 : (valA > valB) ? -1 : 0;
        });
    }
    for (int i = 0; i < whiteDiagCount; i++) {
        qsort(whiteValues[i], whiteCounts[i], sizeof(long long), [](const void* a, const void* b) {
            long long valA = *(long long*)a;
            long long valB = *(long long*)b;
            return (valA < valB) ? 1 : (valA > valB) ? -1 : 0;
        });
    }
    /* Calculate maximum sum by placing 3 rooks */
    long long maxSum = -0x7FFFFFFFFFFFFFFFLL;

    for (int b = 0; b <= 3; b++) {
        int w = 3 - b;
        if (blackDP[blackDiagCount][b] == 0 || whiteDP[whiteDiagCount][w] == 0) {
            continue;
        }
        long long currentSum = 0;
        /* Sum top b values from black diagonals */
        int placed = 0;
        for (int i = 0; i < blackDiagCount && placed < b; i++) {
            for (int j = 0; j < blackCounts[i] && placed < b; j++) {
                currentSum += blackValues[i][j];
                placed++;
            }
        }
        /* Sum top w values from white diagonals */
        placed = 0;
        for (int i = 0; i < whiteDiagCount && placed < w; i++) {
            for (int j = 0; j < whiteCounts[i] && placed < w; j++) {
                currentSum += whiteValues[i][j];
                placed++;
            }
        }
        if (currentSum > maxSum) {
            maxSum = currentSum;
        }
    }
    return maxSum;
}
