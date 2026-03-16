# Source: https://leetcode.com/problems/minimum-seconds-to-equalize-a-circular-array/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 0-indexed array nums containing n integers.
#
# At each second, you perform the following operation on the array:
#
#
# 	For every index i in the range [0, n - 1], replace nums[i] with either nums[i], nums[(i - 1 + n) % n], or nums[(i + 1) % n].
#
#
# Note that all the elements get replaced simultaneously.
#
# Return the minimum number of seconds needed to make all elements in the array nums equal.
#
# Example:
# Input: nums = [1,2,1,2]
# Output: 1
# Explanation: We can equalize the array in 1 second in the following way:
# - At 1st second, replace values at each index with [nums[3],nums[1],nums[3],nums[3]]. After replacement, nums = [2,2,2,2].
# It can be proven that 1 second is the minimum amount of seconds needed for equalizing the array.
#
# Constraints:
# 1 <= n == nums.length <= 105
# 	1 <= nums[i] <= 109
#

class Solution(object):
    def minimumSeconds(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        n = len(nums)
        extended_nums = nums + nums  # Extend the array to handle circular nature
        count_map = {}
        max_distance_map = {}

        for i in range(2 * n):
            num = extended_nums[i]
            if num not in count_map:
                count_map[num] = 0
                max_distance_map[num] = 0

            if i < n:
                count_map[num] += 1

            if count_map[num] == 0:
                continue

            if i >= n:
                distance = i - (i - n)
                max_distance_map[num] = max(max_distance_map[num], distance)

            if i >= n and extended_nums[i - n] == num:
                count_map[num] -= 1

        min_seconds = float('inf')
        for num, max_distance in max_distance_map.items():
            if count_map[num] > 0:
                seconds_needed = (max_distance + 1) // 2
                min_seconds = min(min_seconds, seconds_needed)

        return min_seconds if min_seconds != float('inf') else 0