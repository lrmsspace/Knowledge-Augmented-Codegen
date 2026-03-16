# Source: https://leetcode.com/problems/change-minimum-characters-to-satisfy-one-of-three-conditions/   |   Difficulty: Medium
#
# Problem Description:
# You are given two strings a and b that consist of lowercase letters. In one operation, you can change any character in a or b to any lowercase letter.
#
# Your goal is to satisfy one of the following three conditions:
#
#
# 	Every letter in a is strictly less than every letter in b in the alphabet.
# 	Every letter in b is strictly less than every letter in a in the alphabet.
# 	Both a and b consist of only one distinct letter.
#
#
# Return the minimum number of operations needed to achieve your goal.
#
# Example:
# Input: a = "aba", b = "caa"
# Output: 2
# Explanation: Consider the best way to make each condition true:
# 1) Change b to "ccc" in 2 operations, then every letter in a is less than every letter in b.
# 2) Change a to "bbb" and b to "aaa" in 3 operations, then every letter in b is less than every letter in a.
# 3) Change a to "aaa" and b to "aaa" in 2 operations, then a and b consist of one distinct letter.
# The best way was done in 2 operations (either condition 1 or condition 3).
#
# Constraints:
# 1 <= a.length, b.length <= 105
# 	a and b consist only of lowercase letters.
#

class Solution(object):
    def minCharacters(self, a, b):
        """
        :type a: str
        :type b: str
        :rtype: int
        """
        countA = [0] * 26
        countB = [0] * 26
        
        for char in a:
            countA[ord(char) - ord('a')] += 1
            
        for char in b:
            countB[ord(char) - ord('a')] += 1
            
        prefixA = [0] * 26
        prefixB = [0] * 26
        
        prefixA[0] = countA[0]
        prefixB[0] = countB[0]
        
        for i in range(1, 26):
            prefixA[i] = prefixA[i - 1] + countA[i]
            prefixB[i] = prefixB[i - 1] + countB[i]
        
        totalA = len(a)
        totalB = len(b)
        
        min_operations = float('inf')
        
        # Condition 1: Every letter in a is strictly less than every letter in b
        for i in range(25):
            operations = (totalA - prefixA[i]) + prefixB[i]
            min_operations = min(min_operations, operations)
        
        # Condition 2: Every letter in b is strictly less than every letter in a
        for i in range(25):
            operations = (totalB - prefixB[i]) + prefixA[i]
            min_operations = min(min_operations, operations)
        
        # Condition 3: Both a and b consist of only one distinct letter
        for i in range(26):
            operations = (totalA - countA[i]) + (totalB - countB[i])
            min_operations = min(min_operations, operations)
        
        return min_operations