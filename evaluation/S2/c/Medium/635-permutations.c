// Source: https://leetcode.com/problems/permutations/   |   Difficulty: Medium
//
// Problem Description:
// Given an array nums of distinct integers, return all the possible permutations. You can return the answer in any order.
//
// Example:
// Input: nums = [1,2,3]
// Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
//
// Constraints:
// 1 <= nums.length <= 6
// 	-10 <= nums[i] <= 10
// 	All the integers of nums are unique.
//
// Helpful references (internal KB):
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - palindrome-partitioning (string, array, backtracking, recursion)
//   • When to use: Use this when you need to find all possible ways to break down a string into parts, where each part must satisfy a specific property. It is suitable for generating all combinations or permutations with constraints.
//   • Idea: This algorithm recursively explores all possible ways to partition a string into substrings, ensuring each substring is a palindrome. It employs a backtracking approach to build valid partitions incrementally, typically resulting in exponential time complexity.
//   • Invariants: At the start of each recursive call, the 'step' list contains a valid palindrome partition for the string segment processed so far.; The current processing index (or remaining string) always points to the unpartitioned suffix of the original input string.
//   • Tips: Utilize a helper function to manage additional state, such as the current partition path and the overall result list.; Pass the remaining string or a start index to recursive calls to define the subproblem for subsequent partitioning.
//   • Pitfalls: Forgetting to create a new copy of the current partition path before adding it to the final result list, leading to incorrect results.; Incorrectly defining the base case for recursion, which can cause infinite loops or missed valid partitions.
// - Non-negative Integers without Consecutive Ones (number, recursion, backtracking)
//   • When to use: Use when counting numbers within a range that satisfy a specific digit-based or bit-based pattern constraint, especially when the constraint involves adjacent digits or bits.
//   • Idea: This algorithm recursively generates binary numbers bit by bit, ensuring no two consecutive ones are formed. It prunes branches that exceed a given upper limit or violate the consecutive one constraint, effectively counting valid numbers up to N in O(log N) time.
//   • Invariants: The `sum` generated so far never exceeds the target `num`.; The `prev` boolean accurately reflects whether the last bit added was a '1'.
//   • Tips: Generate numbers bit by bit, typically from LSB or MSB, to build up valid sequences.; Maintain state about the previously placed bit to enforce the 'no consecutive ones' rule.
//   • Pitfalls: Failing to correctly handle the base cases for the recursive function.; Incorrectly managing the 'previous bit' state, leading to invalid sequences.
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
int** permute(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
    // Calculate the total number of permutations (n!)
    int totalPermutations = 1;
    for (int i = 1; i <= numsSize; i++) {
        totalPermutations *= i;
    }

    // Allocate memory for the result array and column sizes
    int** result = (int**)malloc(totalPermutations * sizeof(int*));
    *returnColumnSizes = (int*)malloc(totalPermutations * sizeof(int));
    
    // Helper function to generate permutations using backtracking
    void backtrack(int* current, int* used, int depth) {
        if (depth == numsSize) {
            // Found a complete permutation, add it to the result
            result[*returnSize] = (int*)malloc(numsSize * sizeof(int));
            for (int i = 0; i < numsSize; i++) {
                result[*returnSize][i] = current[i];
            }
            (*returnColumnSizes)[*returnSize] = numsSize;
            (*returnSize)++;
            return;
        }
        
        for (int i = 0; i < numsSize; i++) {
            if (!used[i]) {
                // Mark the number as used and add it to the current permutation
                used[i] = 1;
                current[depth] = nums[i];
                
                // Recur with the next depth
                backtrack(current, used, depth + 1);
                
                // Backtrack: unmark the number and remove it from the current permutation
                used[i] = 0;
            }
        }
    }

    // Initialize variables for backtracking
    int* currentPermutation = (int*)malloc(numsSize * sizeof(int));
    int* used = (int*)calloc(numsSize, sizeof(int)); // Track used numbers

    // Start backtracking to generate permutations
    *returnSize = 0;
    backtrack(currentPermutation, used, 0);

    // Clean up temporary arrays
    free(currentPermutation);
    free(used);

    return result;      
}
