# Source: https://leetcode.com/problems/maximize-the-number-of-partitions-after-operations/   |   Difficulty: Hard
#
# Problem Description:
# You are given a string s and an integer k.
#
# First, you are allowed to change at most one index in s to another lowercase English letter.
#
# After that, do the following partitioning operation until s is empty:
#
#
# 	Choose the longest prefix of s containing at most k distinct characters.
# 	Delete the prefix from s and increase the number of partitions by one. The remaining characters (if any) in s maintain their initial order.
#
#
# Return an integer denoting the maximum number of resulting partitions after the operations by optimally choosing at most one index to change.
#
# Example:
# Input: s = "accca", k = 2
#
# Output: 3
#
# Explanation:
#
# The optimal way is to change s[2] to something other than a and c, for example, b. then it becomes "acbca".
#
# Then we perform the operations:
#
#
# 	The longest prefix containing at most 2 distinct characters is "ac", we remove it and s becomes "bca".
# 	Now The longest prefix containing at most 2 distinct characters is "bc", so we remove it and s becomes "a".
# 	Finally, we remove "a" and s becomes empty, so the procedure ends.
#
#
# Doing the operations, the string is divided into 3 partitions, so the answer is 3.
#
# Constraints:
# 1 <= s.length <= 104
# 	s consists only of lowercase English letters.
# 	1 <= k <= 26
#

class Solution(object):
    def maxPartitionsAfterOperations(self, s, k):
        """
        :type s: str
        :type k: int
        :rtype: int
        """
        def count_partitions(s, k):
            count = 0
            i = 0
            n = len(s)
            while i < n:
                distinct_chars = set()
                j = i
                while j < n and (len(distinct_chars) < k or s[j] in distinct_chars):
                    distinct_chars.add(s[j])
                    j += 1
                count += 1
                i = j
            return count

        max_partitions = count_partitions(s, k)

        for i in range(len(s)):
            original_char = s[i]
            for c in 'abcdefghijklmnopqrstuvwxyz':
                if c != original_char:
                    new_s = s[:i] + c + s[i+1:]
                    max_partitions = max(max_partitions, count_partitions(new_s, k))

        return max_partitions