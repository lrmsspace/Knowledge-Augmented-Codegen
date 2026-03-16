// Source: https://leetcode.com/problems/element-appearing-more-than-25-in-sorted-array/   |   Difficulty: Easy
//
// Problem Description:
// Given an integer array sorted in non-decreasing order, there is exactly one integer in the array that occurs more than 25% of the time, return that integer.
//
// Example:
// Input: arr = [1,2,2,6,6,6,6,7,10]
// Output: 6
//
// Constraints:
// 1 <= arr.length <= 104
// 	0 <= arr[i] <= 105
//
// Helpful references (internal KB):
// -  
// Kth order statistic in O(N) (array, enumeration)
//   • When to use: Use when you need to find the Kth smallest or largest element in an unsorted array efficiently, without sorting the entire dataset. It's ideal for problems requiring a specific order statistic in linear average time.
//   • Idea: This algorithm finds the Kth smallest (or largest) element in an unsorted array in expected linear time, O(N), by repeatedly partitioning the array around a pivot. It is a selection algorithm, conceptually similar to quicksort but only recursing on one side.
//   • Invariants: All elements to the left of the chosen pivot are less than or equal to the pivot.; All elements to the right of the chosen pivot are greater than or equal to the pivot.
//   • Tips: Choose a good pivot (e.g., random element) to minimize the chance of worst-case performance.; The algorithm can be implemented iteratively to avoid potential recursion depth limits for very large inputs.
//   • Pitfalls: Poor pivot selection can lead to a worst-case time complexity of O(N^2).; Off-by-one errors are common when translating K (1-based) to array indices (0-based).
// - Longest increasing subsequence (array, dp-1d)
//   • When to use: Use when finding the maximum length of a subsequence where elements are strictly increasing. It's suitable for problems requiring ordered selection from a sequence.
//   • Idea: This algorithm finds the longest subsequence of a given sequence such that all elements of the subsequence are sorted in increasing order. The standard DP approach has a time complexity of O(N^2).
//   • Invariants: At the start of iteration `i`, `dp[j]` for `j < i` stores the length of the LIS ending at `arr[j]`.; After processing `arr[i]`, `dp[i]` holds the length of the LIS ending with `arr[i]`.
//   • Tips: Initialize DP array with 1s, as each element is an LIS of length 1.; Iterate through all previous elements to find potential predecessors.
//   • Pitfalls: Forgetting to initialize the DP array correctly.; Incorrectly handling strict versus non-strict increasing conditions.
// - Ternary Search (interval, number, binary-search)
//   • When to use: Use when finding the extremum (maximum or minimum) of a unimodal function over a continuous interval, where the function strictly increases then decreases, or vice versa.
//   • Idea: Ternary search is an optimization algorithm that efficiently finds the extremum (maximum or minimum) of a unimodal function over a continuous interval. It operates in logarithmic time, O(log N), by repeatedly narrowing the search space.
//   • Invariants: The global extremum of the unimodal function is always contained within the current interval [l, r].; The function f(x) remains unimodal on the interval [l, r] throughout the search process.
//   • Tips: For floating-point functions, use a fixed number of iterations (e.g., 100-300) instead of an epsilon threshold for robustness.; The two comparison points m1 and m2 should divide the interval into three roughly equal parts for optimal convergence.
//   • Pitfalls: Applying ternary search to a non-unimodal function will not guarantee finding the global extremum.; Floating-point precision errors can lead to incorrect comparisons or infinite loops if epsilon is too small.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} arr
 * @return {number}
 */
var findSpecialInteger = function(arr) {
    const n = arr.length;
    const threshold = Math.floor(n / 4);
    
    for (let i = 0; i < n; i++) {
        if (i + threshold < n && arr[i] === arr[i + threshold]) {
            return arr[i];
        }
    }
    
    return -1; // This line should never be reached based on the problem constraints.
};
