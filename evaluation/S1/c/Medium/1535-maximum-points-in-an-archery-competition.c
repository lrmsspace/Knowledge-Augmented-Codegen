// Source: https://leetcode.com/problems/maximum-points-in-an-archery-competition/   |   Difficulty: Medium
//
// Problem Description:
// Alice and Bob are opponents in an archery competition. The competition has set the following rules:
//
//
// 	Alice first shoots numArrows arrows and then Bob shoots numArrows arrows.
// 	The points are then calculated as follows:
// 	
// 		The target has integer scoring sections ranging from 0 to 11 inclusive.
// 		For each section of the target with score k (in between 0 to 11), say Alice and Bob have shot ak and bk arrows on that section respectively. If ak >= bk, then Alice takes k points. If ak < bk, then Bob takes k points.
// 		However, if ak == bk == 0, then nobody takes k points.
// 	
// 	
//
//
//
// 	
// 	For example, if Alice and Bob both shot 2 arrows on the section with score 11, then Alice takes 11 points. On the other hand, if Alice shot 0 arrows on the section with score 11 and Bob shot 2 arrows on that same section, then Bob takes 11 points.
// 	
//
//
// You are given the integer numArrows and an integer array aliceArrows of size 12, which represents the number of arrows Alice shot on each scoring section from 0 to 11. Now, Bob wants to maximize the total number of points he can obtain.
//
// Return the array bobArrows which represents the number of arrows Bob shot on each scoring section from 0 to 11. The sum of the values in bobArrows should equal numArrows.
//
// If there are multiple ways for Bob to earn the maximum total points, return any one of them.
//
// Example:
// Input: numArrows = 9, aliceArrows = [1,1,0,1,0,0,2,1,0,1,2,0]
// Output: [0,0,0,0,1,1,0,0,1,2,3,1]
// Explanation: The table above shows how the competition is scored. 
// Bob earns a total point of 4 + 5 + 8 + 9 + 10 + 11 = 47.
// It can be shown that Bob cannot obtain a score higher than 47 points.
//
// Constraints:
// 1 <= numArrows <= 105
// 	aliceArrows.length == bobArrows.length == 12
// 	0 <= aliceArrows[i], bobArrows[i] <= numArrows
// 	sum(aliceArrows[i]) == numArrows
//
// Helpful references (internal KB):
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
// - Dynamic Programming on Broken Profile. Problem "Parquet" (matrix, bitset, dp-2d, bitmask-dp)
//   • When to use: When problems involve tiling a grid or area with specific shapes, and the state can be represented by the 'profile' or boundary between processed and unprocessed cells, often using a bitmask.
//   • Idea: Dynamic Programming on Broken Profile is a technique used to solve tiling problems on grids by iterating through cells and maintaining the 'profile' of the boundary between filled and unfilled regions using a bitmask. This approach typically has a time complexity of O(N * M * 2^M) or O(N * M * 2^N), depending on the smaller dimension.
//   • Invariants: dp[row][mask] correctly stores the count of ways to tile the grid up to row-1, with mask representing the profile of row `row`.; All cells in rows 0 through `row-1` are completely and non-overlappingly tiled.
//   • Tips: Represent the profile as a bitmask where each bit indicates the state of a cell on the boundary.; Process the grid cell by cell, usually row by row, then column by column within a row.
//   • Pitfalls: Incorrectly defining the bitmask or its interpretation (e.g., which direction it represents).; Handling boundary conditions and edge cases for the grid dimensions.
// - Backtracking Algorithm (graph, backtracking, recursion, dfs)
//   • When to use: Used when exploring multiple possibilities to find a solution incrementally, often involving undoing choices if they lead to a dead end.
//   • Idea: Backtracking is a problem-solving technique that incrementally builds a solution by trying options and undoing them upon reaching a dead end. It typically explores a search space in a depth-first manner, often resulting in exponential time complexity.
//   • Invariants: The current partial solution is valid up to the current decision point.; All choices made to reach the current state can be systematically undone.
//   • Tips: Define clear base cases for recursive termination.; Identify decision points and available choices at each step.
//   • Pitfalls: Forgetting to undo changes (backtrack) after exploring a path.; Incorrectly defining base cases, leading to infinite recursion or wrong results.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* maximumBobPoints(int numArrows, int* aliceArrows, int aliceArrowsSize, int* returnSize) {
    int dp[13][numArrows + 1];
    int choice[13][numArrows + 1];
    for (int i = 0; i <= 12; i++) {
        for (int j = 0; j <= numArrows; j++) {
            dp[i][j] = 0;
            choice[i][j] = 0;
        }
    }

    for (int i = 11; i >= 0; i--) {
        int arrowsNeeded = aliceArrows[i] + 1;
        for (int j = 0; j <= numArrows; j++) {
            if (j >= arrowsNeeded) {
                int takePoints = i + dp[i + 1][j - arrowsNeeded];
                int skipPoints = dp[i + 1][j];
                if (takePoints > skipPoints) {
                    dp[i][j] = takePoints;
                    choice[i][j] = arrowsNeeded;
                } else {
                    dp[i][j] = skipPoints;
                    choice[i][j] = 0;
                }
            } else {
                dp[i][j] = dp[i + 1][j];
                choice[i][j] = 0;
            }
        }
    }

    int* bobArrows = (int*)calloc(12, sizeof(int));
    int remainingArrows = numArrows;
    for (int i = 0; i < 12; i++) {
        if (choice[i][remainingArrows] > 0) {
            bobArrows[i] = choice[i][remainingArrows];
            remainingArrows -= choice[i][remainingArrows];
        }
    }
    bobArrows[11] += remainingArrows;

    *returnSize = 12;
    return bobArrows;       
}
