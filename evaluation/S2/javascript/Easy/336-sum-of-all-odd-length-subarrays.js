// Source: https://leetcode.com/problems/sum-of-all-odd-length-subarrays/   |   Difficulty: Easy
//
// Problem Description:
// Given an array of positive integers arr, return the sum of all possible odd-length subarrays of arr.
//
// A subarray is a contiguous subsequence of the array.
//
// Example:
// Input: arr = [1,4,2,5,3]
// Output: 58
// Explanation: The odd-length subarrays of arr and their sums are:
// [1] = 1
// [4] = 4
// [2] = 2
// [5] = 5
// [3] = 3
// [1,4,2] = 7
// [4,2,5] = 11
// [2,5,3] = 10
// [1,4,2,5,3] = 15
// If we add all these together we get 1 + 4 + 2 + 5 + 3 + 7 + 11 + 10 + 15 = 58
//
// Constraints:
// 1 <= arr.length <= 100
// 	1 <= arr[i] <= 1000
//
//
//  
// Follow up:
//
// Could you solve this problem in O(n) time complexity?
//
// Helpful references (internal KB):
// - Manacher's Algorithm - Finding all sub-p (string, array, simulation, enumeration)
//   • When to use: When you need to find all palindromic substrings or the longest palindromic substring within a given string efficiently. It is particularly useful for achieving linear time complexity for this task.
//   • Idea: Manacher's algorithm finds all maximal palindromic substrings centered at each position in a string by leveraging symmetry and previously computed results. It achieves an optimal O(N) time complexity.
//   • Invariants: d_odd[i] stores the radius of the longest odd-length palindrome centered at i.; The (l, r) interval always defines the rightmost palindrome found so far.
//   • Tips: Preprocess the string with delimiters to unify odd and even length palindromes.; Maintain the current rightmost boundary `r` of the largest palindrome found.
//   • Pitfalls: Forgetting to update the `(l, r)` boundaries after processing each center.; Incorrectly calculating mirror positions or handling boundary cases for `i > r`.
// - Operations on polynomials and series (array, recursion)
//   • When to use: Apply when multiplying polynomials or combining two sequences where the resulting element's index is the sum of indices from the original sequences. This is typically for enumerative counting problems.
//   • Idea: Convolution computes the coefficients of the product of two polynomials or series by summing products of coefficients whose indices add up to the target index. A direct computation has a time complexity of O(N*M).
//   • Invariants: For any k, c_k correctly represents the coefficient of x^k in the product polynomial.; The sum i + (k-i) always equals k for each term contributing to c_k.
//   • Tips: Understand the index relationship: c_k = sum(a_i * b_{k-i}) for all valid i.; Handle array bounds carefully for both input sequences and the result.
//   • Pitfalls: Off-by-one errors in loop bounds for indices i and k-i.; Incorrectly determining the size of the result array (should be n+m+1 elements for degrees n and m).
// - Sqrt Decomposition (array, ds, sliding-window, two-pointers)
//   • When to use: Use when performing frequent range queries and point updates on an array, especially when a segment tree is too complex or memory-intensive, or when query types are diverse. It offers a balanced time complexity for both operations.
//   • Idea: Sqrt decomposition divides an array into blocks of size approximately sqrt(N) to optimize range queries and point updates. It achieves O(sqrt(N)) time complexity for both operations.
//   • Invariants: Each element `arr[i]` belongs to exactly one block `block[i / block_size]`.; The summary for each block `block_summary[j]` accurately reflects the state of elements within block `j`.
//   • Tips: Choose block size carefully, typically sqrt(N) for balanced performance.; Precompute block summaries (e.g., sum, min, max) for efficient queries.
//   • Pitfalls: Off-by-one errors when calculating block indices or boundaries.; Forgetting to update the block's summary after a point update.
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
var sumOddLengthSubarrays = function(arr) {
    let totalSum = 0;
    const n = arr.length;
    
    // For each odd length subarray
    for (let len = 1; len <= n; len += 2) {
        // For each starting index of subarray of current length
        for (let i = 0; i <= n - len; i++) {
            // Sum all elements in the subarray
            for (let j = i; j < i + len; j++) {
                totalSum += arr[j];
            }
        }
    }
    
    return totalSum;
};
