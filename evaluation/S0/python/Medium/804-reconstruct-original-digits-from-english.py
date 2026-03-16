# Source: https://leetcode.com/problems/reconstruct-original-digits-from-english/   |   Difficulty: Medium
#
# Problem Description:
# Given a string s containing an out-of-order English representation of digits 0-9, return the digits in ascending order.
#
# Example:
# Input: s = "owoztneoer"
# Output: "012"
#
# Constraints:
# 1 <= s.length <= 105
# 	s[i] is one of the characters ["e","g","f","i","h","o","n","s","r","u","t","w","v","x","z"].
# 	s is guaranteed to be valid.
#

class Solution(object):
    def originalDigits(self, s):
        """
        :type s: str
        :rtype: str
        """
        from collections import Counter

        count = Counter(s)
        out = {}

        # Identify digits with unique letters
        out['0'] = count['z']
        out['2'] = count['w']
        out['4'] = count['u']
        out['6'] = count['x']
        out['8'] = count['g']

        # Identify remaining digits
        out['3'] = count['h'] - out['8']
        out['5'] = count['f'] - out['4']
        out['7'] = count['s'] - out['6']
        out['1'] = count['o'] - out['0'] - out['2'] - out['4']
        out['9'] = count['i'] - out['5'] - out['6'] - out['8']

        # Construct the final output
        result = []
        for digit in sorted(out.keys()):
            result.append(digit * out[digit])

        return ''.join(result)