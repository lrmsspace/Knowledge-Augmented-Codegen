# Source: https://leetcode.com/problems/find-the-peaks/   |   Difficulty: Easy
#
# Problem Description:
# You are given a 0-indexed array mountain. Your task is to find all the peaks in the mountain array.
#
# Return an array that consists of indices of peaks in the given array in any order.
#
# Example:
# Input: mountain = [2,4,4]
# Output: []
# Explanation: mountain[0] and mountain[2] can not be a peak because they are first and last elements of the array.
# mountain[1] also can not be a peak because it is not strictly greater than mountain[2].
# So the answer is [].
#
# Constraints:
# 3 <= mountain.length <= 100
# 	1 <= mountain[i] <= 100
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def findPeaks(self, mountain):
        """
        :type mountain: List[int]
        :rtype: List[int]
        """
        peaks = []
        for i in range(1, len(mountain) - 1):
            if mountain[i] > mountain[i - 1] and mountain[i] > mountain[i + 1]:
                peaks.append(i)
        return peaks