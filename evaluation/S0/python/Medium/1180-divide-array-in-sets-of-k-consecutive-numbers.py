# Source: https://leetcode.com/problems/divide-array-in-sets-of-k-consecutive-numbers/   |   Difficulty: Medium
#
# Problem Description:
# Given an array of integers nums and a positive integer k, check whether it is possible to divide this array into sets of k consecutive numbers.
#
# Return true if it is possible. Otherwise, return false.
#
# Example:
# Input: nums = [1,2,3,3,4,4,5,6], k = 4
# Output: true
# Explanation: Array can be divided into [1,2,3,4] and [3,4,5,6].
#
# Constraints:
# 1 <= k <= nums.length <= 105
# 	1 <= nums[i] <= 109
#
#
#  
# Note: This question is the same as 846: https://leetcode.com/problems/hand-of-straights/
#

class Solution(object):
    def isPossibleDivide(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: bool
        """
        from collections import Counter
        import heapq

        if len(nums) % k != 0:
            return False

        count = Counter(nums)
        min_heap = list(count.keys())
        heapq.heapify(min_heap)

        while min_heap:
            first = min_heap[0]
            for i in range(first, first + k):
                if i not in count:
                    return False
                count[i] -= 1
                if count[i] == 0:
                    if i != min_heap[0]:
                        return False
                    heapq.heappop(min_heap)

        return True