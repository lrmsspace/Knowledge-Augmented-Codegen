// Source: https://leetcode.com/problems/maximum-product-of-the-length-of-two-palindromic-subsequences/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s, find two disjoint palindromic subsequences of s such that the product of their lengths is maximized. The two subsequences are disjoint if they do not both pick a character at the same index.
//
// Return the maximum possible product of the lengths of the two palindromic subsequences.
//
// A subsequence is a string that can be derived from another string by deleting some or no characters without changing the order of the remaining characters. A string is palindromic if it reads the same forward and backward.
//
// Example:
// Input: s = "leetcodecom"
// Output: 9
// Explanation: An optimal solution is to choose "ete" for the 1st subsequence and "cdc" for the 2nd subsequence.
// The product of their lengths is: 3 * 3 = 9.
//
// Constraints:
// 2 <= s.length <= 12
// 	s consists of lowercase English letters only.
//
// Helpful references (internal KB):
// - Manacher's Algorithm - Finding all sub-p (string, array, simulation, enumeration)
//   • When to use: When you need to find all palindromic substrings or the longest palindromic substring within a given string efficiently. It is particularly useful for achieving linear time complexity for this task.
//   • Idea: Manacher's algorithm finds all maximal palindromic substrings centered at each position in a string by leveraging symmetry and previously computed results. It achieves an optimal O(N) time complexity.
//   • Invariants: d_odd[i] stores the radius of the longest odd-length palindrome centered at i.; The (l, r) interval always defines the rightmost palindrome found so far.
//   • Tips: Preprocess the string with delimiters to unify odd and even length palindromes.; Maintain the current rightmost boundary `r` of the largest palindrome found.
//   • Pitfalls: Forgetting to update the `(l, r)` boundaries after processing each center.; Incorrectly calculating mirror positions or handling boundary cases for `i > r`.
// - Submask Enumeration
//  (number, bitset, enumeration, bitmask-dp)
//   • When to use: When a problem requires iterating through all possible submasks for each given mask. This is common in bitmask dynamic programming problems where relationships between a set and its subsets are crucial.
//   • Idea: This algorithm efficiently iterates through all submasks for every mask from 0 to 2^N - 1. It has a total time complexity of O(3^N) for all masks and their submasks.
//   • Invariants: For a given `mask`, `submask` always represents a subset of `mask`.; Each `submask` is visited exactly once for its corresponding `mask`.
//   • Tips: The `submask = (submask - 1) & mask` trick is crucial for efficient iteration.; Ensure the outer loop iterates through all masks from 0 to 2^N - 1.
//   • Pitfalls: Forgetting the `& mask` part in the inner loop can lead to incorrect submasks or infinite loops.; Misunderstanding the O(3^N) total complexity, leading to Time Limit Exceeded for large N.
// - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
//   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
//   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
//   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
//   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
//   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {string} s
 * @return {number}
 */
var maxProduct = function(s) {
    const n = s.length;
    const totalMasks = 1 << n;
    const palLengths = new Array(totalMasks).fill(0);

    // Function to check if a subsequence represented by mask is a palindrome
    const isPalindrome = (mask) => {
        let subseq = '';
        for (let i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                subseq += s[i];
            }
        }
        let left = 0, right = subseq.length - 1;
        while (left < right) {
            if (subseq[left] !== subseq[right]) return false;
            left++;
            right--;
        }
        return true;
    };

    // Precompute lengths of palindromic subsequences for all masks
    for (let mask = 1; mask < totalMasks; mask++) {
        if (isPalindrome(mask)) {
            let length = 0;
            for (let i = 0; i < n; i++) {
                if (mask & (1 << i)) length++;
            }
            palLengths[mask] = length;
        }
    }

    let maxProduct = 0;

    // Iterate through all pairs of disjoint masks
    for (let mask1 = 1; mask1 < totalMasks; mask1++) {
        if (palLengths[mask1] === 0) continue;
        for (let mask2 = 1; mask2 < totalMasks; mask2++) {
            if ((mask1 & mask2) === 0 && palLengths[mask2] > 0) {
                const product = palLengths[mask1] * palLengths[mask2];
                maxProduct = Math.max(maxProduct, product);
            }
        }
    }

    return maxProduct;
};
