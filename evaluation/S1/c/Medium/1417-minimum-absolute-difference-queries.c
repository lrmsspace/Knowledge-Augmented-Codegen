// Source: https://leetcode.com/problems/minimum-absolute-difference-queries/   |   Difficulty: Medium
//
// Problem Description:
// The minimum absolute difference of an array a is defined as the minimum value of |a[i] - a[j]|, where 0 <= i < j < a.length and a[i] != a[j]. If all elements of a are the same, the minimum absolute difference is -1.
//
//
// 	For example, the minimum absolute difference of the array [5,2,3,7,2] is |2 - 3| = 1. Note that it is not 0 because a[i] and a[j] must be different.
//
//
// You are given an integer array nums and the array queries where queries[i] = [li, ri]. For each query i, compute the minimum absolute difference of the subarray nums[li...ri] containing the elements of nums between the 0-based indices li and ri (inclusive).
//
// Return an array ans where ans[i] is the answer to the ith query.
//
// A subarray is a contiguous sequence of elements in an array.
//
// The value of |x| is defined as:
//
//
// 	x if x >= 0.
// 	-x if x < 0.
//
// Example:
// Input: nums = [1,3,4,8], queries = [[0,1],[1,2],[2,3],[0,3]]
// Output: [2,1,4,1]
// Explanation: The queries are processed as follows:
// - queries[0] = [0,1]: The subarray is [1,3] and the minimum absolute difference is |1-3| = 2.
// - queries[1] = [1,2]: The subarray is [3,4] and the minimum absolute difference is |3-4| = 1.
// - queries[2] = [2,3]: The subarray is [4,8] and the minimum absolute difference is |4-8| = 4.
// - queries[3] = [0,3]: The subarray is [1,3,4,8] and the minimum absolute difference is |3-4| = 1.
//
// Constraints:
// 2 <= nums.length <= 105
// 	1 <= nums[i] <= 100
// 	1 <= queries.length <= 2 * 104
// 	0 <= li < ri < nums.length
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (array, prefix-sum, max-window)
//   • When to use: When needing to find the maximum or minimum sum of any contiguous subarray within a given array efficiently. It is particularly useful for problems requiring an O(N) solution.
//   • Idea: This algorithm finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array, maintaining a running prefix sum, and tracking the minimum (or maximum) prefix sum encountered so far. It achieves an optimal O(N) time complexity with O(1) auxiliary space.
//   • Invariants: max_global_sum stores the maximum subarray sum found among all subarrays ending at or before the current element.; min_prefix_sum_value correctly tracks the minimum prefix sum encountered up to the previous element's prefix sum.
//   • Tips: Use a running sum variable instead of explicitly storing the entire prefix sum array.; Keep track of the minimum prefix sum encountered up to the current point.
//   • Pitfalls: Incorrectly initializing the minimum prefix sum (e.g., to INT_MAX instead of 0 or s[0]).; Off-by-one errors when calculating subarray sums using prefix sums (s[r] - s[l-1]).
// - Solve RMQ (Range Minimum Query) by finding LCA (Lowest Common Ancestor) (array, tree, stack, simulation, monotonic-stack)
//   • When to use: This technique is used to answer Range Minimum Queries efficiently on a static array by transforming them into Lowest Common Ancestor queries on a Cartesian Tree.
//   • Idea: This approach solves Range Minimum Query problems by constructing a Cartesian Tree from the input array, where the root of any subtree is its minimum element. RMQ for a given range then reduces to finding the Lowest Common Ancestor of the range's endpoints in this tree, allowing O(N) construction and O(1) query time after O(N) preprocessing.
//   • Invariants: For any node `u` in the Cartesian Tree, `value(u)` is the minimum among all values in the subtree rooted at `u`.; For any node `u`, all nodes in its left subtree have indices smaller than `index(u)`, and all nodes in its right subtree have indices larger than `index(u)`.
//   • Tips: A Cartesian Tree is a binary tree where each node's value is less than its children's values, and an in-order traversal yields the original array.; Utilize a monotonic stack to construct the Cartesian Tree in linear O(N) time.
//   • Pitfalls: Correctly implementing the monotonic stack for Cartesian Tree construction can be challenging.; Edge cases, such as an empty stack or handling the last elements during tree building, must be managed carefully.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
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
int* minDifference(int* nums, int numsSize, int** queries, int queriesSize, int* queriesColSize, int* returnSize) {
    // Since nums[i] is in the range [1, 100], we can use a frequency array to count occurrences
    // of each number in the current subarray defined by each query.
    int* result = (int*)malloc(queriesSize * sizeof(int));
    *returnSize = queriesSize;

    for (int q = 0; q < queriesSize; q++) {
        int left = queries[q][0];
        int right = queries[q][1];

        // Frequency array for numbers 1 to 100
        int freq[101] = {0};
        for (int i = left; i <= right; i++) {
            freq[nums[i]]++;
        }

        // Find the minimum absolute difference
        int minDiff = 101; // Initialize to a value larger than any possible difference
        int prevNum = -1;

        for (int num = 1; num <= 100; num++) {
            if (freq[num] > 0) {
                if (prevNum != -1) {
                    int diff = num - prevNum;
                    if (diff < minDiff) {
                        minDiff = diff;
                    }
                }
                prevNum = num;
            }
        }

        // If minDiff was not updated, it means all elements are the same
        result[q] = (minDiff == 101) ? -1 : minDiff;
    }

    return result;      
}
