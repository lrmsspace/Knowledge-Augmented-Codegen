# Source: https://leetcode.com/problems/count-stepping-numbers-in-range/   |   Difficulty: Hard
#
# Problem Description:
# Given two positive integers low and high represented as strings, find the count of stepping numbers in the inclusive range [low, high].
#
# A stepping number is an integer such that all of its adjacent digits have an absolute difference of exactly 1.
#
# Return an integer denoting the count of stepping numbers in the inclusive range [low, high]. 
#
# Since the answer may be very large, return it modulo 109 + 7.
#
# Note: A stepping number should not have a leading zero.
#
# Example:
# Input: low = "1", high = "11"
# Output: 10
# Explanation: The stepping numbers in the range [1,11] are 1, 2, 3, 4, 5, 6, 7, 8, 9 and 10. There are a total of 10 stepping numbers in the range. Hence, the output is 10.
#
# Constraints:
# 1 <= int(low) <= int(high) < 10100
# 	1 <= low.length, high.length <= 100
# 	low and high consist of only digits.
# 	low and high don't have any leading zeros.
#

class Solution(object):
    def countSteppingNumbers(self, low, high):
        """
        :type low: str
        :type high: str
        :rtype: int
        """
        MOD = 10**9 + 7
        
        def bfs(n):
            queue = []
            for i in range(1, 10):
                queue.append(i)
            count = 0
            
            while queue:
                step_num = queue.pop(0)
                
                if low <= str(step_num) <= high:
                    count = (count + 1) % MOD
                
                if step_num == 0 or step_num > n:
                    continue
                
                last_digit = step_num % 10
                
                step_num_a = step_num * 10 + (last_digit - 1)
                step_num_b = step_num * 10 + (last_digit + 1)
                
                if last_digit == 0:
                    queue.append(step_num_b)
                elif last_digit == 9:
                    queue.append(step_num_a)
                else:
                    queue.append(step_num_a)
                    queue.append(step_num_b)
            
            return count
        
        return bfs(int(high))