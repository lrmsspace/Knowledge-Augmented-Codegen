# Source: https://leetcode.com/problems/maximum-gap/   |   Difficulty: Hard
#
# Problem Description:
# Given an integer array nums, return the maximum difference between two successive elements in its sorted form. If the array contains less than two elements, return 0.
#
# You must write an algorithm that runs in linear time and uses linear extra space.
#
# Example:
# Input: nums = [3,6,9,1]
# Output: 3
# Explanation: The sorted form of the array is [1,3,6,9], either (3,6) or (6,9) has the maximum difference 3.
#
# Constraints:
# 1 <= nums.length <= 105
# 	0 <= nums[i] <= 109
#

class Solution(object):
    def maximumGap(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        if len(nums) < 2:
            return 0

        min_num = min(nums)
        max_num = max(nums)

        if min_num == max_num:
            return 0

        n = len(nums)
        bucket_size = max(1, (max_num - min_num) // (n - 1))
        bucket_count = (max_num - min_num) // bucket_size + 1

        buckets = [[None, None] for _ in range(bucket_count)]

        for num in nums:
            index = (num - min_num) // bucket_size
            if buckets[index][0] is None:
                buckets[index][0] = num
                buckets[index][1] = num
            else:
                buckets[index][0] = min(buckets[index][0], num)
                buckets[index][1] = max(buckets[index][1], num)

        max_gap = 0
        previous_max = None

        for b in buckets:
            if b[0] is not None:
                if previous_max is not None:
                    max_gap = max(max_gap, b[0] - previous_max)
                previous_max = b[1]

        return max_gap