# Source: https://leetcode.com/problems/sum-of-beauty-of-all-substrings/   |   Difficulty: Medium
#
# Problem Description:
# The beauty of a string is the difference in frequencies between the most frequent and least frequent characters.
#
#
# 	For example, the beauty of "abaacc" is 3 - 1 = 2.
#
#
# Given a string s, return the sum of beauty of all of its substrings.
#
# Example:
# Input: s = "aabcb"
# Output: 5
# Explanation: The substrings with non-zero beauty are ["aab","aabc","aabcb","abcb","bcb"], each with beauty equal to 1.
#
# Constraints:
# 1 <= s.length <= 500
# 	s consists of only lowercase English letters.
#

class Solution(object):
    def beautySum(self, s):
        """
        :type s: str
        :rtype: int
        """
        total_beauty = 0
        n = len(s)
        
        for i in range(n):
            freq = [0] * 26  # Frequency array for 'a' to 'z'
            for j in range(i, n):
                freq[ord(s[j]) - ord('a')] += 1
                
                max_freq = max(freq)
                min_freq = min([f for f in freq if f > 0])
                
                total_beauty += (max_freq - min_freq)
        
        return total_beauty