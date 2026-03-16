# Source: https://leetcode.com/problems/numbers-with-same-consecutive-differences/   |   Difficulty: Medium
#
# Problem Description:
# Given two integers n and k, return an array of all the integers of length n where the difference between every two consecutive digits is k. You may return the answer in any order.
#
# Note that the integers should not have leading zeros. Integers as 02 and 043 are not allowed.
#
# Example:
# Input: n = 3, k = 7
# Output: [181,292,707,818,929]
# Explanation: Note that 070 is not a valid number, because it has leading zeroes.
#
# Constraints:
# 2 <= n <= 9
# 	0 <= k <= 9
#

class Solution(object):
    def numsSameConsecDiff(self, n, k):
        """
        :type n: int
        :type k: int
        :rtype: List[int]
        """
        if n == 1:
            return [i for i in range(10)]
        
        results = []
        
        def backtrack(num, length):
            if length == n:
                results.append(num)
                return
            
            last_digit = num % 10
            
            next_digits = set()
            if last_digit + k <= 9:
                next_digits.add(last_digit + k)
            if last_digit - k >= 0:
                next_digits.add(last_digit - k)
            
            for next_digit in next_digits:
                new_num = num * 10 + next_digit
                backtrack(new_num, length + 1)
        
        for first_digit in range(1, 10):
            backtrack(first_digit, 1)
        
        return results