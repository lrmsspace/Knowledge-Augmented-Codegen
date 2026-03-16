# Source: https://leetcode.com/problems/maximum-sum-circular-subarray/   |   Difficulty: Medium
#
# Problem Description:
# Given a circular integer array nums of length n, return the maximum possible sum of a non-empty subarray of nums.
#
# A circular array means the end of the array connects to the beginning of the array. Formally, the next element of nums[i] is nums[(i + 1) % n] and the previous element of nums[i] is nums[(i - 1 + n) % n].
#
# A subarray may only include each element of the fixed buffer nums at most once. Formally, for a subarray nums[i], nums[i + 1], ..., nums[j], there does not exist i <= k1, k2 <= j with k1 % n == k2 % n.
#
# Example:
# Input: nums = [1,-2,3,-2]
# Output: 3
# Explanation: Subarray [3] has maximum sum 3.
#
# Constraints:
# n == nums.length
# 	1 <= n <= 3 * 104
# 	-3 * 104 <= nums[i] <= 3 * 104
#

class Solution(object):
    def maxSubarraySumCircular(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        def kadane(gen):
            # Standard Kadane's algorithm to find maximum subarray sum
            curr = best = float('-inf')
            for x in gen:
                curr = x + max(curr, 0)
                best = max(best, curr)
            return best

        S = sum(nums)
        # Maximum subarray sum using standard Kadane's algorithm
        ans1 = kadane(nums)
        # Maximum subarray sum that wraps around the array
        ans2 = S + kadane(-nums[i] for i in range(1, len(nums)))  # Exclude first element
        ans3 = S + kadane(-nums[i] for i in range(len(nums) - 1))  # Exclude last element

        return max(ans1, ans2, ans3) if ans1 > 0 else ans1