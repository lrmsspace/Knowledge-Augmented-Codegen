# Source: https://leetcode.com/problems/get-the-maximum-score/   |   Difficulty: Hard
#
# Problem Description:
# You are given two sorted arrays of distinct integers nums1 and nums2.
#
# A valid path is defined as follows:
#
#
# 	Choose array nums1 or nums2 to traverse (from index-0).
# 	Traverse the current array from left to right.
# 	If you are reading any value that is present in nums1 and nums2 you are allowed to change your path to the other array. (Only one repeated value is considered in the valid path).
#
#
# The score is defined as the sum of unique values in a valid path.
#
# Return the maximum score you can obtain of all possible valid paths. Since the answer may be too large, return it modulo 109 + 7.
#
# Example:
# Input: nums1 = [2,4,5,8,10], nums2 = [4,6,8,9]
# Output: 30
# Explanation: Valid paths:
# [2,4,5,8,10], [2,4,5,8,9], [2,4,6,8,9], [2,4,6,8,10],  (starting from nums1)
# [4,6,8,9], [4,5,8,10], [4,5,8,9], [4,6,8,10]    (starting from nums2)
# The maximum is obtained with the path in green [2,4,6,8,10].
#
# Constraints:
# 1 <= nums1.length, nums2.length <= 105
# 	1 <= nums1[i], nums2[i] <= 107
# 	nums1 and nums2 are strictly increasing.
#

class Solution(object):
    def maxSum(self, nums1, nums2):
        """
        :type nums1: List[int]
        :type nums2: List[int]
        :rtype: int
        """
        MOD = 10**9 + 7
        i, j = 0, 0
        sum1, sum2 = 0, 0
        n, m = len(nums1), len(nums2)

        while i < n or j < m:
            if i < n and (j == m or nums1[i] < nums2[j]):
                sum1 += nums1[i]
                i += 1
            elif j < m and (i == n or nums1[i] > nums2[j]):
                sum2 += nums2[j]
                j += 1
            else:
                max_sum = max(sum1, sum2) + nums1[i]
                sum1 = max_sum
                sum2 = max_sum
                i += 1
                j += 1

        return max(sum1, sum2) % MOD