# Source: https://leetcode.com/problems/maximum-split-of-positive-even-integers/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer finalSum. Split it into a sum of a maximum number of unique positive even integers.
#
#
# 	For example, given finalSum = 12, the following splits are valid (unique positive even integers summing up to finalSum): (12), (2 + 10), (2 + 4 + 6), and (4 + 8). Among them, (2 + 4 + 6) contains the maximum number of integers. Note that finalSum cannot be split into (2 + 2 + 4 + 4) as all the numbers should be unique.
#
#
# Return a list of integers that represent a valid split containing a maximum number of integers. If no valid split exists for finalSum, return an empty list. You may return the integers in any order.
#
# Example:
# Input: finalSum = 12
# Output: [2,4,6]
# Explanation: The following are valid splits: (12), (2 + 10), (2 + 4 + 6), and (4 + 8).
# (2 + 4 + 6) has the maximum number of integers, which is 3. Thus, we return [2,4,6].
# Note that [2,6,4], [6,2,4], etc. are also accepted.
#
# Constraints:
# 1 <= finalSum <= 1010
#

class Solution(object):
    def maximumEvenSplit(self, finalSum):
        """
        :type finalSum: int
        :rtype: List[int]
        """
        if finalSum % 2 != 0:
            return []
        
        result = []
        current_even = 2
        
        while finalSum > 0:
            if finalSum - current_even >= 0:
                result.append(current_even)
                finalSum -= current_even
                current_even += 2
            else:
                result[-1] += finalSum
                finalSum = 0
        
        return result