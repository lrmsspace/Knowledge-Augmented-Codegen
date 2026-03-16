# Source: https://leetcode.com/problems/create-maximum-number/   |   Difficulty: Hard
#
# Problem Description:
# You are given two integer arrays nums1 and nums2 of lengths m and n respectively. nums1 and nums2 represent the digits of two numbers. You are also given an integer k.
#
# Create the maximum number of length k <= m + n from digits of the two numbers. The relative order of the digits from the same array must be preserved.
#
# Return an array of the k digits representing the answer.
#
# Example:
# Input: nums1 = [3,4,6,5], nums2 = [9,1,2,5,8,3], k = 5
# Output: [9,8,6,5,3]
#
# Constraints:
# m == nums1.length
# 	n == nums2.length
# 	1 <= m, n <= 500
# 	0 <= nums1[i], nums2[i] <= 9
# 	1 <= k <= m + n
# 	nums1 and nums2 do not have leading zeros.
#

class Solution(object):
    def maxNumber(self, nums1, nums2, k):
        """
        :type nums1: List[int]
        :type nums2: List[int]
        :type k: int
        :rtype: List[int]
        """
        def pick_max(nums, pick):
            drop = len(nums) - pick
            stack = []
            for num in nums:
                while drop and stack and stack[-1] < num:
                    stack.pop()
                    drop -= 1
                stack.append(num)
            return stack[:pick]

        def merge(nums1, nums2):
            return [max(nums1, nums2).pop(0) for _ in range(len(nums1) + len(nums2))]

        max_num = []
        start = max(0, k - len(nums2))
        end = min(k, len(nums1))
        for i in range(start, end + 1):
            part1 = pick_max(nums1, i)
            part2 = pick_max(nums2, k - i)
            candidate = merge(part1, part2)
            max_num = max(max_num, candidate)
        return max_num