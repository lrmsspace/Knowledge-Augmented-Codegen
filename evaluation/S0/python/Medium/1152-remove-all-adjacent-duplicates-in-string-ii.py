# Source: https://leetcode.com/problems/remove-all-adjacent-duplicates-in-string-ii/   |   Difficulty: Medium
#
# Problem Description:
# You are given a string s and an integer k, a k duplicate removal consists of choosing k adjacent and equal letters from s and removing them, causing the left and the right side of the deleted substring to concatenate together.
#
# We repeatedly make k duplicate removals on s until we no longer can.
#
# Return the final string after all such duplicate removals have been made. It is guaranteed that the answer is unique.
#
# Example:
# Input: s = "abcd", k = 2
# Output: "abcd"
# Explanation: There's nothing to delete.
#
# Constraints:
# 1 <= s.length <= 105
# 	2 <= k <= 104
# 	s only contains lowercase English letters.
#

class Solution(object):
    def removeDuplicates(self, s, k):
        """
        :type s: str
        :type k: int
        :rtype: str
        """
        stack = []  # Each element is [character, count]

        for char in s:
            if stack and stack[-1][0] == char:
                stack[-1][1] += 1
                if stack[-1][1] == k:
                    stack.pop()  # Remove the last k duplicates
            else:
                stack.append([char, 1])

        # Reconstruct the string from the stack
        result = []
        for char, count in stack:
            result.append(char * count)

        return ''.join(result)