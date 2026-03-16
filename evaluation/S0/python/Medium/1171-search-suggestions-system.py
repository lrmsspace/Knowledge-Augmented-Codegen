# Source: https://leetcode.com/problems/search-suggestions-system/   |   Difficulty: Medium
#
# Problem Description:
# You are given an array of strings products and a string searchWord.
#
# Design a system that suggests at most three product names from products after each character of searchWord is typed. Suggested products should have common prefix with searchWord. If there are more than three products with a common prefix return the three lexicographically minimums products.
#
# Return a list of lists of the suggested products after each character of searchWord is typed.
#
# Example:
# Input: products = ["mobile","mouse","moneypot","monitor","mousepad"], searchWord = "mouse"
# Output: [["mobile","moneypot","monitor"],["mobile","moneypot","monitor"],["mouse","mousepad"],["mouse","mousepad"],["mouse","mousepad"]]
# Explanation: products sorted lexicographically = ["mobile","moneypot","monitor","mouse","mousepad"].
# After typing m and mo all products match and we show user ["mobile","moneypot","monitor"].
# After typing mou, mous and mouse the system suggests ["mouse","mousepad"].
#
# Constraints:
# 1 <= products.length <= 1000
# 	1 <= products[i].length <= 3000
# 	1 <= sum(products[i].length) <= 2 * 104
# 	All the strings of products are unique.
# 	products[i] consists of lowercase English letters.
# 	1 <= searchWord.length <= 1000
# 	searchWord consists of lowercase English letters.
#

class Solution(object):
    def suggestedProducts(self, products, searchWord):
        """
        :type products: List[str]
        :type searchWord: str
        :rtype: List[List[str]]
        """
        products.sort()
        result = []
        prefix = ""
        for char in searchWord:
            prefix += char
            matched = [product for product in products if product.startswith(prefix)]
            result.append(matched[:3])
        return result