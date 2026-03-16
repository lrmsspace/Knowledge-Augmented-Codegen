# Source: https://leetcode.com/problems/maximum-odd-binary-number/   |   Difficulty: Easy
#
# Problem Description:
# You are given a binary string s that contains at least one '1'.
#
# You have to rearrange the bits in such a way that the resulting binary number is the maximum odd binary number that can be created from this combination.
#
# Return a string representing the maximum odd binary number that can be created from the given combination.
#
# Note that the resulting string can have leading zeros.
#
# Example:
# Input: s = "010"
# Output: "001"
# Explanation: Because there is just one '1', it must be in the last position. So the answer is "001".
#
# Constraints:
# 1 <= s.length <= 100
# 	s consists only of '0' and '1'.
# 	s contains at least one '1'.
#

class Solution(object):
    def maximumOddBinaryNumber(self, s):
        """
        :type s: str
        :rtype: str
        """
        ones = s.count('1')
        zeros = s.count('0')
        
        # To form the maximum odd binary number, we need to place all '1's at the front
        # except for one '1' which should be at the end to ensure the number is odd.
        if ones > 0:
            result = '1' * (ones - 1) + '0' * zeros + '1'
        else:
            result = '0' * zeros  # This case won't happen as per problem constraints
        
        return result