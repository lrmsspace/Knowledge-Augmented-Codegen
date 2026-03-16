# Source: https://leetcode.com/problems/minimum-number-of-flips-to-make-the-binary-string-alternating/   |   Difficulty: Medium
#
# Problem Description:
# You are given a binary string s. You are allowed to perform two types of operations on the string in any sequence:
#
#
# 	Type-1: Remove the character at the start of the string s and append it to the end of the string.
# 	Type-2: Pick any character in s and flip its value, i.e., if its value is '0' it becomes '1' and vice-versa.
#
#
# Return the minimum number of type-2 operations you need to perform such that s becomes alternating.
#
# The string is called alternating if no two adjacent characters are equal.
#
#
# 	For example, the strings "010" and "1010" are alternating, while the string "0100" is not.
#
# Example:
# Input: s = "111000"
# Output: 2
# Explanation: Use the first operation two times to make s = "100011".
# Then, use the second operation on the third and sixth elements to make s = "101010".
#
# Constraints:
# 1 <= s.length <= 105
# 	s[i] is either '0' or '1'.
#
# Helpful references (internal KB):
# - Manacher's Algorithm - Finding all sub-p (string, array, simulation, enumeration)
#   • When to use: When you need to find all palindromic substrings or the longest palindromic substring within a given string efficiently. It is particularly useful for achieving linear time complexity for this task.
#   • Idea: Manacher's algorithm finds all maximal palindromic substrings centered at each position in a string by leveraging symmetry and previously computed results. It achieves an optimal O(N) time complexity.
#   • Invariants: d_odd[i] stores the radius of the longest odd-length palindrome centered at i.; The (l, r) interval always defines the rightmost palindrome found so far.
#   • Tips: Preprocess the string with delimiters to unify odd and even length palindromes.; Maintain the current rightmost boundary `r` of the largest palindrome found.
#   • Pitfalls: Forgetting to update the `(l, r)` boundaries after processing each center.; Incorrectly calculating mirror positions or handling boundary cases for `i > r`.
# - Suffix Array (array, string, simulation, two-pointers)
#   • When to use: Use when needing to efficiently compare substrings, find all occurrences of a pattern, or determine lexicographical order among suffixes within a string.
#   • Idea: A Suffix Array stores sorted suffixes of a string, enabling fast substring comparisons and pattern searching. Construction typically takes O(N log N) time, with comparisons often O(1) after preprocessing.
#   • Invariants: The suffix array `p` contains all suffixes of the string `s` sorted lexicographically.; During construction, equivalence classes `c` correctly group suffixes that are identical up to a certain length `2^k`.
#   • Tips: Precompute log values for efficient block length calculation.; Utilize equivalence classes for O(1) comparison of power-of-two length substrings.
#   • Pitfalls: Complexity of suffix array construction can be tricky (e.g., O(N log N) vs O(N)).; Off-by-one errors when calculating block indices or lengths.
# - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
#   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
#   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
#   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
#   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
#   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def minFlips(self, s):
        """
        :type s: str
        :rtype: int
        """
        n = len(s)
        s = s + s  # Concatenate the string to itself to simulate rotation
        count1 = count2 = 0  # Counters for the two alternating patterns

        for i in range(2 * n):
            if s[i] != str(i % 2):  # Pattern "0101..."
                count1 += 1
            else:  # Pattern "1010..."
                count2 += 1

            if i >= n:  # When we have processed more than n characters, we need to remove the effect of the character that is sliding out of the window
                if s[i - n] != str((i - n) % 2):
                    count1 -= 1
                else:
                    count2 -= 1

            if i >= n - 1:  # We can start checking for minimum flips after processing at least n characters
                if i < n + (n - 1):  # Only check for the first n rotations
                    min_flips = min(count1, count2)
                    if i == n - 1:
                        result = min_flips
                    else:
                        result = min(result, min_flips)

        return result