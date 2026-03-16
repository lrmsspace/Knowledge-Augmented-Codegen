# Source: https://leetcode.com/problems/minimum-number-of-moves-to-make-palindrome/   |   Difficulty: Hard
#
# Problem Description:
# You are given a string s consisting only of lowercase English letters.
#
# In one move, you can select any two adjacent characters of s and swap them.
#
# Return the minimum number of moves needed to make s a palindrome.
#
# Note that the input will be generated such that s can always be converted to a palindrome.
#
# Example:
# Input: s = "aabb"
# Output: 2
# Explanation:
# We can obtain two palindromes from s, "abba" and "baab". 
# - We can obtain "abba" from s in 2 moves: "aabb" -> "abab" -> "abba".
# - We can obtain "baab" from s in 2 moves: "aabb" -> "abab" -> "baab".
# Thus, the minimum number of moves needed to make s a palindrome is 2.
#
# Constraints:
# 1 <= s.length <= 2000
# 	s consists only of lowercase English letters.
# 	s can be converted to a palindrome using a finite number of moves.
#
# Helpful references (internal KB):
# - Manacher's Algorithm - Finding all sub-p (string, array, two-pointers, simulation)
#   • When to use: When you need to find all palindromic substrings or the longest palindromic substring in a given string efficiently. It is particularly useful for achieving linear time complexity by leveraging symmetry.
#   • Idea: Manacher's algorithm finds all palindromic substrings in a string by expanding around centers and utilizing symmetry to avoid redundant comparisons. It achieves a linear time complexity of O(N) by maintaining the rightmost boundary of the longest palindrome found so far.
#   • Invariants: For any index k < i, d[k] correctly stores the radius of the longest palindrome centered at k.; The pair (l, r) always represents the exclusive boundaries of the palindrome that extends furthest to the right among all processed centers.
#   • Tips: Pre-process the string with delimiters (e.g., '#') to uniformly handle both odd and even length palindromes.; Leverage symmetry: for a center 'i' within the current rightmost palindrome, its mirror 'j' provides a lower bound for the palindrome length at 'i'.
#   • Pitfalls: Incorrectly handling boundary conditions when the mirror palindrome extends beyond the current rightmost palindrome.; Forgetting to update the 'l' and 'r' boundaries after finding a new palindrome that extends further to the right.
# - Manacher's Algorithm - Finding all sub-p (string, array, simulation, enumeration)
#   • When to use: When you need to find all palindromic substrings or the longest palindromic substring within a given string efficiently. It is particularly useful for achieving linear time complexity for this task.
#   • Idea: Manacher's algorithm finds all maximal palindromic substrings centered at each position in a string by leveraging symmetry and previously computed results. It achieves an optimal O(N) time complexity.
#   • Invariants: d_odd[i] stores the radius of the longest odd-length palindrome centered at i.; The (l, r) interval always defines the rightmost palindrome found so far.
#   • Tips: Preprocess the string with delimiters to unify odd and even length palindromes.; Maintain the current rightmost boundary `r` of the largest palindrome found.
#   • Pitfalls: Forgetting to update the `(l, r)` boundaries after processing each center.; Incorrectly calculating mirror positions or handling boundary cases for `i > r`.
# - palindrome-partitioning (string, two-pointers, simulation)
#   • When to use: When a string needs to be decomposed into all possible sets of palindromic substrings. It's suitable for problems requiring exhaustive enumeration of such partitions.
#   • Idea: This algorithm finds all possible ways to partition a given string such that every substring in the partition is a palindrome. It typically uses a recursive exploration approach combined with a two-pointer check for palindrome validation, resulting in an exponential time complexity.
#   • Invariants: At any point, the `step` list contains a valid palindromic partition of the prefix processed so far.; The `s` parameter in the recursive function always represents the unpartitioned suffix of the original string.
#   • Tips: Implement the `isPalindrome` check efficiently using two pointers for O(length) time.; Use a recursive helper function to explore all possible partition points.
#   • Pitfalls: Incorrectly handling substring boundaries, leading to off-by-one errors or incorrect partitions.; Forgetting to backtrack (remove the last added substring) after a recursive call returns.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def minMovesToMakePalindrome(self, s):
        """
        :type s: str
        :rtype: int
        """
        from collections import Counter

        char_count = Counter(s)
        odd_count = sum(1 for count in char_count.values() if count % 2 != 0)

        # If more than one character has an odd count, it's impossible to form a palindrome
        if odd_count > 1:
            return -1

        s_list = list(s)
        moves = 0
        left, right = 0, len(s) - 1

        while left < right:
            if s_list[left] == s_list[right]:
                left += 1
                right -= 1
            else:
                # Find the matching character for s_list[left] from the right side
                match_index = right
                while match_index > left and s_list[match_index] != s_list[left]:
                    match_index -= 1

                if match_index == left:  # No matching character found, swap with the next character
                    s_list[left], s_list[left + 1] = s_list[left + 1], s_list[left]
                    moves += 1
                else:  # Matching character found, move it to the right position
                    for i in range(match_index, right):
                        s_list[i], s_list[i + 1] = s_list[i + 1], s_list[i]
                        moves += 1
                    left += 1
                    right -= 1

        return moves