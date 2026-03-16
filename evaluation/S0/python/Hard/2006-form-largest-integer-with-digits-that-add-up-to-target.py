# Source: https://leetcode.com/problems/form-largest-integer-with-digits-that-add-up-to-target/   |   Difficulty: Hard
#
# Problem Description:
# Given an array of integers cost and an integer target, return the maximum integer you can paint under the following rules:
#
#
# 	The cost of painting a digit (i + 1) is given by cost[i] (0-indexed).
# 	The total cost used must be equal to target.
# 	The integer does not have 0 digits.
#
#
# Since the answer may be very large, return it as a string. If there is no way to paint any integer given the condition, return "0".
#
# Example:
# Input: cost = [4,3,2,5,6,7,2,5,5], target = 9
# Output: "7772"
# Explanation: The cost to paint the digit '7' is 2, and the digit '2' is 3. Then cost("7772") = 2*3+ 3*1 = 9. You could also paint "977", but "7772" is the largest number.
# Digit    cost
#   1  ->   4
#   2  ->   3
#   3  ->   2
#   4  ->   5
#   5  ->   6
#   6  ->   7
#   7  ->   2
#   8  ->   5
#   9  ->   5
#
# Constraints:
# cost.length == 9
# 	1 <= cost[i], target <= 5000
#

class Solution(object):
    def largestNumber(self, cost, target):
        """
        :type cost: List[int]
        :type target: int
        :rtype: str
        """
        dp = [''] + [None] * target

        for t in range(1, target + 1):
            for d in range(9):
                c = cost[d]
                if t >= c and dp[t - c] is not None:
                    candidate = dp[t - c] + str(d + 1)
                    if dp[t] is None or len(candidate) > len(dp[t]) or (len(candidate) == len(dp[t]) and candidate > dp[t]):
                        dp[t] = candidate

        return dp[target] if dp[target] is not None else '0'