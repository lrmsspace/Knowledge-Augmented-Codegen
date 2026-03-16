# Source: https://leetcode.com/problems/find-two-non-overlapping-sub-arrays-each-with-target-sum/   |   Difficulty: Medium
#
# Problem Description:
# You are given an array of integers arr and an integer target.
#
# You have to find two non-overlapping sub-arrays of arr each with a sum equal target. There can be multiple answers so you have to find an answer where the sum of the lengths of the two sub-arrays is minimum.
#
# Return the minimum sum of the lengths of the two required sub-arrays, or return -1 if you cannot find such two sub-arrays.
#
# Example:
# Input: arr = [3,2,2,4,3], target = 3
# Output: 2
# Explanation: Only two sub-arrays have sum = 3 ([3] and [3]). The sum of their lengths is 2.
#
# Constraints:
# 1 <= arr.length <= 105
# 	1 <= arr[i] <= 1000
# 	1 <= target <= 108
#

class Solution(object):
    def minSumOfLengths(self, arr, target):
        """
        :type arr: List[int]
        :type target: int
        :rtype: int
        """
        n = len(arr)
        prefix_sum = {0: -1}
        curr_sum = 0
        min_len = [float('inf')] * n
        result = float('inf')
        best_len = float('inf')

        for i in range(n):
            curr_sum += arr[i]
            if curr_sum - target in prefix_sum:
                start_index = prefix_sum[curr_sum - target] + 1
                curr_len = i - start_index + 1

                if start_index > 0 and min_len[start_index - 1] != float('inf'):
                    result = min(result, curr_len + min_len[start_index - 1])

                best_len = min(best_len, curr_len)

            min_len[i] = best_len
            prefix_sum[curr_sum] = i

        return result if result != float('inf') else -1