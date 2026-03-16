# Source: https://leetcode.com/problems/choose-k-elements-with-maximum-sum/   |   Difficulty: Medium
#
# Problem Description:
# You are given two integer arrays, nums1 and nums2, both of length n, along with a positive integer k.
#
# For each index i from 0 to n - 1, perform the following:
#
#
# 	Find all indices j where nums1[j] is less than nums1[i].
# 	Choose at most k values of nums2[j] at these indices to maximize the total sum.
#
#
# Return an array answer of size n, where answer[i] represents the result for the corresponding index i.
#
# Example:
# Input: nums1 = [4,2,1,5,3], nums2 = [10,20,30,40,50], k = 2
#
# Output: [80,30,0,80,50]
#
# Explanation:
#
#
# 	For i = 0: Select the 2 largest values from nums2 at indices [1, 2, 4] where nums1[j] < nums1[0], resulting in 50 + 30 = 80.
# 	For i = 1: Select the 2 largest values from nums2 at index [2] where nums1[j] < nums1[1], resulting in 30.
# 	For i = 2: No indices satisfy nums1[j] < nums1[2], resulting in 0.
# 	For i = 3: Select the 2 largest values from nums2 at indices [0, 1, 2, 4] where nums1[j] < nums1[3], resulting in 50 + 30 = 80.
# 	For i = 4: Select the 2 largest values from nums2 at indices [1, 2] where nums1[j] < nums1[4], resulting in 30 + 20 = 50.
#
# Constraints:
# n == nums1.length == nums2.length
# 	1 <= n <= 105
# 	1 <= nums1[i], nums2[i] <= 106
# 	1 <= k <= n
#

class Solution(object):
    def findMaxSum(self, nums1, nums2, k):
        """
        :type nums1: List[int]
        :type nums2: List[int]
        :type k: int
        :rtype: List[int]
        """
        n = len(nums1)
        result = [0] * n
        
        for i in range(n):
            candidates = [nums2[j] for j in range(n) if nums1[j] < nums1[i]]
            candidates.sort(reverse=True)
            result[i] = sum(candidates[:k])
        
        return result