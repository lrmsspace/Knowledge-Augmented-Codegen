# Source: https://leetcode.com/problems/count-largest-group/   |   Difficulty: Easy
#
# Problem Description:
# You are given an integer n.
#
# We need to group the numbers from 1 to n according to the sum of its digits. For example, the numbers 14 and 5 belong to the same group, whereas 13 and 3 belong to different groups.
#
# Return the number of groups that have the largest size, i.e. the maximum number of elements.
#
# Example:
# Input: n = 13
# Output: 4
# Explanation: There are 9 groups in total, they are grouped according sum of its digits of numbers from 1 to 13:
# [1,10], [2,11], [3,12], [4,13], [5], [6], [7], [8], [9].
# There are 4 groups with largest size.
#
# Constraints:
# 1 <= n <= 104
#

class Solution(object):
    def countLargestGroup(self, n):
        """
        :type n: int
        :rtype: int
        """
        from collections import defaultdict

        digit_sum_groups = defaultdict(int)

        for num in range(1, n + 1):
            digit_sum = sum(int(digit) for digit in str(num))
            digit_sum_groups[digit_sum] += 1

        max_group_size = max(digit_sum_groups.values())
        largest_group_count = sum(1 for size in digit_sum_groups.values() if size == max_group_size)

        return largest_group_count