// Source: https://leetcode.com/problems/zero-array-transformation-ii/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums of length n and a 2D array queries where queries[i] = [li, ri, vali].
//
// Each queries[i] represents the following action on nums:
//
//
// 	Decrement the value at each index in the range [li, ri] in nums by at most vali.
// 	The amount by which each value is decremented can be chosen independently for each index.
//
//
// A Zero Array is an array with all its elements equal to 0.
//
// Return the minimum possible non-negative value of k, such that after processing the first k queries in sequence, nums becomes a Zero Array. If no such k exists, return -1.
//
// Example:
// Input: nums = [2,0,2], queries = [[0,2,1],[0,2,1],[1,1,3]]
//
// Output: 2
//
// Explanation:
//
//
// 	For i = 0 (l = 0, r = 2, val = 1):
//
// 	
// 		Decrement values at indices [0, 1, 2] by [1, 0, 1] respectively.
// 		The array will become [1, 0, 1].
// 	
// 	
// 	For i = 1 (l = 0, r = 2, val = 1):
// 	
// 		Decrement values at indices [0, 1, 2] by [1, 0, 1] respectively.
// 		The array will become [0, 0, 0], which is a Zero Array. Therefore, the minimum value of k is 2.
//
// Constraints:
// 1 <= nums.length <= 105
// 	0 <= nums[i] <= 5 * 105
// 	1 <= queries.length <= 105
// 	queries[i].length == 3
// 	0 <= li <= ri < nums.length
// 	1 <= vali <= 5
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (array, binary-search-answer)
//   • When to use: Use when the problem asks for the minimum or maximum value that satisfies a monotonic condition.
//   • Idea: This technique finds a target value within a range by repeatedly dividing the search interval in half, based on a monotonic condition. It typically achieves O(log N) time complexity for a search space of size N.
//   • Invariants: The optimal answer always lies within the current search range [low, high].; All values less than 'low' (for min search) or greater than 'high' (for max search) are known to be non-optimal.
//   • Tips: Clearly define the search space [low, high] for the answer.; Implement a `check` function that determines if a given `mid` value is a feasible solution.
//   • Pitfalls: Incorrectly defining the search range [low, high] for the answer.; Errors in the `check` function leading to incorrect monotonicity or logic.
// - Sqrt Decomposition (array, enumeration, difference-array)
//   • When to use: Efficiently calculate sums or properties over various ranges in a static array. Useful for many range queries or when combining range updates with point queries.
//   • Idea: Prefix sums allow O(1) range sum queries after O(N) preprocessing. Difference arrays enable O(1) range updates and O(N) point queries after O(N) reconstruction.
//   • Invariants: The prefix sum array P[i] stores the sum of elements from A[0] to A[i-1].; The difference array D[i] stores A[i] - A[i-1] (for i > 0).
//   • Tips: Precompute prefix sums to answer range sum queries in constant time.; Use a difference array to apply range updates efficiently.
//   • Pitfalls: Off-by-one errors in range boundaries for prefix sums.; Forgetting to initialize the difference array correctly (e.g., diff[0] = arr[0] for 0-indexed).
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int minZeroArray(int* nums, int numsSize, int** queries, int queriesSize, int* queriesColSize) {
    // Sqrt Decomposition with Difference Array implementation
    int blockSize = 320; // Approximate sqrt(10^5)
    int numBlocks = (numsSize + blockSize - 1) / blockSize;

    int* diff = (int*)calloc(numsSize + 1, sizeof(int));
    int* blockAdd = (int*)calloc(numBlocks, sizeof(int));

    for (int q = 0; q < queriesSize; q++) {
        int l = queries[q][0];
        int r = queries[q][1];
        int val = queries[q][2];

        int startBlock = l / blockSize;
        int endBlock = r / blockSize;

        if (startBlock == endBlock) {
            for (int i = l; i <= r; i++) {
                diff[i] -= val;
            }
        } else {
            for (int i = l; i < (startBlock + 1) * blockSize; i++) {
                diff[i] -= val;
            }
            for (int b = startBlock + 1; b < endBlock; b++) {
                blockAdd[b] -= val;
            }
            for (int i = endBlock * blockSize; i <= r; i++) {
                diff[i] -= val;
            }
        }

        // Check if nums can be reduced to zero
        int canZero = 1;
        int currentAdd = 0;
        for (int i = 0; i < numsSize; i++) {
            if (i % blockSize == 0) {
                currentAdd += blockAdd[i / blockSize];
            }
            currentAdd += diff[i];
            if (nums[i] + currentAdd > 0) {
                canZero = 0;
                break;
            }
        }

        if (canZero) {
            free(diff);
            free(blockAdd);
            return q + 1;
        }
    }

    free(diff);
    free(blockAdd);
    return -1;
}
