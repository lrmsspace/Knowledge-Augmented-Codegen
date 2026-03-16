# Source: https://leetcode.com/problems/equal-sum-arrays-with-minimum-number-of-operations/   |   Difficulty: Medium
#
# Problem Description:
# You are given two arrays of integers nums1 and nums2, possibly of different lengths. The values in the arrays are between 1 and 6, inclusive.
#
# In one operation, you can change any integer's value in any of the arrays to any value between 1 and 6, inclusive.
#
# Return the minimum number of operations required to make the sum of values in nums1 equal to the sum of values in nums2. Return -1​​​​​ if it is not possible to make the sum of the two arrays equal.
#
# Example:
# Input: nums1 = [1,2,3,4,5,6], nums2 = [1,1,2,2,2,2]
# Output: 3
# Explanation: You can make the sums of nums1 and nums2 equal with 3 operations. All indices are 0-indexed.
# - Change nums2[0] to 6. nums1 = [1,2,3,4,5,6], nums2 = [6,1,2,2,2,2].
# - Change nums1[5] to 1. nums1 = [1,2,3,4,5,1], nums2 = [6,1,2,2,2,2].
# - Change nums1[2] to 2. nums1 = [1,2,2,4,5,1], nums2 = [6,1,2,2,2,2].
#
# Constraints:
# 1 <= nums1.length, nums2.length <= 105
# 	1 <= nums1[i], nums2[i] <= 6
#

class Solution(object):
    def minOperations(self, nums1, nums2):
        """
        :type nums1: List[int]
        :type nums2: List[int]
        :rtype: int
        """
        sum1, sum2 = sum(nums1), sum(nums2)
        if sum1 == sum2:
            return 0
        if 6 * len(nums1) < sum2 or 6 * len(nums2) < sum1:
            return -1
        
        if sum1 > sum2:
            nums1, nums2 = nums2, nums1
            sum1, sum2 = sum2, sum1
        
        diff = sum2 - sum1
        changes = []
        
        for n in nums1:
            changes.append(6 - n)
        for n in nums2:
            changes.append(n - 1)
        
        changes.sort(reverse=True)
        
        ops = 0
        for change in changes:
            diff -= change
            ops += 1
            if diff <= 0:
                return ops
        
        return -1