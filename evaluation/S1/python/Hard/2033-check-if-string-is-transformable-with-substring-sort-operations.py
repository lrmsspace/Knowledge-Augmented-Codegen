# Source: https://leetcode.com/problems/check-if-string-is-transformable-with-substring-sort-operations/   |   Difficulty: Hard
#
# Problem Description:
# Given two strings s and t, transform string s into string t using the following operation any number of times:
#
#
# 	Choose a non-empty substring in s and sort it in place so the characters are in ascending order.
#
# 	
# 		For example, applying the operation on the underlined substring in "14234" results in "12344".
# 	
# 	
#
#
# Return true if it is possible to transform s into t. Otherwise, return false.
#
# A substring is a contiguous sequence of characters within a string.
#
# Example:
# Input: s = "84532", t = "34852"
# Output: true
# Explanation: You can transform s into t using the following sort operations:
# "84532" (from index 2 to 3) -> "84352"
# "84352" (from index 0 to 2) -> "34852"
#
# Constraints:
# s.length == t.length
# 	1 <= s.length <= 105
# 	s and t consist of only digits.
#
# Helpful references (internal KB):
# - Fenwick Tree (array, bit-fenwick, difference-array)
#   • When to use: Use when you need to efficiently calculate prefix sums or range sums on an array that undergoes frequent point updates. It provides logarithmic time complexity for both operations.
#   • Idea: A Fenwick Tree, also known as a Binary Indexed Tree (BIT), is a data structure that can efficiently update individual elements and calculate prefix sums in an array. Both operations are performed in O(log N) time.
#   • Invariants: Each `tree[i]` element stores the sum of a contiguous range of elements from the original array, specifically from `i - (i & -i) + 1` to `i` (inclusive, 1-based).; After any `update(idx, val)` operation, `query(idx)` will reflect the new sum up to `idx`.
#   • Tips: Use 1-based indexing for array elements to simplify bitwise logic; The `idx & -idx` operation is key to navigating the implicit tree structure
#   • Pitfalls: Confusing 0-based and 1-based indexing can lead to incorrect results; Off-by-one errors when calculating range sums (e.g., `query(R) - query(L-1)`)
# - The Inclusion-Exclusion Principle (string, counting)
#   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
#   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
#   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
#   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
#   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
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
    def isTransformable(self, s, t):
        """
        :type s: str
        :type t: str
        :rtype: bool
        """
        from collections import defaultdict
        import bisect

        # Step 1: Build a mapping of characters in s to their indices
        char_positions = defaultdict(list)
        for i, char in enumerate(s):
            char_positions[char].append(i)

        # Step 2: Iterate through characters in t and check if they can be matched in s
        for char in t:
            if char not in char_positions or not char_positions[char]:
                return False  # No more occurrences of char in s

            # Get the index of the next occurrence of char in s
            pos = char_positions[char].pop(0)

            # Check if there are any characters that come before pos that are greater than char
            for c in char_positions:
                if c > char and char_positions[c] and char_positions[c][0] < pos:
                    return False  # Found a character that should have been sorted before

        return True