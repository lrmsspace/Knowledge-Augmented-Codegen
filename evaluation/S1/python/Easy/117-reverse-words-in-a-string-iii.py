# Source: https://leetcode.com/problems/reverse-words-in-a-string-iii/   |   Difficulty: Easy
#
# Problem Description:
# Given a string s, reverse the order of characters in each word within a sentence while still preserving whitespace and initial word order.
#
# Example:
# Input: s = "Let's take LeetCode contest"
# Output: "s'teL ekat edoCteeL tsetnoc"
#
# Constraints:
# 1 <= s.length <= 5 * 104
# 	s contains printable ASCII characters.
# 	s does not contain any leading or trailing spaces.
# 	There is at least one word in s.
# 	All the words in s are separated by a single space.
#
# Helpful references (internal KB):
# - palindrome-partitioning (string, two-pointers, simulation)
#   • When to use: When a string needs to be decomposed into all possible sets of palindromic substrings. It's suitable for problems requiring exhaustive enumeration of such partitions.
#   • Idea: This algorithm finds all possible ways to partition a given string such that every substring in the partition is a palindrome. It typically uses a recursive exploration approach combined with a two-pointer check for palindrome validation, resulting in an exponential time complexity.
#   • Invariants: At any point, the `step` list contains a valid palindromic partition of the prefix processed so far.; The `s` parameter in the recursive function always represents the unpartitioned suffix of the original string.
#   • Tips: Implement the `isPalindrome` check efficiently using two pointers for O(length) time.; Use a recursive helper function to explore all possible partition points.
#   • Pitfalls: Incorrectly handling substring boundaries, leading to off-by-one errors or incorrect partitions.; Forgetting to backtrack (remove the last added substring) after a recursive call returns.
# - Lyndon factorization (string, greedy, two-pointers)
#   • When to use: Use this algorithm to decompose a string into a unique sequence of Lyndon words, which are lexicographically smallest among their cyclic shifts. It is also applicable for finding the smallest cyclic shift of a string.
#   • Idea: The Duval algorithm greedily factorizes a string into a sequence of Lyndon words by maintaining three pointers to manage processed, pre-simple, and untouched parts. It achieves this in O(N) time complexity.
#   • Invariants: The prefix s[0...i-1] always contains a valid Lyndon factorization.; The substring s[i...j-1] is always a pre-simple string.
#   • Tips: Thoroughly understand the definitions of 'simple string' and 'pre-simple string' to correctly apply the comparison logic.; The three pointers (i, j, k) are crucial; 'i' marks the start of the current pre-simple string, 'j' the start of the untouched part, and 'k' for comparison within the pre-simple string.
#   • Pitfalls: Incorrectly resetting the 'k' pointer when s[j] > s[k], which should point back to the beginning of the simple word within s2.; Misinterpreting the length of the simple string (j - k) when a factorization step occurs.
# - Minkowski sum of convex polygons (geometry, array, two-pointers)
#   • When to use: When needing to compute the sum of two convex polygons, or efficiently determine the minimum distance or intersection between them.
#   • Idea: The Minkowski sum of two convex polygons P and Q is a new convex polygon formed by vector addition of all points from P and Q. It can be computed in O(|P| + |Q|) time by merging their edge vectors.
#   • Invariants: The current edge added to the Minkowski sum is the one with the smallest angle among the remaining edges from both polygons.; The sequence of edges in the Minkowski sum maintains convexity.
#   • Tips: The vertices of P+Q are sums of vertices of P and Q.; The edges of P+Q are the edges of P and Q, sorted by angle.
#   • Pitfalls: Incorrectly handling edge cases like collinear edges or degenerate polygons.; Floating point precision issues in geometric calculations.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def reverseWords(self, s):
        """
        :type s: str
        :rtype: str
        """
        words = s.split(' ')
        reversed_words = [word[::-1] for word in words]
        return ' '.join(reversed_words)