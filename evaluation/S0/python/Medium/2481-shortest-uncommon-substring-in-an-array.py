# Source: https://leetcode.com/problems/shortest-uncommon-substring-in-an-array/   |   Difficulty: Medium
#
# Problem Description:
# You are given an array arr of size n consisting of non-empty strings.
#
# Find a string array answer of size n such that:
#
#
# 	answer[i] is the shortest substring of arr[i] that does not occur as a substring in any other string in arr. If multiple such substrings exist, answer[i] should be the lexicographically smallest. And if no such substring exists, answer[i] should be an empty string.
#
#
# Return the array answer.
#
# Example:
# Input: arr = ["cab","ad","bad","c"]
# Output: ["ab","","ba",""]
# Explanation: We have the following:
# - For the string "cab", the shortest substring that does not occur in any other string is either "ca" or "ab", we choose the lexicographically smaller substring, which is "ab".
# - For the string "ad", there is no substring that does not occur in any other string.
# - For the string "bad", the shortest substring that does not occur in any other string is "ba".
# - For the string "c", there is no substring that does not occur in any other string.
#
# Constraints:
# n == arr.length
# 	2 <= n <= 100
# 	1 <= arr[i].length <= 20
# 	arr[i] consists only of lowercase English letters.
#

class Solution(object):
    def shortestSubstrings(self, arr):
        """
        :type arr: List[str]
        :rtype: List[str]
        """
        def get_substrings(s):
            substrings = set()
            length = len(s)
            for l in range(1, length + 1):
                for i in range(length - l + 1):
                    substrings.add(s[i:i+l])
            return substrings

        n = len(arr)
        all_substrings = [get_substrings(s) for s in arr]
        result = []

        for i in range(n):
            min_substring = None
            for substr in all_substrings[i]:
                found_in_others = False
                for j in range(n):
                    if i != j and substr in all_substrings[j]:
                        found_in_others = True
                        break
                if not found_in_others:
                    if (min_substring is None or 
                        len(substr) < len(min_substring) or 
                        (len(substr) == len(min_substring) and substr < min_substring)):
                        min_substring = substr
            result.append(min_substring if min_substring is not None else "")
        
        return result