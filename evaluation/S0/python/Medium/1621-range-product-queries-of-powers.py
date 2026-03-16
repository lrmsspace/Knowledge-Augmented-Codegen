# Source: https://leetcode.com/problems/range-product-queries-of-powers/   |   Difficulty: Medium
#
# Problem Description:
# Given a positive integer n, there exists a 0-indexed array called powers, composed of the minimum number of powers of 2 that sum to n. The array is sorted in non-decreasing order, and there is only one way to form the array.
#
# You are also given a 0-indexed 2D integer array queries, where queries[i] = [lefti, righti]. Each queries[i] represents a query where you have to find the product of all powers[j] with lefti <= j <= righti.
#
# Return an array answers, equal in length to queries, where answers[i] is the answer to the ith query. Since the answer to the ith query may be too large, each answers[i] should be returned modulo 109 + 7.
#
# Example:
# Input: n = 15, queries = [[0,1],[2,2],[0,3]]
# Output: [2,4,64]
# Explanation:
# For n = 15, powers = [1,2,4,8]. It can be shown that powers cannot be a smaller size.
# Answer to 1st query: powers[0] * powers[1] = 1 * 2 = 2.
# Answer to 2nd query: powers[2] = 4.
# Answer to 3rd query: powers[0] * powers[1] * powers[2] * powers[3] = 1 * 2 * 4 * 8 = 64.
# Each answer modulo 109 + 7 yields the same answer, so [2,4,64] is returned.
#
# Constraints:
# 1 <= n <= 109
# 	1 <= queries.length <= 105
# 	0 <= starti <= endi < powers.length
#

class Solution(object):
    def productQueries(self, n, queries):
        """
        :type n: int
        :type queries: List[List[int]]
        :rtype: List[int]
        """
        MOD = 10**9 + 7
        
        # Step 1: Generate the powers array
        powers = []
        power = 1
        while n > 0:
            if n & 1:
                powers.append(power)
            power <<= 1
            n >>= 1
        
        # Step 2: Precompute prefix products modulo MOD
        prefix_products = [1]
        for p in powers:
            prefix_products.append((prefix_products[-1] * p) % MOD)
        
        # Step 3: Process each query
        results = []
        for left, right in queries:
            prod = (prefix_products[right + 1] * pow(prefix_products[left], MOD - 2, MOD)) % MOD
            results.append(prod)
        
        return results