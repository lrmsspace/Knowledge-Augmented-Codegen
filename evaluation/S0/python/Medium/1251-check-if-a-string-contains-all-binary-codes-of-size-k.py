# Source: https://leetcode.com/problems/check-if-a-string-contains-all-binary-codes-of-size-k/   |   Difficulty: Medium
#
# Problem Description:
# Given a binary string s and an integer k, return true if every binary code of length k is a substring of s. Otherwise, return false.
#
# Example:
# Input: s = "00110110", k = 2
# Output: true
# Explanation: The binary codes of length 2 are "00", "01", "10" and "11". They can be all found as substrings at indices 0, 1, 3 and 2 respectively.
#
# Constraints:
# 1 <= s.length <= 5 * 105
# 	s[i] is either '0' or '1'.
# 	1 <= k <= 20
#

class Solution(object):
    def hasAllCodes(self, s, k):
        """
        :type s: str
        :type k: int
        :rtype: bool
        """
        needed = 1 << k
        got = set()

        for i in range(len(s) - k + 1):
            substring = s[i:i + k]
            num = int(substring, 2)
            if num not in got:
                got.add(num)
                needed -= 1
                if needed == 0:
                    return True

        return False