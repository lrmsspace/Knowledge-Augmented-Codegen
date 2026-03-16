# Source: https://leetcode.com/problems/license-key-formatting/   |   Difficulty: Easy
#
# Problem Description:
# You are given a license key represented as a string s that consists of only alphanumeric characters and dashes. The string is separated into n + 1 groups by n dashes. You are also given an integer k.
#
# We want to reformat the string s such that each group contains exactly k characters, except for the first group, which could be shorter than k but still must contain at least one character. Furthermore, there must be a dash inserted between two groups, and you should convert all lowercase letters to uppercase.
#
# Return the reformatted license key.
#
# Example:
# Input: s = "5F3Z-2e-9-w", k = 4
# Output: "5F3Z-2E9W"
# Explanation: The string s has been split into two parts, each part has 4 characters.
# Note that the two extra dashes are not needed and can be removed.
#
# Constraints:
# 1 <= s.length <= 105
# 	s consists of English letters, digits, and dashes '-'.
# 	1 <= k <= 104
#

class Solution(object):
    def licenseKeyFormatting(self, s, k):
        """
        :type s: str
        :type k: int
        :rtype: str
        """
        # 移除所有的破折号并转换为大写
        s = s.replace('-', '').upper()
        
        # 计算第一个组的长度
        first_group_length = len(s) % k
        groups = []
        
        # 如果第一个组有字符，添加它
        if first_group_length > 0:
            groups.append(s[:first_group_length])
        
        # 处理剩余的字符，每k个字符一组
        for i in range(first_group_length, len(s), k):
            groups.append(s[i:i+k])
        
        # 使用破折号连接所有组
        return '-'.join(groups)