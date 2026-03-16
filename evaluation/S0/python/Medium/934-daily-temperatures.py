# Source: https://leetcode.com/problems/daily-temperatures/   |   Difficulty: Medium
#
# Problem Description:
# Given an array of integers temperatures represents the daily temperatures, return an array answer such that answer[i] is the number of days you have to wait after the ith day to get a warmer temperature. If there is no future day for which this is possible, keep answer[i] == 0 instead.
#
# Example:
# Input: temperatures = [73,74,75,71,69,72,76,73]
# Output: [1,1,4,2,1,1,0,0]
#
# Constraints:
# 1 <= temperatures.length <= 105
# 	30 <= temperatures[i] <= 100
#

class Solution(object):
    def dailyTemperatures(self, temperatures):
        """
        :type temperatures: List[int]
        :rtype: List[int]
        """
        n = len(temperatures)
        answer = [0] * n
        stack = []  # This will store indices of the temperatures list

        for i in range(n - 1, -1, -1):
            current_temp = temperatures[i]
            # Pop elements from the stack until we find a warmer temperature
            while stack and temperatures[stack[-1]] <= current_temp:
                stack.pop()

            if stack:
                answer[i] = stack[-1] - i  # Calculate the number of days to wait

            stack.append(i)  # Push the current index onto the stack

        return answer