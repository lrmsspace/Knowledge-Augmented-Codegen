# Source: https://leetcode.com/problems/maximum-swap/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer num. You can swap two digits at most once to get the maximum valued number.
#
# Return the maximum valued number you can get.
#
# Example:
# Input: num = 2736
# Output: 7236
# Explanation: Swap the number 2 and the number 7.
#
# Constraints:
# 0 <= num <= 108
#

class Solution(object):
    def maximumSwap(self, num):
        """
        :type num: int
        :rtype: int
        """
        num_list = list(str(num))
        last = {int(x): i for i, x in enumerate(num_list)}
        
        for i, x in enumerate(num_list):
            for d in range(9, int(x), -1):
                if last.get(d, -1) > i:
                    num_list[i], num_list[last[d]] = num_list[last[d]], num_list[i]
                    return int(''.join(num_list))
        
        return num