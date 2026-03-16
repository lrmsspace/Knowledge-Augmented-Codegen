# Source: https://leetcode.com/problems/make-the-xor-of-all-segments-equal-to-zero/   |   Difficulty: Hard
#
# Problem Description:
# You are given an array nums​​​ and an integer k​​​​​. The XOR of a segment [left, right] where left <= right is the XOR of all the elements with indices between left and right, inclusive: nums[left] XOR nums[left+1] XOR ... XOR nums[right].
#
# Return the minimum number of elements to change in the array such that the XOR of all segments of size k​​​​​​ is equal to zero.
#
# Example:
# Input: nums = [1,2,0,3,0], k = 1
# Output: 3
# Explanation: Modify the array from [1,2,0,3,0] to from [0,0,0,0,0].
#
# Constraints:
# 1 <= k <= nums.length <= 2000
# 	​​​​​​0 <= nums[i] < 210
#

class Solution(object):
    def minChanges(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        from collections import defaultdict
        n = len(nums)
        max_xor = 1 << 10
        dp = [float('inf')] * max_xor
        dp[0] = 0

        for i in range(k):
            count = defaultdict(int)
            size = 0
            for j in range(i, n, k):
                count[nums[j]] += 1
                size += 1

            min_dp = min(dp)
            new_dp = [min_dp] * max_xor

            for mask in range(max_xor):
                for x in count:
                    new_dp[mask] = min(new_dp[mask], dp[mask ^ x] - count[x])

            for mask in range(max_xor):
                new_dp[mask] += size

            dp = new_dp

        return dp[0]