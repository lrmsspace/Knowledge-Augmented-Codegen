# Source: https://leetcode.com/problems/restore-ip-addresses/   |   Difficulty: Medium
#
# Problem Description:
# A valid IP address consists of exactly four integers separated by single dots. Each integer is between 0 and 255 (inclusive) and cannot have leading zeros.
#
#
# 	For example, "0.1.2.201" and "192.168.1.1" are valid IP addresses, but "0.011.255.245", "192.168.1.312" and "192.168@1.1" are invalid IP addresses.
#
#
# Given a string s containing only digits, return all possible valid IP addresses that can be formed by inserting dots into s. You are not allowed to reorder or remove any digits in s. You may return the valid IP addresses in any order.
#
# Example:
# Input: s = "25525511135"
# Output: ["255.255.11.135","255.255.111.35"]
#
# Constraints:
# 1 <= s.length <= 20
# 	s consists of digits only.
#

class Solution(object):
    def restoreIpAddresses(self, s):
        """
        :type s: str
        :rtype: List[str]
        """
        def is_valid(segment):
            # Check if the segment is valid: not leading zero unless it's '0', and <= 255
            return len(segment) == 1 or (segment[0] != '0' and int(segment) <= 255)

        def backtrack(start=0, path=[]):
            # If we have 4 segments and we're at the end of the string, it's a valid IP
            if len(path) == 4:
                if start == len(s):
                    result.append('.'.join(path))
                return

            # Try segments of length 1 to 3
            for length in range(1, 4):
                if start + length <= len(s):
                    segment = s[start:start + length]
                    if is_valid(segment):
                        backtrack(start + length, path + [segment])

        result = []
        backtrack()
        return result