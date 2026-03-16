# Source: https://leetcode.com/problems/maximum-product-after-k-increments/   |   Difficulty: Medium
#
# Problem Description:
# You are given an array of non-negative integers nums and an integer k. In one operation, you may choose any element from nums and increment it by 1.
#
# Return the maximum product of nums after at most k operations. Since the answer may be very large, return it modulo 109 + 7. Note that you should maximize the product before taking the modulo.
#
# Example:
# Input: nums = [0,4], k = 5
# Output: 20
# Explanation: Increment the first number 5 times.
# Now nums = [5, 4], with a product of 5 * 4 = 20.
# It can be shown that 20 is maximum product possible, so we return 20.
# Note that there may be other ways to increment nums to have the maximum product.
#
# Constraints:
# 1 <= nums.length, k <= 105
# 	0 <= nums[i] <= 106
#

class Solution(object):
    def maximumProduct(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        import heapq

        MOD = 10**9 + 7
        min_heap = nums[:]
        heapq.heapify(min_heap)

        for _ in range(k):
            smallest = heapq.heappop(min_heap)
            smallest += 1
            heapq.heappush(min_heap, smallest)

        product = 1
        for num in min_heap:
            product = (product * num) % MOD

        return product