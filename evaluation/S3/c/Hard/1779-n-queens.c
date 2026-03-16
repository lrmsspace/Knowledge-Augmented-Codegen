// Source: https://leetcode.com/problems/n-queens/   |   Difficulty: Hard
//
// Problem Description:
// The n-queens puzzle is the problem of placing n queens on an n x n chessboard such that no two queens attack each other.
//
// Given an integer n, return all distinct solutions to the n-queens puzzle. You may return the answer in any order.
//
// Each solution contains a distinct board configuration of the n-queens' placement, where 'Q' and '.' both indicate a queen and an empty space, respectively.
//
// Example:
// Input: n = 4
// Output: [[".Q..","...Q","Q...","..Q."],["..Q.","Q...","...Q",".Q.."]]
// Explanation: There exist two distinct solutions to the 4-queens puzzle as shown above
//
// Constraints:
// 1 <= n <= 9
//
// Helpful references (internal KB):
// - Generating all K-combinations (bitset, recursion, enumeration)
//   • When to use: Use when an exhaustive list of all subsets of a specific size K from a set of N items is required. It's suitable for problems needing to explore every possible configuration of K elements.
//   • Idea: This algorithm systematically generates all unique subsets of size K from a set of N distinct elements, commonly employing recursion or bit manipulation. The typical time complexity is O(N choose K * K) for construction or O(N choose K) if just iterating.
//   • Invariants: The current partial combination always contains unique elements.; The number of elements chosen so far does not exceed K.
//   • Tips: Employ backtracking or recursion for a straightforward implementation.; Utilize bitmasks for efficient representation and generation, especially for smaller N.
//   • Pitfalls: Accidentally generating duplicate combinations if elements are not handled uniquely.; Failing to correctly define base cases or termination conditions for recursive calls.
// - Generating all K-combinations (bitset, enumeration)
//   • When to use: When all subsets of a fixed size K need to be generated, either in lexicographical order or such that successive combinations differ by exactly one element.
//   • Idea: This algorithm enumerates all K-combinations from a set, either in lexicographical order or using a Gray code approach where adjacent combinations differ by a single element. It typically runs in O(N choose K) time, generating each combination in O(K) or O(1) amortized time.
//   • Invariants: Each generated combination contains exactly K distinct elements.; All elements within a combination are unique and from the original set.
//   • Tips: For lexicographical generation, find the rightmost element that can be incremented without exceeding its maximum possible value.; After incrementing an element, set all subsequent elements to their minimum valid values.
//   • Pitfalls: Incorrectly handling boundary conditions for the rightmost element or its maximum value.; Off-by-one errors when assigning subsequent elements after an increment.
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

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
char*** solveNQueens(int n, int* returnSize, int** returnColumnSizes) {
    // Step 1: Initialize the board and result storage
    char*** result = (char***)malloc(1000 * sizeof(char**)); // Allocate memory for up to 1000 solutions
    *returnColumnSizes = (int*)malloc(1000 * sizeof(int)); // Allocate memory for column sizes
    int resultSize = 0; // To keep track of the number of solutions found

    // Step 2: Create a board representation
    char** board = (char**)malloc(n * sizeof(char*));
    for (int i = 0; i < n; i++) {
        board[i] = (char*)malloc((n + 1) * sizeof(char)); // +1 for null terminator
        memset(board[i], '.', n); // Initialize with '.'
        board[i][n] = '\0'; // Null terminate each row
    }

    // Step 3: Backtracking function to place queens
    void backtrack(int row, int* columns, int* diag1, int* diag2) {
        if (row == n) {
            // Found a valid solution, add it to the result
            result[resultSize] = (char**)malloc(n * sizeof(char*));
            for (int i = 0; i < n; i++) {
                result[resultSize][i] = strdup(board[i]); // Duplicate the current board state
            }
            (*returnColumnSizes)[resultSize] = n; // Each solution has n rows
            resultSize++;
            return;
        }

        for (int col = 0; col < n; col++) {
            if (!columns[col] && !diag1[row + col] && !diag2[row - col + n - 1]) {
                // Place a queen at (row, col)
                board[row][col] = 'Q';
                columns[col] = diag1[row + col] = diag2[row - col + n - 1] = 1;

                // Recur to place queens in the next row
                backtrack(row + 1, columns, diag1, diag2);

                // Backtrack: remove the queen and reset the markers
                board[row][col] = '.';
                columns[col] = diag1[row + col] = diag2[row - col + n - 1] = 0;
            }
        }
    }

    // Step 4: Initialize helper arrays for tracking columns and diagonals
    int* columns = (int*)calloc(n, sizeof(int)); // To track occupied columns
    int* diag1 = (int*)calloc(2 * n - 1, sizeof(int)); // To track occupied major diagonals
    int* diag2 = (int*)calloc(2 * n - 1, sizeof(int)); // To track occupied minor diagonals

    // Step 5: Start backtracking from the first row
    backtrack(0, columns, diag1, diag2);
    *returnSize = resultSize;
    return result;
            
}
