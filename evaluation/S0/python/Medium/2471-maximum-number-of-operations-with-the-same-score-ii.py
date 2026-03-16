# Source: https://leetcode.com/problems/maximum-number-of-operations-with-the-same-score-ii/   |   Difficulty: Medium
#
# Problem Description:
# Given an array of integers called nums, you can perform any of the following operation while nums contains at least 2 elements:
#
#
# 	Choose the first two elements of nums and delete them.
# 	Choose the last two elements of nums and delete them.
# 	Choose the first and the last elements of nums and delete them.
#
#
# The score of the operation is the sum of the deleted elements.
#
# Your task is to find the maximum number of operations that can be performed, such that all operations have the same score.
#
# Return the maximum number of operations possible that satisfy the condition mentioned above.
#
# Example:
# Input: nums = [3,2,1,2,3,4]
# Output: 3
# Explanation: We perform the following operations:
# - Delete the first two elements, with score 3 + 2 = 5, nums = [1,2,3,4].
# - Delete the first and the last elements, with score 1 + 4 = 5, nums = [2,3].
# - Delete the first and the last elements, with score 2 + 3 = 5, nums = [].
# We are unable to perform any more operations as nums is empty.
#
# Constraints:
# 2 <= nums.length <= 2000
# 	1 <= nums[i] <= 1000
#

class Solution(object):
    def maxOperations(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        from collections import Counter

        n = len(nums)
        pair_sum_count = Counter()

        # Calculate all possible pair sums and their counts
        for i in range(n):
            for j in range(i + 1, n):
                pair_sum = nums[i] + nums[j]
                pair_sum_count[pair_sum] += 1

        max_operations = 0

        # For each unique pair sum, calculate the maximum number of operations
        for target_sum, count in pair_sum_count.items():
            left, right = 0, n - 1
            operations = 0
            used = [False] * n

            while left < right:
                if used[left]:
                    left += 1
                    continue
                if used[right]:
                    right -= 1
                    continue

                current_sum = nums[left] + nums[right]

                if current_sum == target_sum:
                    operations += 1
                    used[left] = True
                    used[right] = True
                    left += 1
                    right -= 1
                elif current_sum < target_sum:
                    left += 1
                else:
                    right -= 1

            max_operations = max(max_operations, operations)

        return max_operations