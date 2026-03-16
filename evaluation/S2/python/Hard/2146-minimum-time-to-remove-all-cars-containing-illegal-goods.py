# Source: https://leetcode.com/problems/minimum-time-to-remove-all-cars-containing-illegal-goods/   |   Difficulty: Hard
#
# Problem Description:
# You are given a 0-indexed binary string s which represents a sequence of train cars. s[i] = '0' denotes that the ith car does not contain illegal goods and s[i] = '1' denotes that the ith car does contain illegal goods.
#
# As the train conductor, you would like to get rid of all the cars containing illegal goods. You can do any of the following three operations any number of times:
#
#
# 	Remove a train car from the left end (i.e., remove s[0]) which takes 1 unit of time.
# 	Remove a train car from the right end (i.e., remove s[s.length - 1]) which takes 1 unit of time.
# 	Remove a train car from anywhere in the sequence which takes 2 units of time.
#
#
# Return the minimum time to remove all the cars containing illegal goods.
#
# Note that an empty sequence of cars is considered to have no cars containing illegal goods.
#
# Example:
# Input: s = "1100101"
# Output: 5
# Explanation: 
# One way to remove all the cars containing illegal goods from the sequence is to
# - remove a car from the left end 2 times. Time taken is 2 * 1 = 2.
# - remove a car from the right end. Time taken is 1.
# - remove the car containing illegal goods found in the middle. Time taken is 2.
# This obtains a total time of 2 + 1 + 2 = 5. 
#
# An alternative way is to
# - remove a car from the left end 2 times. Time taken is 2 * 1 = 2.
# - remove a car from the right end 3 times. Time taken is 3 * 1 = 3.
# This also obtains a total time of 2 + 3 = 5.
#
# 5 is the minimum time taken to remove all the cars containing illegal goods. 
# There are no other ways to remove them with less time.
#
# Constraints:
# 1 <= s.length <= 2 * 105
# 	s[i] is either '0' or '1'.
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
    def minimumTime(self, s):
        """
        :type s: str
        :rtype: int
        """
        left, right = 0, len(s) - 1
        time = 0

        while left <= right:
            if s[left] == '1' and s[right] == '1':
                time += 2
                left += 1
                right -= 1
            elif s[left] == '1':
                time += 1
                left += 1
            elif s[right] == '1':
                time += 1
                right -= 1
            else:
                left += 1
                right -= 1

        return time