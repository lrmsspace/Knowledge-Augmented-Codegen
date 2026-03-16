# Source: https://leetcode.com/problems/minimum-operations-to-make-the-array-alternating/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 0-indexed array nums consisting of n positive integers.
#
# The array nums is called alternating if:
#
#
# 	nums[i - 2] == nums[i], where 2 <= i <= n - 1.
# 	nums[i - 1] != nums[i], where 1 <= i <= n - 1.
#
#
# In one operation, you can choose an index i and change nums[i] into any positive integer.
#
# Return the minimum number of operations required to make the array alternating.
#
# Example:
# Input: nums = [3,1,3,2,4,3]
# Output: 3
# Explanation:
# One way to make the array alternating is by converting it to [3,1,3,1,3,1].
# The number of operations required in this case is 3.
# It can be proven that it is not possible to make the array alternating in less than 3 operations.
#
# Constraints:
# 1 <= nums.length <= 105
# 	1 <= nums[i] <= 105
#

class Solution(object):
    def minimumOperations(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        from collections import Counter

        n = len(nums)
        if n == 1:
            return 0

        even_counts = Counter()
        odd_counts = Counter()

        for i in range(n):
            if i % 2 == 0:
                even_counts[nums[i]] += 1
            else:
                odd_counts[nums[i]] += 1

        even_common = even_counts.most_common(2)
        odd_common = odd_counts.most_common(2)

        even_most, even_second = (even_common[0][0], even_common[0][1]) if len(even_common) > 0 else (None, 0), (even_common[1][0], even_common[1][1]) if len(even_common) > 1 else (None, 0)
        odd_most, odd_second = (odd_common[0][0], odd_common[0][1]) if len(odd_common) > 0 else (None, 0), (odd_common[1][0], odd_common[1][1]) if len(odd_common) > 1 else (None, 0)

        if even_most != odd_most:
            return n - (even_second + odd_second)
        else:
            return min(n - (even_second + odd_common[1][1]), n - (even_common[1][1] + odd_second))