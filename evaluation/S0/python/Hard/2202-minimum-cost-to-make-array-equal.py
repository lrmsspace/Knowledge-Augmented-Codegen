# Source: https://leetcode.com/problems/minimum-cost-to-make-array-equal/   |   Difficulty: Hard
#
# Problem Description:
# You are given two 0-indexed arrays nums and cost consisting each of n positive integers.
#
# You can do the following operation any number of times:
#
#
# 	Increase or decrease any element of the array nums by 1.
#
#
# The cost of doing one operation on the ith element is cost[i].
#
# Return the minimum total cost such that all the elements of the array nums become equal.
#
# Example:
# Input: nums = [1,3,5,2], cost = [2,3,1,14]
# Output: 8
# Explanation: We can make all the elements equal to 2 in the following way:
# - Increase the 0th element one time. The cost is 2.
# - Decrease the 1st element one time. The cost is 3.
# - Decrease the 2nd element three times. The cost is 1 + 1 + 1 = 3.
# The total cost is 2 + 3 + 3 = 8.
# It can be shown that we cannot make the array equal with a smaller cost.
#
# Constraints:
# n == nums.length == cost.length
# 	1 <= n <= 105
# 	1 <= nums[i], cost[i] <= 106
# 	Test cases are generated in a way that the output doesn't exceed 253-1
#

class Solution(object):
    def minCost(self, nums, cost):
        """
        :type nums: List[int]
        :type cost: List[int]
        :rtype: int
        """
        def compute_total_cost(target):
            total_cost = 0
            for i in range(len(nums)):
                total_cost += abs(nums[i] - target) * cost[i]
            return total_cost

        left, right = min(nums), max(nums)
        min_total_cost = float('inf')

        while left <= right:
            mid = (left + right) // 2
            cost_mid = compute_total_cost(mid)
            cost_mid_plus_one = compute_total_cost(mid + 1)

            min_total_cost = min(min_total_cost, cost_mid, cost_mid_plus_one)

            if cost_mid < cost_mid_plus_one:
                right = mid - 1
            else:
                left = mid + 1

        return min_total_cost