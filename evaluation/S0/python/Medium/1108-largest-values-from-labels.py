# Source: https://leetcode.com/problems/largest-values-from-labels/   |   Difficulty: Medium
#
# Problem Description:
# You are given n item's value and label as two integer arrays values and labels. You are also given two integers numWanted and useLimit.
#
# Your task is to find a subset of items with the maximum sum of their values such that:
#
#
# 	The number of items is at most numWanted.
# 	The number of items with the same label is at most useLimit.
#
#
# Return the maximum sum.
#
# Example:
# Input: values = [5,4,3,2,1], labels = [1,1,2,2,3], numWanted = 3, useLimit = 1
#
# Output: 9
#
# Explanation:
#
# The subset chosen is the first, third, and fifth items with the sum of values 5 + 3 + 1.
#
# Constraints:
# n == values.length == labels.length
# 	1 <= n <= 2 * 104
# 	0 <= values[i], labels[i] <= 2 * 104
# 	1 <= numWanted, useLimit <= n
#

class Solution(object):
    def largestValsFromLabels(self, values, labels, numWanted, useLimit):
        """
        :type values: List[int]
        :type labels: List[int]
        :type numWanted: int
        :type useLimit: int
        :rtype: int
        """
        items = sorted(zip(values, labels), key=lambda x: -x[0])
        label_count = {}
        total_value = 0
        items_used = 0

        for value, label in items:
            if items_used >= numWanted:
                break
            if label_count.get(label, 0) < useLimit:
                total_value += value
                label_count[label] = label_count.get(label, 0) + 1
                items_used += 1

        return total_value