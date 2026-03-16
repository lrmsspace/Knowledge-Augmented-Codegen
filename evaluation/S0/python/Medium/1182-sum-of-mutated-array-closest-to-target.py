# Source: https://leetcode.com/problems/sum-of-mutated-array-closest-to-target/   |   Difficulty: Medium
#
# Problem Description:
# Given an integer array arr and a target value target, return the integer value such that when we change all the integers larger than value in the given array to be equal to value, the sum of the array gets as close as possible (in absolute difference) to target.
#
# In case of a tie, return the minimum such integer.
#
# Notice that the answer is not neccesarilly a number from arr.
#
# Example:
# Input: arr = [4,9,3], target = 10
# Output: 3
# Explanation: When using 3 arr converts to [3, 3, 3] which sums 9 and that's the optimal answer.
#
# Constraints:
# 1 <= arr.length <= 104
# 	1 <= arr[i], target <= 105
#

class Solution(object):
    def findBestValue(self, arr, target):
        """
        :type arr: List[int]
        :type target: int
        :rtype: int
        """
        left, right = 0, max(arr)
        result = right
        min_diff = float('inf')

        while left <= right:
            mid = (left + right) // 2
            current_sum = sum(min(x, mid) for x in arr)
            current_diff = abs(current_sum - target)

            if current_diff < min_diff or (current_diff == min_diff and mid < result):
                min_diff = current_diff
                result = mid

            if current_sum < target:
                left = mid + 1
            else:
                right = mid - 1

        return result