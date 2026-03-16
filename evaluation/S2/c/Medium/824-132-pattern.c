// Source: https://leetcode.com/problems/132-pattern/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of n integers nums, a 132 pattern is a subsequence of three integers nums[i], nums[j] and nums[k] such that i < j < k and nums[i] < nums[k] < nums[j].
//
// Return true if there is a 132 pattern in nums, otherwise, return false.
//
// Example:
// Input: nums = [1,2,3,4]
// Output: false
// Explanation: There is no 132 pattern in the sequence.
//
// Constraints:
// n == nums.length
// 	1 <= n <= 2 * 105
// 	-109 <= nums[i] <= 109
//
// Helpful references (internal KB):
// - Longest Increasing Subsequence (array, coordinate-compress, segment-tree, dp-1d)
//   • When to use: Use when finding the maximum length of a subsequence where elements must be strictly increasing. It is applicable for problems requiring optimal substructure on sequences with an increasing property.
//   • Idea: The Longest Increasing Subsequence (LIS) problem finds the longest subsequence of a given sequence such that all elements of the subsequence are in increasing order. It can be solved in O(N log N) time using dynamic programming with binary search or a segment tree with coordinate compression.
//   • Invariants: The `dp` array (or segment tree) stores information about the smallest ending element for increasing subsequences of various lengths.; The `dp` array, if used, remains sorted in strictly increasing order.
//   • Tips: The O(N log N) solution uses a `dp` array storing the smallest ending element for all increasing subsequences of a given length.; Binary search (`lower_bound`) efficiently finds the correct position to update in the `dp` array.
//   • Pitfalls: Confusing subsequence with subarray, which requires contiguous elements.; Incorrectly handling duplicates; LIS typically requires strictly increasing elements.
// - Minimum stack / Minimum queue (queue, deque, monotonic-queue)
//   • When to use: Use this technique when you need to perform standard queue or stack operations while also querying the minimum (or maximum) element in O(1) time. It is ideal for problems involving sliding windows or dynamic collections where min/max queries are frequent.
//   • Idea: This technique augments a queue or stack with an auxiliary data structure, typically a deque, to maintain elements in monotonic order. This allows for O(1) retrieval of the minimum (or maximum) element, with standard operations achieving amortized O(1) time complexity.
//   • Invariants: The auxiliary deque stores elements in non-decreasing order from front to back.; The element at the front of the auxiliary deque is the minimum of all elements currently in the main queue/stack.
//   • Tips: Utilize a deque for the auxiliary structure to efficiently add and remove from both ends.; For a minimum queue, maintain the auxiliary deque in non-decreasing order from front to back.
//   • Pitfalls: Incorrectly handling removals when the element to be removed from the main structure is not the current minimum.; Forgetting to remove elements from the auxiliary deque when they are no longer relevant (e.g., out of window bounds).
// - Ternary Search (interval, number, binary-search, greedy)
//   • When to use: Use when searching for the extremum (maximum or minimum) of a unimodal function over a continuous or discrete interval. It efficiently narrows down the search space by evaluating the function at two internal points.
//   • Idea: Ternary search is a divide and conquer algorithm that finds the extremum of a unimodal function within an interval by repeatedly reducing the search space by approximately one-third. It has a logarithmic time complexity, similar to binary search, but requires two function evaluations per step.
//   • Invariants: The extremum of the unimodal function lies within the current interval [l, r].; The function value at m1 is compared with the function value at m2.
//   • Tips: Handle discrete intervals by checking remaining points when interval size is small.; Consider Golden Section Search to reduce function evaluations per iteration.
//   • Pitfalls: Incorrectly applying to non-unimodal functions.; Infinite loops if stopping condition for discrete intervals is not handled.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

bool find132pattern(int* nums, int numsSize) {
    if (numsSize < 3) {
        return false;
    }

    int stack[numsSize];
    int top = -1;
    int second = INT_MIN;

    for (int i = numsSize - 1; i >= 0; i--) {
        if (nums[i] < second) {
            return true;
        }
        while (top >= 0 && nums[i] > stack[top]) {
            second = stack[top--];
        }
        stack[++top] = nums[i];
    }

    return false;       
}
