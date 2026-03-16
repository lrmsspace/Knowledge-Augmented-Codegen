# Source: https://leetcode.com/problems/display-table-of-food-orders-in-a-restaurant/   |   Difficulty: Medium
#
# Problem Description:
# Given the array orders, which represents the orders that customers have done in a restaurant. More specifically orders[i]=[customerNamei,tableNumberi,foodItemi] where customerNamei is the name of the customer, tableNumberi is the table customer sit at, and foodItemi is the item customer orders.
#
# Return the restaurant's “display table”. The “display table” is a table whose row entries denote how many of each food item each table ordered. The first column is the table number and the remaining columns correspond to each food item in alphabetical order. The first row should be a header whose first column is “Table”, followed by the names of the food items. Note that the customer names are not part of the table. Additionally, the rows should be sorted in numerically increasing order.
#
# Example:
# Input: orders = [["David","3","Ceviche"],["Corina","10","Beef Burrito"],["David","3","Fried Chicken"],["Carla","5","Water"],["Carla","5","Ceviche"],["Rous","3","Ceviche"]]
# Output: [["Table","Beef Burrito","Ceviche","Fried Chicken","Water"],["3","0","2","1","0"],["5","0","1","0","1"],["10","1","0","0","0"]] 
# Explanation:
# The displaying table looks like:
# Table,Beef Burrito,Ceviche,Fried Chicken,Water
# 3    ,0           ,2      ,1            ,0
# 5    ,0           ,1      ,0            ,1
# 10   ,1           ,0      ,0            ,0
# For the table 3: David orders "Ceviche" and "Fried Chicken", and Rous orders "Ceviche".
# For the table 5: Carla orders "Water" and "Ceviche".
# For the table 10: Corina orders "Beef Burrito".
#
# Constraints:
# 1 <= orders.length <= 5 * 10^4
# 	orders[i].length == 3
# 	1 <= customerNamei.length, foodItemi.length <= 20
# 	customerNamei and foodItemi consist of lowercase and uppercase English letters and the space character.
# 	tableNumberi is a valid integer between 1 and 500.
#
# Helpful references (internal KB):
# - Generating all K-combinations (array, enumeration, greedy)
#   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
#   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
#   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
#   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
#   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
# - Knapsack Problem (array, knapsack, dp-1d, enumeration)
#   • When to use: Use when selecting items from a set to maximize or minimize a value under a capacity constraint. It's also applicable for partitioning problems with a fixed budget.
#   • Idea: This algorithm finds the maximum value that can be obtained by selecting a subset of items, each with a weight and a value, such that their total weight does not exceed a given capacity. It typically uses dynamic programming with a time complexity of O(N*W), where N is the number of items and W is the capacity.
#   • Invariants: After processing item `i`, `dp[w]` stores the maximum value for capacity `w` using items up to `i`.; For each item, `dp[w]` is updated considering either including or excluding the current item.
#   • Tips: Use a 2D DP table `dp[i][w]` for item `i` and weight `w` for clarity, then optimize to 1D.; When optimizing to 1D, iterate weights downwards to avoid using an item multiple times.
#   • Pitfalls: Incorrectly initializing the DP table can lead to wrong results or infinite loops.; Forgetting to iterate weights downwards in 1D DP can lead to items being picked multiple times (unbounded knapsack).
# - Ordered Set - Python (ds, hashing)
#   • When to use: Use when you need a collection of unique items that also preserves the order in which items were first added. It's ideal for scenarios requiring both set-like behavior and predictable iteration order.
#   • Idea: An ordered set is a data structure that stores unique elements while maintaining their insertion order. It combines the O(1) average-case time complexity for additions, deletions, and lookups of a hash set with the ordered iteration of a list.
#   • Invariants: All elements within the ordered set are unique.; The iteration order of elements matches their original insertion order.
#   • Tips: Install via `pip install ordered_set` for Python environments.; Leverage for scenarios requiring both uniqueness and order preservation.
#   • Pitfalls: Not a built-in Python type; requires external module installation.; Performance might be marginally slower than a standard `set` due to order maintenance overhead.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):

    def displayTable(self, orders):

        """

        :type orders: List[List[str]]

        :rtype: List[List[str]]

        """
        from collections import defaultdict

        table_food_count = defaultdict(lambda: defaultdict(int))
        food_items = set()
        table_numbers = set()

        for customer, table, food in orders:
            table_food_count[table][food] += 1
            food_items.add(food)
            table_numbers.add(table)

        sorted_food_items = sorted(food_items)
        sorted_table_numbers = sorted(table_numbers, key=int)

        result = []
        header = ["Table"] + sorted_food_items
        result.append(header)

        for table in sorted_table_numbers:
            row = [table]
            for food in sorted_food_items:
                row.append(str(table_food_count[table][food]))
            result.append(row)

        return result