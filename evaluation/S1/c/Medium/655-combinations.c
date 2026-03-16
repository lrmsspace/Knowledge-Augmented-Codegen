// Source: https://leetcode.com/problems/combinations/   |   Difficulty: Medium
//
// Problem Description:
// Given two integers n and k, return all possible combinations of k numbers chosen from the range [1, n].
//
// You may return the answer in any order.
//
// Example:
// Input: n = 4, k = 2
// Output: [[1,2],[1,3],[1,4],[2,3],[2,4],[3,4]]
// Explanation: There are 4 choose 2 = 6 total combinations.
// Note that combinations are unordered, i.e., [1,2] and [2,1] are considered to be the same combination.
//
// Constraints:
// 1 <= n <= 20
// 	1 <= k <= n
//
// Helpful references (internal KB):
// - Generating all K-combinations (bitset, recursion, enumeration)
//   • When to use: Use when an exhaustive list of all subsets of a specific size K from a set of N items is required. It's suitable for problems needing to explore every possible configuration of K elements.
//   • Idea: This algorithm systematically generates all unique subsets of size K from a set of N distinct elements, commonly employing recursion or bit manipulation. The typical time complexity is O(N choose K * K) for construction or O(N choose K) if just iterating.
//   • Invariants: The current partial combination always contains unique elements.; The number of elements chosen so far does not exceed K.
//   • Tips: Employ backtracking or recursion for a straightforward implementation.; Utilize bitmasks for efficient representation and generation, especially for smaller N.
//   • Pitfalls: Accidentally generating duplicate combinations if elements are not handled uniquely.; Failing to correctly define base cases or termination conditions for recursive calls.
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
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
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** combine(int n, int k, int* returnSize, int** returnColumnSizes) {
    int totalCombinations = 1;
    for (int i = 0; i < k; ++i) {
        totalCombinations = totalCombinations * (n - i) / (i + 1);
    }

    int** result = (int**)malloc(totalCombinations * sizeof(int*));
    *returnColumnSizes = (int*)malloc(totalCombinations * sizeof(int));
    *returnSize = 0;

    void backtrack(int start, int depth, int* currentCombination) {
        if (depth == k) {
            result[*returnSize] = (int*)malloc(k * sizeof(int));
            for (int i = 0; i < k; ++i) {
                result[*returnSize][i] = currentCombination[i];
            }
            (*returnColumnSizes)[*returnSize] = k;
            (*returnSize)++;
            return;
        }

        for (int i = start; i <= n - (k - depth); ++i) {
            currentCombination[depth] = i;
            backtrack(i + 1, depth + 1, currentCombination);
        }
    }

    int* currentCombination = (int*)malloc(k * sizeof(int));
    backtrack(1, 0, currentCombination);
    free(currentCombination);

    return result;      
}
