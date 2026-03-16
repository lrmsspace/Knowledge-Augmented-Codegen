# Source: https://leetcode.com/problems/partition-array-into-two-arrays-to-minimize-sum-difference/   |   Difficulty: Hard
#
# Problem Description:
# You are given an integer array nums of 2 * n integers. You need to partition nums into two arrays of length n to minimize the absolute difference of the sums of the arrays. To partition nums, put each element of nums into one of the two arrays.
#
# Return the minimum possible absolute difference.
#
# Example:
# Input: nums = [3,9,7,3]
# Output: 2
# Explanation: One optimal partition is: [3,9] and [7,3].
# The absolute difference between the sums of the arrays is abs((3 + 9) - (7 + 3)) = 2.
#
# Constraints:
# 1 <= n <= 15
# 	nums.length == 2 * n
# 	-107 <= nums[i] <= 107
#

class Solution(object):
    def minimumDifference(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        from itertools import combinations
        n = len(nums) // 2
        total_sum = sum(nums)
        left_nums = nums[:n]
        right_nums = nums[n:]

        left_sums = {i: [] for i in range(n + 1)}
        right_sums = {i: [] for i in range(n + 1)}

        for i in range(n + 1):
            for comb in combinations(left_nums, i):
                left_sums[i].append(sum(comb))
            for comb in combinations(right_nums, i):
                right_sums[i].append(sum(comb))

        for i in range(n + 1):
            left_sums[i].sort()
            right_sums[i].sort()

        min_diff = float('inf')

        for i in range(n + 1):
            j = n - i
            left_part = left_sums[i]
            right_part = right_sums[j]

            for left_sum in left_part:
                target = (total_sum // 2) - left_sum
                l, r = 0, len(right_part) - 1

                while l <= r:
                    mid = (l + r) // 2
                    current_sum = left_sum + right_part[mid]
                    current_diff = abs(total_sum - 2 * current_sum)

                    min_diff = min(min_diff, current_diff)

                    if current_sum < target:
                        l = mid + 1
                    else:
                        r = mid - 1

        return min_diff