# Source: https://leetcode.com/problems/construct-the-longest-new-string/   |   Difficulty: Medium
#
# Problem Description:
# You are given three integers x, y, and z.
#
# You have x strings equal to "AA", y strings equal to "BB", and z strings equal to "AB". You want to choose some (possibly all or none) of these strings and concatenate them in some order to form a new string. This new string must not contain "AAA" or "BBB" as a substring.
#
# Return the maximum possible length of the new string.
#
# A substring is a contiguous non-empty sequence of characters within a string.
#
# Example:
# Input: x = 2, y = 5, z = 1
# Output: 12
# Explanation: We can concatenate the strings "BB", "AA", "BB", "AA", "BB", and "AB" in that order. Then, our new string is "BBAABBAABBAB". 
# That string has length 12, and we can show that it is impossible to construct a string of longer length.
#
# Constraints:
# 1 <= x, y, z <= 50
#

class Solution(object):
    def longestString(self, x, y, z):
        """
        :type x: int
        :type y: int
        :type z: int
        :rtype: int
        """
        # 使用贪心算法构建最长的新字符串
        result = []
        
        # 优先使用 "AB" 字符串
        while z > 0:
            result.append("AB")
            z -= 1
        
        # 交替使用 "AA" 和 "BB" 字符串，避免出现 "AAA" 或 "BBB"
        while x > 0 or y > 0:
            if len(result) == 0 or result[-1][-1] == 'B':
                if x > 0:
                    result.append("AA")
                    x -= 1
                elif y > 0:
                    result.append("BB")
                    y -= 1
                else:
                    break
            else:
                if y > 0:
                    result.append("BB")
                    y -= 1
                elif x > 0:
                    result.append("AA")
                    x -= 1
                else:
                    break
        
        return sum(len(s) for s in result)