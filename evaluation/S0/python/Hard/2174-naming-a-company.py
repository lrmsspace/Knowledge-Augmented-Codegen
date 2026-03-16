# Source: https://leetcode.com/problems/naming-a-company/   |   Difficulty: Hard
#
# Problem Description:
# You are given an array of strings ideas that represents a list of names to be used in the process of naming a company. The process of naming a company is as follows:
#
#
# 	Choose 2 distinct names from ideas, call them ideaA and ideaB.
# 	Swap the first letters of ideaA and ideaB with each other.
# 	If both of the new names are not found in the original ideas, then the name ideaA ideaB (the concatenation of ideaA and ideaB, separated by a space) is a valid company name.
# 	Otherwise, it is not a valid name.
#
#
# Return the number of distinct valid names for the company.
#
# Example:
# Input: ideas = ["coffee","donuts","time","toffee"]
# Output: 6
# Explanation: The following selections are valid:
# - ("coffee", "donuts"): The company name created is "doffee conuts".
# - ("donuts", "coffee"): The company name created is "conuts doffee".
# - ("donuts", "time"): The company name created is "tonuts dime".
# - ("donuts", "toffee"): The company name created is "tonuts doffee".
# - ("time", "donuts"): The company name created is "dime tonuts".
# - ("toffee", "donuts"): The company name created is "doffee tonuts".
# Therefore, there are a total of 6 distinct company names.
#
# The following are some examples of invalid selections:
# - ("coffee", "time"): The name "toffee" formed after swapping already exists in the original array.
# - ("time", "toffee"): Both names are still the same after swapping and exist in the original array.
# - ("coffee", "toffee"): Both names formed after swapping already exist in the original array.
#
# Constraints:
# 2 <= ideas.length <= 5 * 104
# 	1 <= ideas[i].length <= 10
# 	ideas[i] consists of lowercase English letters.
# 	All the strings in ideas are unique.
#

class Solution(object):
    def distinctNames(self, ideas):
        """
        :type ideas: List[str]
        :rtype: int
        """
        suffix_map = {}
        for idea in ideas:
            first_char = idea[0]
            suffix = idea[1:]
            if suffix not in suffix_map:
                suffix_map[suffix] = set()
            suffix_map[suffix].add(first_char)

        total_names = 0
        suffixes = list(suffix_map.keys())
        n = len(suffixes)

        for i in range(n):
            for j in range(i + 1, n):
                suffix1 = suffixes[i]
                suffix2 = suffixes[j]
                common_prefixes = suffix_map[suffix1].intersection(suffix_map[suffix2])
                count1 = len(suffix_map[suffix1]) - len(common_prefixes)
                count2 = len(suffix_map[suffix2]) - len(common_prefixes)
                total_names += count1 * count2 * 2

        return total_names