# Source: https://leetcode.com/problems/peaks-in-array/   |   Difficulty: Hard
#
# Problem Description:
# A peak in an array arr is an element that is greater than its previous and next element in arr.
#
# You are given an integer array nums and a 2D integer array queries.
#
# You have to process queries of two types:
#
#
# 	queries[i] = [1, li, ri], determine the count of peak elements in the subarray nums[li..ri].
# 	queries[i] = [2, indexi, vali], change nums[indexi] to vali.
#
#
# Return an array answer containing the results of the queries of the first type in order.
#
# Input: nums = [3,1,4,2,5], queries = [[2,3,4],[1,0,4]]
#
# Output: [0]
#
# Explanation:
#
# First query: We change nums[3] to 4 and nums becomes [3,1,4,4,5].
#
# Second query: The number of peaks in the [3,1,4,4,5] is 0.
#
# Constraints:
# 3 <= nums.length <= 105
# 	1 <= nums[i] <= 105
# 	1 <= queries.length <= 105
# 	queries[i][0] == 1 or queries[i][0] == 2
# 	For all i that:
# 	
# 		queries[i][0] == 1: 0 <= queries[i][1] <= queries[i][2] <= nums.length - 1
# 		queries[i][0] == 2: 0 <= queries[i][1] <= nums.length - 1, 1 <= queries[i][2] <= 105
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def countOfPeaks(self, nums, queries):
        """
        :type nums: List[int]
        :type queries: List[List[int]]
        :rtype: List[int]
        """
        n = len(nums)
        peaks = [0] * n
        
        # Function to check if an index is a peak
        def is_peak(i):
            if i <= 0 or i >= n - 1:
                return False
            return nums[i] > nums[i - 1] and nums[i] > nums[i + 1]
        
        # Initialize peaks array
        for i in range(1, n - 1):
            if is_peak(i):
                peaks[i] = 1
        
        result = []
        
        for query in queries:
            if query[0] == 1:
                l, r = query[1], query[2]
                count = sum(peaks[l:r+1])
                result.append(count)
            elif query[0] == 2:
                index, val = query[1], query[2]
                nums[index] = val
                
                # Update peaks around the changed index
                for i in range(max(1, index - 1), min(n - 1, index + 2)):
                    peaks[i] = 1 if is_peak(i) else 0
        
        return result