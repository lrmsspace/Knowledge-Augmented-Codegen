# Source: https://leetcode.com/problems/minimum-index-sum-of-two-lists/   |   Difficulty: Easy
#
# Problem Description:
# Given two arrays of strings list1 and list2, find the common strings with the least index sum.
#
# A common string is a string that appeared in both list1 and list2.
#
# A common string with the least index sum is a common string such that if it appeared at list1[i] and list2[j] then i + j should be the minimum value among all the other common strings.
#
# Return all the common strings with the least index sum. Return the answer in any order.
#
# Example:
# Input: list1 = ["Shogun","Tapioca Express","Burger King","KFC"], list2 = ["Piatti","The Grill at Torrey Pines","Hungry Hunter Steakhouse","Shogun"]
# Output: ["Shogun"]
# Explanation: The only common string is "Shogun".
#
# Constraints:
# 1 <= list1.length, list2.length <= 1000
# 	1 <= list1[i].length, list2[i].length <= 30
# 	list1[i] and list2[i] consist of spaces ' ' and English letters.
# 	All the strings of list1 are unique.
# 	All the strings of list2 are unique.
# 	There is at least a common string between list1 and list2.
#

class Solution(object):
    def findRestaurant(self, list1, list2):
        """
        :type list1: List[str]
        :type list2: List[str]
        :rtype: List[str]
        """
        index_map = {restaurant: i for i, restaurant in enumerate(list1)}
        min_sum = float('inf')
        result = []

        for j, restaurant in enumerate(list2):
            if restaurant in index_map:
                index_sum = index_map[restaurant] + j
                if index_sum < min_sum:
                    min_sum = index_sum
                    result = [restaurant]
                elif index_sum == min_sum:
                    result.append(restaurant)

        return result