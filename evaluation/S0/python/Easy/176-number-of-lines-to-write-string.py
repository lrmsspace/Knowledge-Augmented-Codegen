# Source: https://leetcode.com/problems/number-of-lines-to-write-string/   |   Difficulty: Easy
#
# Problem Description:
# You are given a string s of lowercase English letters and an array widths denoting how many pixels wide each lowercase English letter is. Specifically, widths[0] is the width of 'a', widths[1] is the width of 'b', and so on.
#
# You are trying to write s across several lines, where each line is no longer than 100 pixels. Starting at the beginning of s, write as many letters on the first line such that the total width does not exceed 100 pixels. Then, from where you stopped in s, continue writing as many letters as you can on the second line. Continue this process until you have written all of s.
#
# Return an array result of length 2 where:
#
#
# 	result[0] is the total number of lines.
# 	result[1] is the width of the last line in pixels.
#
# Example:
# Input: widths = [10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10], s = "abcdefghijklmnopqrstuvwxyz"
# Output: [3,60]
# Explanation: You can write s as follows:
# abcdefghij  // 100 pixels wide
# klmnopqrst  // 100 pixels wide
# uvwxyz      // 60 pixels wide
# There are a total of 3 lines, and the last line is 60 pixels wide.
#
# Constraints:
# widths.length == 26
# 	2 <= widths[i] <= 10
# 	1 <= s.length <= 1000
# 	s contains only lowercase English letters.
#

class Solution(object):
    def numberOfLines(self, widths, s):
        """
        :type widths: List[int]
        :type s: str
        :rtype: List[int]
        """
        lines = 1
        current_width = 0
        
        for char in s:
            char_width = widths[ord(char) - ord('a')]
            if current_width + char_width > 100:
                lines += 1
                current_width = char_width
            else:
                current_width += char_width
        
        return [lines, current_width]