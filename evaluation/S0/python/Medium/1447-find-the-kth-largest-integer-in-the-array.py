# Source: https://leetcode.com/problems/find-the-kth-largest-integer-in-the-array/   |   Difficulty: Medium
#
# Problem Description:
# You are given an array of strings nums and an integer k. Each string in nums represents an integer without leading zeros.
#
# Return the string that represents the kth largest integer in nums.
#
# Note: Duplicate numbers should be counted distinctly. For example, if nums is ["1","2","2"], "2" is the first largest integer, "2" is the second-largest integer, and "1" is the third-largest integer.
#
# Example:
# Input: nums = ["3","6","7","10"], k = 4
# Output: "3"
# Explanation:
# The numbers in nums sorted in non-decreasing order are ["3","6","7","10"].
# The 4th largest integer in nums is "3".
#
# Constraints:
# 1 <= k <= nums.length <= 104
# 	1 <= nums[i].length <= 100
# 	nums[i] consists of only digits.
# 	nums[i] will not have any leading zeros.
#

class Solution(object):
    def kthLargestNumber(self, nums, k):
        """
        :type nums: List[str]
        :type k: int
        :rtype: str
        """
        nums.sort(key=lambda x: (len(x), x), reverse=True)
        return nums[k - 1]