# Source: https://leetcode.com/problems/maximum-number-of-ways-to-partition-an-array/   |   Difficulty: Hard
#
# Problem Description:
# You are given a 0-indexed integer array nums of length n. The number of ways to partition nums is the number of pivot indices that satisfy both conditions:
#
#
# 	1 <= pivot < n
# 	nums[0] + nums[1] + ... + nums[pivot - 1] == nums[pivot] + nums[pivot + 1] + ... + nums[n - 1]
#
#
# You are also given an integer k. You can choose to change the value of one element of nums to k, or to leave the array unchanged.
#
# Return the maximum possible number of ways to partition nums to satisfy both conditions after changing at most one element.
#
# Example:
# Input: nums = [2,-1,2], k = 3
# Output: 1
# Explanation: One optimal approach is to change nums[0] to k. The array becomes [3,-1,2].
# There is one way to partition the array:
# - For pivot = 2, we have the partition [3,-1 | 2]: 3 + -1 == 2.
#
# Constraints:
# n == nums.length
# 	2 <= n <= 105
# 	-105 <= k, nums[i] <= 105
#

class Solution(object):
    def waysToPartition(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        n = len(nums)
        total_sum = sum(nums)
        prefix_sum = 0
        count_map = {}
        base_count = 0

        for i in range(n - 1):
            prefix_sum += nums[i]
            suffix_sum = total_sum - prefix_sum

            if prefix_sum == suffix_sum:
                base_count += 1

            diff = suffix_sum - prefix_sum
            count_map[diff] = count_map.get(diff, 0) + 1

        max_ways = base_count

        prefix_sum = 0
        for i in range(n):
            old_val = nums[i]
            new_val = k
            diff = new_val - old_val

            current_ways = base_count
            current_ways += count_map.get(diff, 0)
            current_ways -= count_map.get(-diff, 0)

            max_ways = max(max_ways, current_ways)

            prefix_sum += old_val
            suffix_sum = total_sum - prefix_sum

            if i < n - 1:
                if prefix_sum == suffix_sum:
                    base_count -= 1

                diff = suffix_sum - prefix_sum
                count_map[diff] -= 1

        return max_ways