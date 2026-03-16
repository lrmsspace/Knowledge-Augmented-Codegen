# Source: https://leetcode.com/problems/maximum-number-of-operations-with-the-same-score-i/   |   Difficulty: Easy
#
# Problem Description:
# You are given an array of integers nums. Consider the following operation:
#
#
# 	Delete the first two elements nums and define the score of the operation as the sum of these two elements.
#
#
# You can perform this operation until nums contains fewer than two elements. Additionally, the same score must be achieved in all operations.
#
# Return the maximum number of operations you can perform.
#
# Example:
# Input: nums = [3,2,1,4,5]
#
# Output: 2
#
# Explanation:
#
#
# 	We can perform the first operation with the score 3 + 2 = 5. After this operation, nums = [1,4,5].
# 	We can perform the second operation as its score is 4 + 1 = 5, the same as the previous operation. After this operation, nums = [5].
# 	As there are fewer than two elements, we can't perform more operations.
#
# Constraints:
# 2 <= nums.length <= 100
# 	1 <= nums[i] <= 1000
#

class Solution(object):
    def maxOperations(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        from collections import Counter
        count = Counter(nums)
        max_ops = 0

        for target_sum in range(2, 2001):
            current_ops = 0
            left, right = 1, target_sum - 1

            while left <= right:
                if left + right == target_sum:
                    if left == right:
                        current_ops += count[left] // 2
                    else:
                        current_ops += min(count[left], count[right])
                left += 1
                right -= 1

            max_ops = max(max_ops, current_ops)

        return max_ops