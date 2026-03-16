# Source: https://leetcode.com/problems/unique-number-of-occurrences/   |   Difficulty: Easy
#
# Problem Description:
# Given an array of integers arr, return true if the number of occurrences of each value in the array is unique or false otherwise.
#
# Example:
# Input: arr = [1,2,2,1,1,3]
# Output: true
# Explanation: The value 1 has 3 occurrences, 2 has 2 and 3 has 1. No two values have the same number of occurrences.
#
# Constraints:
# 1 <= arr.length <= 1000
# 	-1000 <= arr[i] <= 1000
#
# Helpful references (internal KB):
# - N/A
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def uniqueOccurrences(self, arr):
        """
        :type arr: List[int]
        :rtype: bool
        """
        from collections import Counter
        count = Counter(arr)
        occurrences = set()
        
        for freq in count.values():
            if freq in occurrences:
                return False
            occurrences.add(freq)
        
        return True