# Source: https://leetcode.com/problems/check-if-strings-can-be-made-equal-with-operations-ii/   |   Difficulty: Medium
#
# Problem Description:
# You are given two strings s1 and s2, both of length n, consisting of lowercase English letters.
#
# You can apply the following operation on any of the two strings any number of times:
#
#
# 	Choose any two indices i and j such that i < j and the difference j - i is even, then swap the two characters at those indices in the string.
#
#
# Return true if you can make the strings s1 and s2 equal, and false otherwise.
#
# Example:
# Input: s1 = "abcdba", s2 = "cabdab"
# Output: true
# Explanation: We can apply the following operations on s1:
# - Choose the indices i = 0, j = 2. The resulting string is s1 = "cbadba".
# - Choose the indices i = 2, j = 4. The resulting string is s1 = "cbbdaa".
# - Choose the indices i = 1, j = 5. The resulting string is s1 = "cabdab" = s2.
#
# Constraints:
# n == s1.length == s2.length
# 	1 <= n <= 105
# 	s1 and s2 consist only of lowercase English letters.
#
# Helpful references (internal KB):
# - The Inclusion-Exclusion Principle (string, counting)
#   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
#   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
#   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
#   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
#   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
# - Suffix Array (array, string, simulation, two-pointers)
#   • When to use: Use when needing to efficiently compare substrings, find all occurrences of a pattern, or determine lexicographical order among suffixes within a string.
#   • Idea: A Suffix Array stores sorted suffixes of a string, enabling fast substring comparisons and pattern searching. Construction typically takes O(N log N) time, with comparisons often O(1) after preprocessing.
#   • Invariants: The suffix array `p` contains all suffixes of the string `s` sorted lexicographically.; During construction, equivalence classes `c` correctly group suffixes that are identical up to a certain length `2^k`.
#   • Tips: Precompute log values for efficient block length calculation.; Utilize equivalence classes for O(1) comparison of power-of-two length substrings.
#   • Pitfalls: Complexity of suffix array construction can be tricky (e.g., O(N log N) vs O(N)).; Off-by-one errors when calculating block indices or lengths.
# - Suffix Array (string, array, counting-sort, radix-sort)
#   • When to use: Use when you need to efficiently query or analyze all suffixes of a string, often for pattern matching, string searching, or finding repeated substrings. It provides a sorted order of all suffixes.
#   • Idea: The Suffix Array algorithm constructs an array containing the starting indices of all suffixes of a string, sorted lexicographically. It typically uses a doubling strategy with counting sort or radix sort in each step, achieving an O(N log N) time complexity.
#   • Invariants: After iteration k, p contains the sorted indices of all cyclic substrings of length 2^k.; After iteration k, c[i] represents the equivalence class of the cyclic substring starting at i with length 2^k.
#   • Tips: Append a unique, smallest character (e.g., '$') to the string to handle suffixes as cyclic shifts.; Utilize counting sort for efficient sorting of characters and pairs of equivalence classes.
#   • Pitfalls: Incorrectly handling the sentinel character can lead to incorrect suffix order or out-of-bounds access.; Off-by-one errors when calculating indices for cyclic shifts or substring lengths.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def checkStrings(self, s1, s2):
        """
        :type s1: str
        :type s2: str
        :rtype: bool
        """
        from collections import Counter
        
        # Count characters at even and odd indices separately for both strings
        count_s1_even = Counter(s1[i] for i in range(0, len(s1), 2))
        count_s1_odd = Counter(s1[i] for i in range(1, len(s1), 2))
        count_s2_even = Counter(s2[i] for i in range(0, len(s2), 2))
        count_s2_odd = Counter(s2[i] for i in range(1, len(s2), 2))
        
        # Check if the counts match for even and odd indices
        return count_s1_even == count_s2_even and count_s1_odd == count_s2_odd