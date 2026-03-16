# Source: https://leetcode.com/problems/maximal-score-after-applying-k-operations/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 0-indexed integer array nums and an integer k. You have a starting score of 0.
#
# In one operation:
#
#
# 	choose an index i such that 0 <= i < nums.length,
# 	increase your score by nums[i], and
# 	replace nums[i] with ceil(nums[i] / 3).
#
#
# Return the maximum possible score you can attain after applying exactly k operations.
#
# The ceiling function ceil(val) is the least integer greater than or equal to val.
#
# Example:
# Input: nums = [10,10,10,10,10], k = 5
# Output: 50
# Explanation: Apply the operation to each array element exactly once. The final score is 10 + 10 + 10 + 10 + 10 = 50.
#
# Constraints:
# 1 <= nums.length, k <= 105
# 	1 <= nums[i] <= 109
#

class Solution(object):
    def maxKelements(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        import heapq
        max_heap = [-num for num in nums]
        heapq.heapify(max_heap)
        score = 0
        
        for _ in range(k):
            largest = -heapq.heappop(max_heap)
            score += largest
            new_value = -((largest + 2) // 3)  # ceil division
            heapq.heappush(max_heap, new_value)
        
        return score