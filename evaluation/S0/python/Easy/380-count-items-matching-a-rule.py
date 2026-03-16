# Source: https://leetcode.com/problems/count-items-matching-a-rule/   |   Difficulty: Easy
#
# Problem Description:
# You are given an array items, where each items[i] = [typei, colori, namei] describes the type, color, and name of the ith item. You are also given a rule represented by two strings, ruleKey and ruleValue.
#
# The ith item is said to match the rule if one of the following is true:
#
#
# 	ruleKey == "type" and ruleValue == typei.
# 	ruleKey == "color" and ruleValue == colori.
# 	ruleKey == "name" and ruleValue == namei.
#
#
# Return the number of items that match the given rule.
#
# Example:
# Input: items = [["phone","blue","pixel"],["computer","silver","lenovo"],["phone","gold","iphone"]], ruleKey = "color", ruleValue = "silver"
# Output: 1
# Explanation: There is only one item matching the given rule, which is ["computer","silver","lenovo"].
#
# Constraints:
# 1 <= items.length <= 104
# 	1 <= typei.length, colori.length, namei.length, ruleValue.length <= 10
# 	ruleKey is equal to either "type", "color", or "name".
# 	All strings consist only of lowercase letters.
#

class Solution(object):
    def countMatches(self, items, ruleKey, ruleValue):
        """
        :type items: List[List[str]]
        :type ruleKey: str
        :type ruleValue: str
        :rtype: int
        """
        key_index = {"type": 0, "color": 1, "name": 2}
        index = key_index[ruleKey]
        count = 0
        
        for item in items:
            if item[index] == ruleValue:
                count += 1
                
        return count