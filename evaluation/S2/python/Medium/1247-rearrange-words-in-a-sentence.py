# Source: https://leetcode.com/problems/rearrange-words-in-a-sentence/   |   Difficulty: Medium
#
# Problem Description:
# Given a sentence text (A sentence is a string of space-separated words) in the following format:
#
#
# 	First letter is in upper case.
# 	Each word in text are separated by a single space.
#
#
# Your task is to rearrange the words in text such that all words are rearranged in an increasing order of their lengths. If two words have the same length, arrange them in their original order.
#
# Return the new text following the format shown above.
#
# Example:
# Input: text = "Leetcode is cool"
# Output: "Is cool leetcode"
# Explanation: There are 3 words, "Leetcode" of length 8, "is" of length 2 and "cool" of length 4.
# Output is ordered by length and the new first word starts with capital letter.
#
# Constraints:
# text begins with a capital letter and then contains lowercase letters and single space between words.
# 	1 <= text.length <= 10^5
#
# Helpful references (internal KB):
# - Lyndon factorization (string, greedy, two-pointers)
#   • When to use: Use this algorithm to decompose a string into a unique sequence of Lyndon words, which are lexicographically smallest among their cyclic shifts. It is also applicable for finding the smallest cyclic shift of a string.
#   • Idea: The Duval algorithm greedily factorizes a string into a sequence of Lyndon words by maintaining three pointers to manage processed, pre-simple, and untouched parts. It achieves this in O(N) time complexity.
#   • Invariants: The prefix s[0...i-1] always contains a valid Lyndon factorization.; The substring s[i...j-1] is always a pre-simple string.
#   • Tips: Thoroughly understand the definitions of 'simple string' and 'pre-simple string' to correctly apply the comparison logic.; The three pointers (i, j, k) are crucial; 'i' marks the start of the current pre-simple string, 'j' the start of the untouched part, and 'k' for comparison within the pre-simple string.
#   • Pitfalls: Incorrectly resetting the 'k' pointer when s[j] > s[k], which should point back to the beginning of the simple word within s2.; Misinterpreting the length of the simple string (j - k) when a factorization step occurs.
# - bucket-sort (array, bucket-sort)
#   • When to use: Use when sorting elements with a known, uniform distribution over a specific range. It is efficient for numbers that are uniformly distributed across a range, often achieving linear time complexity.
#   • Idea: Bucket sort distributes elements into a fixed number of buckets, sorts each bucket individually, and then concatenates them. It can achieve O(N+K) average time complexity for uniformly distributed data.
#   • Invariants: After distributing elements, each element `x` is in bucket `floor(N * x)`.; After sorting buckets, every bucket `buckets[i]` contains its elements in sorted order.
#   • Tips: Choose the number of buckets appropriately based on data distribution and range.; Normalize input data to a [0, 1) range for simpler bucket indexing.
#   • Pitfalls: Poor performance with non-uniform data distribution, potentially degrading to O(N^2).; Requires extra space for the buckets, proportional to N+K.
# - Longest increasing subsequence (array, dp-1d, segment-tree, coordinate-compress)
#   • When to use: Use when you need to find the longest possible subsequence of a given sequence such that elements in the subsequence are in strictly increasing order, preserving their original relative order.
#   • Idea: This algorithm finds the longest subsequence where elements are in strictly increasing order. It can be solved with dynamic programming in O(N^2) time or optimized to O(N log N) using binary search or a segment tree.
#   • Invariants: The 'tails' array (or DP array) is always sorted in increasing order.; For any index 'i', 'tails[i]' stores the smallest possible ending element of an increasing subsequence of length 'i+1'.
#   • Tips: The O(N log N) approach maintains an array where dp[i] stores the smallest ending element of an increasing subsequence of length i+1.; Binary search is used to find the correct position for the current element in the dp array.
#   • Pitfalls: Confusing subsequence with subarray, which requires contiguous elements.; Incorrectly handling duplicates for strictly increasing versus non-decreasing requirements.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def arrangeWords(self, text):
        """
        :type text: str
        :rtype: str
        """
        words = text.split()
        words[0] = words[0].lower()  # Convert the first word to lowercase for sorting
        words.sort(key=lambda w: (len(w), words.index(w)))  # Sort by length, then by original order
        words[0] = words[0].capitalize()  # Capitalize the first word of the result
        return ' '.join(words)