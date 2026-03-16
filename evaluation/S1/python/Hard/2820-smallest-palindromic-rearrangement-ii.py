# Source: https://leetcode.com/problems/smallest-palindromic-rearrangement-ii/   |   Difficulty: Hard
#
# Problem Description:
# You are given a palindromic string s and an integer k.
#
# Return the k-th lexicographically smallest palindromic permutation of s. If there are fewer than k distinct palindromic permutations, return an empty string.
#
# Note: Different rearrangements that yield the same palindromic string are considered identical and are counted once.
#
# Example:
# Input: s = "abba", k = 2
#
# Output: "baab"
#
# Explanation:
#
#
# 	The two distinct palindromic rearrangements of "abba" are "abba" and "baab".
# 	Lexicographically, "abba" comes before "baab". Since k = 2, the output is "baab".
#
# Constraints:
# 1 <= s.length <= 104
# 	s consists of lowercase English letters.
# 	s is guaranteed to be palindromic.
# 	1 <= k <= 106
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
# - Generating all K-combinations (array, enumeration, greedy)
#   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
#   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
#   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
#   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
#   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def smallestPalindrome(self, s, k):
        """
        :type s: str
        :type k: int
        :rtype: str
        """
        from collections import Counter
        from math import factorial

        # Count the frequency of each character
        count = Counter(s)
        odd_count = sum(1 for c in count if count[c] % 2 != 0)

        # If there are more than 1 odd counts, it's impossible to form a palindrome
        if odd_count > 1:
            return ""

        # Prepare the half string and the middle character (if any)
        half_str = []
        middle_char = None
        for c in sorted(count.keys()):
            half_str.append(c * (count[c] // 2))
            if count[c] % 2 != 0:
                middle_char = c

        half_str = ''.join(half_str)

        # Calculate the total number of distinct palindromic permutations
        def count_permutations(s):
            freq = Counter(s)
            numerator = factorial(len(s))
            denominator = 1
            for c in freq:
                denominator *= factorial(freq[c])
            return numerator // denominator

        total_permutations = count_permutations(half_str)

        # If k is greater than the total number of permutations, return an empty string
        if k > total_permutations:
            return ""

        # Generate the k-th lexicographical permutation of the half string
        result_half = []
        available_chars = list(half_str)
        
        while available_chars:
            for i in range(len(available_chars)):
                char = available_chars[i]
                # Calculate how many permutations would be possible if we choose this character next
                next_half = result_half + [char] + available_chars[:i] + available_chars[i+1:]
                permutations_with_char = count_permutations(next_half)

                if k <= permutations_with_char:
                    result_half.append(char)
                    available_chars.pop(i)
                    break
                else:
                    k -= permutations_with_char

        # Construct the full palindrome
        result_half_str = ''.join(result_half)
        if middle_char:
            return result_half_str + middle_char + result_half_str[::-1]
        else:
            return result_half_str + result_half_str[::-1]