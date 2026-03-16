# Source: https://leetcode.com/problems/calculate-delayed-arrival-time/   |   Difficulty: Easy
#
# Problem Description:
# You are given a positive integer arrivalTime denoting the arrival time of a train in hours, and another positive integer delayedTime denoting the amount of delay in hours.
#
# Return the time when the train will arrive at the station.
#
# Note that the time in this problem is in 24-hours format.
#
# Example:
# Input: arrivalTime = 15, delayedTime = 5 
# Output: 20 
# Explanation: Arrival time of the train was 15:00 hours. It is delayed by 5 hours. Now it will reach at 15+5 = 20 (20:00 hours).
#
# Constraints:
# 1 <= arrivaltime < 24
# 	1 <= delayedTime <= 24
#
# Helpful references (internal KB):
# - N/A
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def findDelayedArrivalTime(self, arrivalTime, delayedTime):
        """
        :type arrivalTime: int
        :type delayedTime: int
        :rtype: int
        """
        # 计算总时间
        total_time = arrivalTime + delayedTime
        
        # 使用模运算处理超过24小时的情况
        delayed_arrival_time = total_time % 24
        
        return delayed_arrival_time