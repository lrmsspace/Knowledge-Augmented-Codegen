# Source: https://leetcode.com/problems/repeated-dna-sequences/   |   Difficulty: Medium
#
# Problem Description:
# The DNA sequence is composed of a series of nucleotides abbreviated as 'A', 'C', 'G', and 'T'.
#
#
# 	For example, "ACGAATTCCG" is a DNA sequence.
#
#
# When studying DNA, it is useful to identify repeated sequences within the DNA.
#
# Given a string s that represents a DNA sequence, return all the 10-letter-long sequences (substrings) that occur more than once in a DNA molecule. You may return the answer in any order.
#
# Example:
# Input: s = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT"
# Output: ["AAAAACCCCC","CCCCCAAAAA"]
#
# Constraints:
# 1 <= s.length <= 105
# 	s[i] is either 'A', 'C', 'G', or 'T'.
#

class Solution(object):
    def findRepeatedDnaSequences(self, s):
        """
        :type s: str
        :rtype: List[str]
        """
        seen = set()
        repeated = set()
        result = []

        for i in range(len(s) - 9):
            substring = s[i:i + 10]
            if substring in seen:
                if substring not in repeated:
                    result.append(substring)
                    repeated.add(substring)
            else:
                seen.add(substring)

        return result