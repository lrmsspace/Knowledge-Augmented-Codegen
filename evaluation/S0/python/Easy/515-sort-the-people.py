# Source: https://leetcode.com/problems/sort-the-people/   |   Difficulty: Easy
#
# Problem Description:
# You are given an array of strings names, and an array heights that consists of distinct positive integers. Both arrays are of length n.
#
# For each index i, names[i] and heights[i] denote the name and height of the ith person.
#
# Return names sorted in descending order by the people's heights.
#
# Example:
# Input: names = ["Mary","John","Emma"], heights = [180,165,170]
# Output: ["Mary","Emma","John"]
# Explanation: Mary is the tallest, followed by Emma and John.
#
# Constraints:
# n == names.length == heights.length
# 	1 <= n <= 103
# 	1 <= names[i].length <= 20
# 	1 <= heights[i] <= 105
# 	names[i] consists of lower and upper case English letters.
# 	All the values of heights are distinct.
#

class Solution(object):
    def sortPeople(self, names, heights):
        """
        :type names: List[str]
        :type heights: List[int]
        :rtype: List[str]
        """
        paired = list(zip(heights, names))
        paired.sort(reverse=True)
        sorted_names = [name for height, name in paired]
        return sorted_names