# Source: https://leetcode.com/problems/closest-divisors/   |   Difficulty: Medium
#
# Problem Description:
# Given an integer num, find the closest two integers in absolute difference whose product equals num + 1 or num + 2.
#
# Return the two integers in any order.
#
# Example:
# Input: num = 8
# Output: [3,3]
# Explanation: For num + 1 = 9, the closest divisors are 3 & 3, for num + 2 = 10, the closest divisors are 2 & 5, hence 3 & 3 is chosen.
#
# Constraints:
# 1 <= num <= 10^9
#

class Solution(object):
    def closestDivisors(self, num):
        """
        :type num: int
        :rtype: List[int]
        """
        def find_closest_divisors(n):
            import math
            root = int(math.sqrt(n))
            for i in range(root, 0, -1):
                if n % i == 0:
                    return [i, n // i]
            return [1, n]

        div1 = find_closest_divisors(num + 1)
        div2 = find_closest_divisors(num + 2)

        if abs(div1[0] - div1[1]) <= abs(div2[0] - div2[1]):
            return div1
        else:
            return div2