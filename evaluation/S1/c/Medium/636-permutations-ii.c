// Source: https://leetcode.com/problems/permutations-ii/   |   Difficulty: Medium
//
// Problem Description:
// Given a collection of numbers, nums, that might contain duplicates, return all possible unique permutations in any order.
//
// Example:
// Input: nums = [1,1,2]
// Output:
// [[1,1,2],
//  [1,2,1],
//  [2,1,1]]
//
// Constraints:
// 1 <= nums.length <= 8
// 	-10 <= nums[i] <= 10
//
// Helpful references (internal KB):
// - palindrome-partitioning (string, array, backtracking, recursion)
//   • When to use: Use this when you need to find all possible ways to break down a string into parts, where each part must satisfy a specific property. It is suitable for generating all combinations or permutations with constraints.
//   • Idea: This algorithm recursively explores all possible ways to partition a string into substrings, ensuring each substring is a palindrome. It employs a backtracking approach to build valid partitions incrementally, typically resulting in exponential time complexity.
//   • Invariants: At the start of each recursive call, the 'step' list contains a valid palindrome partition for the string segment processed so far.; The current processing index (or remaining string) always points to the unpartitioned suffix of the original input string.
//   • Tips: Utilize a helper function to manage additional state, such as the current partition path and the overall result list.; Pass the remaining string or a start index to recursive calls to define the subproblem for subsequent partitioning.
//   • Pitfalls: Forgetting to create a new copy of the current partition path before adding it to the final result list, leading to incorrect results.; Incorrectly defining the base case for recursion, which can cause infinite loops or missed valid partitions.
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
#include <stdlib.h>
#include <string.h>

static int cmpInt(const void *a, const void *b) {
	return (*(int*)a) - (*(int*)b);
}

static void backtrack(int *nums, int numsSize, int *used, int *path, int depth,
					  int ***results, int *cap, int *returnSize, int **colSizes) {
	if (depth == numsSize) {
		if (*returnSize >= *cap) {
			int newCap = (*cap == 0) ? 16 : (*cap) * 2;
			int **tmp = (int**)realloc(*results, newCap * sizeof(int*));
			if (!tmp) return;
			*results = tmp;
			int *tmpCols = (int*)realloc(*colSizes, newCap * sizeof(int));
			if (!tmpCols) return;
			*colSizes = tmpCols;
			*cap = newCap;
		}
		int *row = (int*)malloc(numsSize * sizeof(int));
		if (!row) return;
		memcpy(row, path, numsSize * sizeof(int));
		(*results)[*returnSize] = row;
		(*colSizes)[*returnSize] = numsSize;
		(*returnSize)++;
		return;
	}

	for (int i = 0; i < numsSize; ++i) {
		if (used[i]) continue;
		if (i > 0 && nums[i] == nums[i-1] && !used[i-1]) continue;
		used[i] = 1;
		path[depth] = nums[i];
		backtrack(nums, numsSize, used, path, depth + 1, results, cap, returnSize, colSizes);
		used[i] = 0;
	}
}

int** permuteUnique(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
	if (!returnSize || !returnColumnSizes) return NULL;
	*returnSize = 0;
	*returnColumnSizes = NULL;
	if (numsSize <= 0) return NULL;

	qsort(nums, numsSize, sizeof(int), cmpInt);

	int **results = NULL;
	int cap = 0;
	int *colSizes = NULL;
	int *used = (int*)calloc(numsSize, sizeof(int));
	int *path = (int*)malloc(numsSize * sizeof(int));

	if (!used || !path) {
		free(used);
		free(path);
		return NULL;
	}

	backtrack(nums, numsSize, used, path, 0, &results, &cap, returnSize, &colSizes);

	free(used);
	free(path);

	*returnColumnSizes = colSizes;
	return results;
}
