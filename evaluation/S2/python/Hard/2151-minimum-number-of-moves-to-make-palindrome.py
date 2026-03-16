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
# - Manacher's Algorithm - Finding all sub-p (string, array, simulation, enumeration)
#   • When to use: When you need to find all palindromic substrings or the longest palindromic substring within a given string efficiently. It is particularly useful for achieving linear time complexity for this task.
#   • Idea: Manacher's algorithm finds all maximal palindromic substrings centered at each position in a string by leveraging symmetry and previously computed results. It achieves an optimal O(N) time complexity.
#   • Invariants: d_odd[i] stores the radius of the longest odd-length palindrome centered at i.; The (l, r) interval always defines the rightmost palindrome found so far.
#   • Tips: Preprocess the string with delimiters to unify odd and even length palindromes.; Maintain the current rightmost boundary `r` of the largest palindrome found.
#   • Pitfalls: Forgetting to update the `(l, r)` boundaries after processing each center.; Incorrectly calculating mirror positions or handling boundary cases for `i > r`.
# - The Inclusion-Exclusion Principle (string, counting)
#   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
#   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
#   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
#   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
#   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
# - Lyndon factorization (string, greedy, two-pointers)
#   • When to use: Use this algorithm to decompose a string into a unique sequence of Lyndon words, which are lexicographically smallest among their cyclic shifts. It is also applicable for finding the smallest cyclic shift of a string.
#   • Idea: The Duval algorithm greedily factorizes a string into a sequence of Lyndon words by maintaining three pointers to manage processed, pre-simple, and untouched parts. It achieves this in O(N) time complexity.
#   • Invariants: The prefix s[0...i-1] always contains a valid Lyndon factorization.; The substring s[i...j-1] is always a pre-simple string.
#   • Tips: Thoroughly understand the definitions of 'simple string' and 'pre-simple string' to correctly apply the comparison logic.; The three pointers (i, j, k) are crucial; 'i' marks the start of the current pre-simple string, 'j' the start of the untouched part, and 'k' for comparison within the pre-simple string.
#   • Pitfalls: Incorrectly resetting the 'k' pointer when s[j] > s[k], which should point back to the beginning of the simple word within s2.; Misinterpreting the length of the simple string (j - k) when a factorization step occurs.
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

        # Count the frequency of each character
        freq = Counter(s)
        
        # Check if the string can be rearranged into a palindrome
        odd_count = sum(1 for count in freq.values() if count % 2 != 0)
        if odd_count > 1:
            return -1  # More than one character has an odd count, cannot form a palindrome
        
        # Convert the string to a list for easier manipulation
        s_list = list(s)
        left, right = 0, len(s_list) - 1
        moves = 0
        
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