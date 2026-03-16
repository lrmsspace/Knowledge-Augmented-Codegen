# Source: https://leetcode.com/problems/latest-time-by-replacing-hidden-digits/   |   Difficulty: Easy
#
# Problem Description:
# You are given a string time in the form of  hh:mm, where some of the digits in the string are hidden (represented by ?).
#
# The valid times are those inclusively between 00:00 and 23:59.
#
# Return the latest valid time you can get from time by replacing the hidden digits.
#
# Example:
# Input: time = "2?:?0"
# Output: "23:50"
# Explanation: The latest hour beginning with the digit '2' is 23 and the latest minute ending with the digit '0' is 50.
#
# Constraints:
# time is in the format hh:mm.
# 	It is guaranteed that you can produce a valid time from the given string.
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
    def maximumTime(self, time):
        """
        :type time: str
        :rtype: str
        """
        time_list = list(time)
        
        # 处理小时的十位
        if time_list[0] == '?':
            if time_list[1] != '?' and time_list[1] > '3':
                time_list[0] = '1'
            else:
                time_list[0] = '2'
        
        # 处理小时的个位
        if time_list[1] == '?':
            if time_list[0] == '2':
                time_list[1] = '3'
            else:
                time_list[1] = '9'
        
        # 处理分钟的十位
        if time_list[3] == '?':
            time_list[3] = '5'
        
        # 处理分钟的个位
        if time_list[4] == '?':
            time_list[4] = '9'
        
        return ''.join(time_list)