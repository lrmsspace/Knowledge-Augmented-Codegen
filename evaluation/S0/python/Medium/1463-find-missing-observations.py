# Source: https://leetcode.com/problems/find-missing-observations/   |   Difficulty: Medium
#
# Problem Description:
# You have observations of n + m 6-sided dice rolls with each face numbered from 1 to 6. n of the observations went missing, and you only have the observations of m rolls. Fortunately, you have also calculated the average value of the n + m rolls.
#
# You are given an integer array rolls of length m where rolls[i] is the value of the ith observation. You are also given the two integers mean and n.
#
# Return an array of length n containing the missing observations such that the average value of the n + m rolls is exactly mean. If there are multiple valid answers, return any of them. If no such array exists, return an empty array.
#
# The average value of a set of k numbers is the sum of the numbers divided by k.
#
# Note that mean is an integer, so the sum of the n + m rolls should be divisible by n + m.
#
# Example:
# Input: rolls = [3,2,4,3], mean = 4, n = 2
# Output: [6,6]
# Explanation: The mean of all n + m rolls is (3 + 2 + 4 + 3 + 6 + 6) / 6 = 4.
#
# Constraints:
# m == rolls.length
# 	1 <= n, m <= 105
# 	1 <= rolls[i], mean <= 6
#

class Solution(object):
    def missingRolls(self, rolls, mean, n):
        """
        :type rolls: List[int]
        :type mean: int
        :type n: int
        :rtype: List[int]
        """
        m = len(rolls)
        total_sum = mean * (n + m)
        current_sum = sum(rolls)
        missing_sum = total_sum - current_sum
        
        if missing_sum < n or missing_sum > 6 * n:
            return []
        
        base_value = missing_sum // n
        remainder = missing_sum % n
        
        result = [base_value] * n
        
        for i in range(remainder):
            result[i] += 1
            
        return result