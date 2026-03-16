# Source: https://leetcode.com/problems/minimum-total-cost-to-make-arrays-unequal/   |   Difficulty: Hard
#
# Problem Description:
# You are given two 0-indexed integer arrays nums1 and nums2, of equal length n.
#
# In one operation, you can swap the values of any two indices of nums1. The cost of this operation is the sum of the indices.
#
# Find the minimum total cost of performing the given operation any number of times such that nums1[i] != nums2[i] for all 0 <= i <= n - 1 after performing all the operations.
#
# Return the minimum total cost such that nums1 and nums2 satisfy the above condition. In case it is not possible, return -1.
#
# Example:
# Input: nums1 = [1,2,3,4,5], nums2 = [1,2,3,4,5]
# Output: 10
# Explanation: 
# One of the ways we can perform the operations is:
# - Swap values at indices 0 and 3, incurring cost = 0 + 3 = 3. Now, nums1 = [4,2,3,1,5]
# - Swap values at indices 1 and 2, incurring cost = 1 + 2 = 3. Now, nums1 = [4,3,2,1,5].
# - Swap values at indices 0 and 4, incurring cost = 0 + 4 = 4. Now, nums1 =[5,3,2,1,4].
# We can see that for each index i, nums1[i] != nums2[i]. The cost required here is 10.
# Note that there are other ways to swap values, but it can be proven that it is not possible to obtain a cost less than 10.
#
# Constraints:
# n == nums1.length == nums2.length
#  1 <= n <= 105
#  1 <= nums1[i], nums2[i] <= n
#

class Solution(object):
    def minimumTotalCost(self, nums1, nums2):
        """
        :type nums1: List[int]
        :type nums2: List[int]
        :rtype: int
        """
        n = len(nums1)
        total_cost = 0
        same_positions = []

        for i in range(n):
            if nums1[i] == nums2[i]:
                same_positions.append(i)

        if not same_positions:
            return 0

        from collections import Counter
        count = Counter()
        for i in same_positions:
            count[nums1[i]] += 1

        max_freq = max(count.values())
        max_freq_num = [num for num, freq in count.items() if freq == max_freq][0]

        swaps_needed = max(0, 2 * max_freq - len(same_positions))
        available_swaps = n - len(same_positions)

        if swaps_needed > available_swaps:
            return -1

        for i in range(n):
            if nums1[i] != nums2[i] and (nums1[i] != max_freq_num and nums2[i] != max_freq_num) and swaps_needed > 0:
                total_cost += i
                swaps_needed -= 1

        for i in same_positions:
            if nums1[i] == max_freq_num and swaps_needed > 0:
                total_cost += i
                swaps_needed -= 1

        for i in same_positions:
            if nums1[i] != max_freq_num:
                total_cost += i

        return total_cost