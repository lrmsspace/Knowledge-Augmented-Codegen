# Source: https://leetcode.com/problems/pizza-with-3n-slices/   |   Difficulty: Hard
#
# Problem Description:
# There is a pizza with 3n slices of varying size, you and your friends will take slices of pizza as follows:
#
#
# 	You will pick any pizza slice.
# 	Your friend Alice will pick the next slice in the anti-clockwise direction of your pick.
# 	Your friend Bob will pick the next slice in the clockwise direction of your pick.
# 	Repeat until there are no more slices of pizzas.
#
#
# Given an integer array slices that represent the sizes of the pizza slices in a clockwise direction, return the maximum possible sum of slice sizes that you can pick.
#
# Example:
# Input: slices = [1,2,3,4,5,6]
# Output: 10
# Explanation: Pick pizza slice of size 4, Alice and Bob will pick slices with size 3 and 5 respectively. Then Pick slices with size 6, finally Alice and Bob will pick slice of size 2 and 1 respectively. Total = 4 + 6.
#
# Constraints:
# 3 * n == slices.length
# 	1 <= slices.length <= 500
# 	1 <= slices[i] <= 1000
#

class Solution(object):
    def maxSizeSlices(self, slices):
        """
        :type slices: List[int]
        :rtype: int
        """
        def calculate(slices):
            n = len(slices)
            pick = n // 3
            dp = [[0] * (pick + 1) for _ in range(n + 1)]

            for i in range(1, n + 1):
                for j in range(1, min(i // 2 + 1, pick + 1)):
                    dp[i][j] = max(dp[i - 1][j], dp[i - 2][j - 1] + slices[i - 1])

            return dp[n][pick]

        return max(calculate(slices[1:]), calculate(slices[:-1]))