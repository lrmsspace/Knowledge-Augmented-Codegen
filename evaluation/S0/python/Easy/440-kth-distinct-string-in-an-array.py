# Source: https://leetcode.com/problems/kth-distinct-string-in-an-array/   |   Difficulty: Easy
#
# Problem Description:
# A distinct string is a string that is present only once in an array.
#
# Given an array of strings arr, and an integer k, return the kth distinct string present in arr. If there are fewer than k distinct strings, return an empty string "".
#
# Note that the strings are considered in the order in which they appear in the array.
#
# Example:
# Input: arr = ["d","b","c","b","c","a"], k = 2
# Output: "a"
# Explanation:
# The only distinct strings in arr are "d" and "a".
# "d" appears 1st, so it is the 1st distinct string.
# "a" appears 2nd, so it is the 2nd distinct string.
# Since k == 2, "a" is returned.
#
# Constraints:
# 1 <= k <= arr.length <= 1000
# 	1 <= arr[i].length <= 5
# 	arr[i] consists of lowercase English letters.
#

class Solution(object):
    def kthDistinct(self, arr, k):
        """
        :type arr: List[str]
        :type k: int
        :rtype: str
        """
        count_map = {}
        
        # Count occurrences of each string
        for s in arr:
            count_map[s] = count_map.get(s, 0) + 1
        
        # Find the kth distinct string
        distinct_count = 0
        for s in arr:
            if count_map[s] == 1:
                distinct_count += 1
                if distinct_count == k:
                    return s
        
        return ""