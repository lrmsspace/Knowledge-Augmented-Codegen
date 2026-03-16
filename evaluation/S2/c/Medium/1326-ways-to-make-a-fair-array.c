// Source: https://leetcode.com/problems/ways-to-make-a-fair-array/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums. You can choose exactly one index (0-indexed) and remove the element. Notice that the index of the elements may change after the removal.
//
// For example, if nums = [6,1,7,4,1]:
//
//
// 	Choosing to remove index 1 results in nums = [6,7,4,1].
// 	Choosing to remove index 2 results in nums = [6,1,4,1].
// 	Choosing to remove index 4 results in nums = [6,1,7,4].
//
//
// An array is fair if the sum of the odd-indexed values equals the sum of the even-indexed values.
//
// Return the number of indices that you could choose such that after the removal, nums is fair.
//
// Example:
// Input: nums = [2,1,6,4]
// Output: 1
// Explanation:
// Remove index 0: [1,6,4] -> Even sum: 1 + 4 = 5. Odd sum: 6. Not fair.
// Remove index 1: [2,6,4] -> Even sum: 2 + 4 = 6. Odd sum: 6. Fair.
// Remove index 2: [2,1,4] -> Even sum: 2 + 4 = 6. Odd sum: 1. Not fair.
// Remove index 3: [2,1,6] -> Even sum: 2 + 6 = 8. Odd sum: 1. Not fair.
// There is 1 index that you can remove to make nums fair.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 104
//
// Helpful references (internal KB):
// - Sqrt Decomposition (array, ds, sliding-window, two-pointers)
//   • When to use: Use when performing frequent range queries and point updates on an array, especially when a segment tree is too complex or memory-intensive, or when query types are diverse. It offers a balanced time complexity for both operations.
//   • Idea: Sqrt decomposition divides an array into blocks of size approximately sqrt(N) to optimize range queries and point updates. It achieves O(sqrt(N)) time complexity for both operations.
//   • Invariants: Each element `arr[i]` belongs to exactly one block `block[i / block_size]`.; The summary for each block `block_summary[j]` accurately reflects the state of elements within block `j`.
//   • Tips: Choose block size carefully, typically sqrt(N) for balanced performance.; Precompute block summaries (e.g., sum, min, max) for efficient queries.
//   • Pitfalls: Off-by-one errors when calculating block indices or boundaries.; Forgetting to update the block's summary after a point update.
// - 15 Puzzle Game: Existence Of The Solution (matrix, number, counting)
//   • When to use: Use this to quickly determine if a given 15-puzzle board configuration can be solved, avoiding exhaustive search. It's applicable when the goal is to check solvability rather than finding the solution path.
//   • Idea: This algorithm determines the solvability of a 15-puzzle configuration by analyzing the parity of inversions in the tile permutation and the blank tile's row. It involves counting inversions, which typically takes O(N^2) time for N tiles, or O(N log N) with a more advanced counting method.
//   • Invariants: The permutation used for inversion counting always excludes the blank tile.; Each pair of tiles (i, j) with i < j is considered exactly once for inversion counting.
//   • Tips: Remember to exclude the blank tile (0) when forming the permutation for inversion counting.; For a 4x4 grid, the blank tile's row (from bottom, 1-indexed) is crucial for the parity check.
//   • Pitfalls: Incorrectly including the blank tile (0) in the inversion count.; Miscalculating the blank tile's row index (e.g., 0-indexed from top vs. 1-indexed from bottom).
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

int waysToMakeFair(int* nums, int numsSize) {
    int evenSum = 0, oddSum = 0;
    for (int i = 0; i < numsSize; i++) {
        if (i % 2 == 0) {
            evenSum += nums[i];
        } else {
            oddSum += nums[i];
        }
    }

    int count = 0;
    int currentEvenSum = evenSum, currentOddSum = oddSum;

    for (int i = 0; i < numsSize; i++) {
        if (i % 2 == 0) {
            currentEvenSum -= nums[i];
        } else {
            currentOddSum -= nums[i];
        }

        if (currentEvenSum == currentOddSum) {
            count++;
        }

        if (i % 2 == 0) {
            currentOddSum += nums[i];
        } else {
            currentEvenSum += nums[i];
        }
    }

    return count;       
}
