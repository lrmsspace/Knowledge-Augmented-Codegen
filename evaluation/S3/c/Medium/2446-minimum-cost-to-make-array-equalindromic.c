// Source: https://leetcode.com/problems/minimum-cost-to-make-array-equalindromic/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array nums having length n.
//
// You are allowed to perform a special move any number of times (including zero) on nums. In one special move you perform the following steps in order:
//
//
// 	Choose an index i in the range [0, n - 1], and a positive integer x.
// 	Add |nums[i] - x| to the total cost.
// 	Change the value of nums[i] to x.
//
//
// A palindromic number is a positive integer that remains the same when its digits are reversed. For example, 121, 2552 and 65756 are palindromic numbers whereas 24, 46, 235 are not palindromic numbers.
//
// An array is considered equalindromic if all the elements in the array are equal to an integer y, where y is a palindromic number less than 109.
//
// Return an integer denoting the minimum possible total cost to make nums equalindromic by performing any number of special moves.
//
// Example:
// Input: nums = [1,2,3,4,5]
// Output: 6
// Explanation: We can make the array equalindromic by changing all elements to 3 which is a palindromic number. The cost of changing the array to [3,3,3,3,3] using 4 special moves is given by |1 - 3| + |2 - 3| + |4 - 3| + |5 - 3| = 6.
// It can be shown that changing all elements to any palindromic number other than 3 cannot be achieved at a lower cost.
//
// Constraints:
// 1 <= n <= 105
// 	1 <= nums[i] <= 109
//
// Helpful references (internal KB):
// - Manacher's Algorithm - Finding all sub-p (string, array, enumeration)
//   • When to use: Use when you need to find all palindromic substrings within a given string, or determine the longest palindromic substring, in optimal linear time.
//   • Idea: Manacher's Algorithm efficiently finds the length of the longest palindromic substring centered at each position in a given string, handling both odd and even lengths uniformly via preprocessing. It achieves this in optimal O(N) time complexity.
//   • Invariants: p[i] correctly stores the radius of the longest palindrome centered at i in the transformed string.; The right_boundary always marks the rightmost extent of the largest palindrome found so far.
//   • Tips: Preprocess the string with a unique delimiter to unify odd and even length palindromes.; Leverage the mirror property around the current center to initialize palindrome radii.
//   • Pitfalls: Off-by-one errors when converting `p` array values back to original string indices or lengths.; Incorrectly handling the boundaries of the preprocessed string.
// - Manacher's Algorithm - Finding all sub-p (string, array, simulation, enumeration)
//   • When to use: When you need to find all palindromic substrings or the longest palindromic substring within a given string efficiently. It is particularly useful for achieving linear time complexity for this task.
//   • Idea: Manacher's algorithm finds all maximal palindromic substrings centered at each position in a string by leveraging symmetry and previously computed results. It achieves an optimal O(N) time complexity.
//   • Invariants: d_odd[i] stores the radius of the longest odd-length palindrome centered at i.; The (l, r) interval always defines the rightmost palindrome found so far.
//   • Tips: Preprocess the string with delimiters to unify odd and even length palindromes.; Maintain the current rightmost boundary `r` of the largest palindrome found.
//   • Pitfalls: Forgetting to update the `(l, r)` boundaries after processing each center.; Incorrectly calculating mirror positions or handling boundary cases for `i > r`.
// - Manacher's Algorithm - Finding all sub-p (string, array, two-pointers, simulation)
//   • When to use: When you need to find all palindromic substrings or the longest palindromic substring in a given string efficiently. It is particularly useful for achieving linear time complexity by leveraging symmetry.
//   • Idea: Manacher's algorithm finds all palindromic substrings in a string by expanding around centers and utilizing symmetry to avoid redundant comparisons. It achieves a linear time complexity of O(N) by maintaining the rightmost boundary of the longest palindrome found so far.
//   • Invariants: For any index k < i, d[k] correctly stores the radius of the longest palindrome centered at k.; The pair (l, r) always represents the exclusive boundaries of the palindrome that extends furthest to the right among all processed centers.
//   • Tips: Pre-process the string with delimiters (e.g., '#') to uniformly handle both odd and even length palindromes.; Leverage symmetry: for a center 'i' within the current rightmost palindrome, its mirror 'j' provides a lower bound for the palindrome length at 'i'.
//   • Pitfalls: Incorrectly handling boundary conditions when the mirror palindrome extends beyond the current rightmost palindrome.; Forgetting to update the 'l' and 'r' boundaries after finding a new palindrome that extends further to the right.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

long long minimumCost(int* nums, int numsSize) {
    long long cost = 0;
    for (int i = 0; i < numsSize / 2; ++i) {
        int left = nums[i];
        int right = nums[numsSize - 1 - i];
        cost += left > right ? left - right : right - left;
    }
    return cost;        
}
