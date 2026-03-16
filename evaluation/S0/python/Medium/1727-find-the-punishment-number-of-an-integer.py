# Source: https://leetcode.com/problems/find-the-punishment-number-of-an-integer/   |   Difficulty: Medium
#
# Problem Description:
# Given a positive integer n, return the punishment number of n.
#
# The punishment number of n is defined as the sum of the squares of all integers i such that:
#
#
# 	1 <= i <= n
# 	The decimal representation of i * i can be partitioned into contiguous substrings such that the sum of the integer values of these substrings equals i.
#
# Example:
# Input: n = 10
# Output: 182
# Explanation: There are exactly 3 integers i in the range [1, 10] that satisfy the conditions in the statement:
# - 1 since 1 * 1 = 1
# - 9 since 9 * 9 = 81 and 81 can be partitioned into 8 and 1 with a sum equal to 8 + 1 == 9.
# - 10 since 10 * 10 = 100 and 100 can be partitioned into 10 and 0 with a sum equal to 10 + 0 == 10.
# Hence, the punishment number of 10 is 1 + 81 + 100 = 182
#
# Constraints:
# 1 <= n <= 1000
#

class Solution(object):
    def punishmentNumber(self, n):
        """
        :type n: int
        :rtype: int
        """
        def dfs(s, target, start):
            if start == len(s) and target == 0:
                return True
            for end in range(start + 1, len(s) + 1):
                num = int(s[start:end])
                if num > target:
                    break
                if dfs(s, target - num, end):
                    return True
            return False

        total = 0
        for i in range(1, n + 1):
            square_str = str(i * i)
            if dfs(square_str, i, 0):
                total += i * i
        return total