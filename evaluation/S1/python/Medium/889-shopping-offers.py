# Source: https://leetcode.com/problems/shopping-offers/   |   Difficulty: Medium
#
# Problem Description:
# In LeetCode Store, there are n items to sell. Each item has a price. However, there are some special offers, and a special offer consists of one or more different kinds of items with a sale price.
#
# You are given an integer array price where price[i] is the price of the ith item, and an integer array needs where needs[i] is the number of pieces of the ith item you want to buy.
#
# You are also given an array special where special[i] is of size n + 1 where special[i][j] is the number of pieces of the jth item in the ith offer and special[i][n] (i.e., the last integer in the array) is the price of the ith offer.
#
# Return the lowest price you have to pay for exactly certain items as given, where you could make optimal use of the special offers. You are not allowed to buy more items than you want, even if that would lower the overall price. You could use any of the special offers as many times as you want.
#
# Example:
# Input: price = [2,5], special = [[3,0,5],[1,2,10]], needs = [3,2]
# Output: 14
# Explanation: There are two kinds of items, A and B. Their prices are $2 and $5 respectively. 
# In special offer 1, you can pay $5 for 3A and 0B
# In special offer 2, you can pay $10 for 1A and 2B. 
# You need to buy 3A and 2B, so you may pay $10 for 1A and 2B (special offer #2), and $4 for 2A.
#
# Constraints:
# n == price.length == needs.length
# 	1 <= n <= 6
# 	0 <= price[i], needs[i] <= 10
# 	1 <= special.length <= 100
# 	special[i].length == n + 1
# 	0 <= special[i][j] <= 50
# 	The input is generated that at least one of special[i][j] is non-zero for 0 <= j <= n - 1.
#
# Helpful references (internal KB):
# - Range Minimum Query (array, sparse-table)
#   • When to use: When performing many range minimum queries on a static array, especially when query time needs to be logarithmic after initial preprocessing.
#   • Idea: A data structure that precomputes minimums for all possible ranges of power-of-two lengths, allowing O(1) query time after O(N log N) preprocessing. It efficiently answers range minimum queries on an immutable array.
#   • Invariants: For any `j`, `dp[i][j]` stores the minimum value in the segment starting at `i` with length `2^j`.; The `log_table[k]` stores `floor(log2(k))` for efficient length calculation.
#   • Tips: Precompute log values or use `std::log2` for efficient length calculations.; The `dp[i][j]` entry stores the minimum in the range `[i, i + 2^j - 1]`.
#   • Pitfalls: Does not support updates to the array elements; it's for static data only.; Higher memory consumption compared to some other range query structures.
# - Introduction to Dynamic Programming (array, tree, recursion, dp-1d)
#   • When to use: Use when a problem has overlapping subproblems and optimal substructure, and a natural recursive solution is inefficient due to redundant computations. It's ideal for transforming exponential recursive solutions into polynomial time.
#   • Idea: Top-down dynamic programming, or memoization, optimizes recursive solutions by storing the results of expensive function calls and returning the cached result when the same inputs occur again. This technique typically reduces time complexity from exponential to polynomial, often O(N) or O(N*M).
#   • Invariants: memo[state] contains the computed result for 'state' if memo[state] is not the sentinel value.; If memo[state] is the sentinel value, the result for 'state' has not yet been computed.
#   • Tips: Initialize the memoization table with a sentinel value (e.g., -1, null) to distinguish uncomputed states from valid zero/false results.; Use arrays for lookup tables when the state space is contiguous and small for optimal cache performance.
#   • Pitfalls: Forgetting to initialize the memoization table, leading to incorrect results or infinite loops.; Incorrectly identifying or handling base cases in the recursive function.
# - Generating all K-combinations (array, enumeration, greedy)
#   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
#   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
#   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
#   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
#   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def shoppingOffers(self, price, special, needs):
        """
        :type price: List[int]
        :type special: List[List[int]]
        :type needs: List[int]
        :rtype: int
        """
        from functools import lru_cache

        n = len(price)

        # Filter out specials that are more expensive than buying items individually
        filtered_special = []
        for offer in special:
            total_price = sum(offer[i] * price[i] for i in range(n))
            if offer[-1] < total_price:
                filtered_special.append(offer)

        @lru_cache(None)
        def dfs(current_needs):
            # Calculate the cost without any special offers
            min_cost = sum(current_needs[i] * price[i] for i in range(n))

            # Try every special offer
            for offer in filtered_special:
                new_needs = []
                for i in range(n):
                    if offer[i] > current_needs[i]:
                        break
                    new_needs.append(current_needs[i] - offer[i])
                else:
                    # If we didn't break, it means the offer can be applied
                    min_cost = min(min_cost, dfs(tuple(new_needs)) + offer[-1])

            return min_cost

        return dfs(tuple(needs))