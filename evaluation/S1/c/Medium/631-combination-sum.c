// Source: https://leetcode.com/problems/combination-sum/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of distinct integers candidates and a target integer target, return a list of all unique combinations of candidates where the chosen numbers sum to target. You may return the combinations in any order.
//
// The same number may be chosen from candidates an unlimited number of times. Two combinations are unique if the frequency of at least one of the chosen numbers is different.
//
// The test cases are generated such that the number of unique combinations that sum up to target is less than 150 combinations for the given input.
//
// Example:
// Input: candidates = [2,3,6,7], target = 7
// Output: [[2,2,3],[7]]
// Explanation:
// 2 and 3 are candidates, and 2 + 2 + 3 = 7. Note that 2 can be used multiple times.
// 7 is a candidate, and 7 = 7.
// These are the only two combinations.
//
// Constraints:
// 1 <= candidates.length <= 30
// 	2 <= candidates[i] <= 40
// 	All elements of candidates are distinct.
// 	1 <= target <= 40
//
// Helpful references (internal KB):
// - Generating all K-combinations (bitset, recursion, enumeration)
//   • When to use: Use when an exhaustive list of all subsets of a specific size K from a set of N items is required. It's suitable for problems needing to explore every possible configuration of K elements.
//   • Idea: This algorithm systematically generates all unique subsets of size K from a set of N distinct elements, commonly employing recursion or bit manipulation. The typical time complexity is O(N choose K * K) for construction or O(N choose K) if just iterating.
//   • Invariants: The current partial combination always contains unique elements.; The number of elements chosen so far does not exceed K.
//   • Tips: Employ backtracking or recursion for a straightforward implementation.; Utilize bitmasks for efficient representation and generation, especially for smaller N.
//   • Pitfalls: Accidentally generating duplicate combinations if elements are not handled uniquely.; Failing to correctly define base cases or termination conditions for recursive calls.
// - Search the subarray with the maximum/minimum sum (array, binary-search-answer)
//   • When to use: Use when the problem asks for the minimum or maximum value that satisfies a monotonic condition.
//   • Idea: This technique finds a target value within a range by repeatedly dividing the search interval in half, based on a monotonic condition. It typically achieves O(log N) time complexity for a search space of size N.
//   • Invariants: The optimal answer always lies within the current search range [low, high].; All values less than 'low' (for min search) or greater than 'high' (for max search) are known to be non-optimal.
//   • Tips: Clearly define the search space [low, high] for the answer.; Implement a `check` function that determines if a given `mid` value is a feasible solution.
//   • Pitfalls: Incorrectly defining the search range [low, high] for the answer.; Errors in the `check` function leading to incorrect monotonicity or logic.
// - palindrome-partitioning (string, array, backtracking, recursion)
//   • When to use: Use this when you need to find all possible ways to break down a string into parts, where each part must satisfy a specific property. It is suitable for generating all combinations or permutations with constraints.
//   • Idea: This algorithm recursively explores all possible ways to partition a string into substrings, ensuring each substring is a palindrome. It employs a backtracking approach to build valid partitions incrementally, typically resulting in exponential time complexity.
//   • Invariants: At the start of each recursive call, the 'step' list contains a valid palindrome partition for the string segment processed so far.; The current processing index (or remaining string) always points to the unpartitioned suffix of the original input string.
//   • Tips: Utilize a helper function to manage additional state, such as the current partition path and the overall result list.; Pass the remaining string or a start index to recursive calls to define the subproblem for subsequent partitioning.
//   • Pitfalls: Forgetting to create a new copy of the current partition path before adding it to the final result list, leading to incorrect results.; Incorrectly defining the base case for recursion, which can cause infinite loops or missed valid partitions.
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
int** combinationSum(int* candidates, int candidatesSize, int target, int* returnSize, int** returnColumnSizes) {
    int **result = NULL;
    int *columnSizes = NULL;
    int resultSize = 0;
    int capacity = 0;

    void backtrack(int start, int remaining, int *path, int pathSize) {
        if (remaining == 0) {
            if (resultSize == capacity) {
                capacity = capacity == 0 ? 1 : capacity * 2;
                result = realloc(result, capacity * sizeof(int *));
                columnSizes = realloc(columnSizes, capacity * sizeof(int));
            }
            result[resultSize] = malloc(pathSize * sizeof(int));
            memcpy(result[resultSize], path, pathSize * sizeof(int));
            columnSizes[resultSize] = pathSize;
            resultSize++;
            return;
        }
        for (int i = start; i < candidatesSize; i++) {
            if (candidates[i] > remaining) continue;
            path[pathSize] = candidates[i];
            backtrack(i, remaining - candidates[i], path, pathSize + 1);
        }
    }

    int *path = malloc(target * sizeof(int));
    backtrack(0, target, path, 0);
    free(path);

    *returnSize = resultSize;
    *returnColumnSizes = columnSizes;
    return result;
}
