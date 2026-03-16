# Source: https://leetcode.com/problems/maximum-good-subtree-score/   |   Difficulty: Hard
#
# Problem Description:
# You are given an undirected tree rooted at node 0 with n nodes numbered from 0 to n - 1. Each node i has an integer value vals[i], and its parent is given by par[i].
#
# A subset of nodes within the subtree of a node is called good if every digit from 0 to 9 appears at most once in the decimal representation of the values of the selected nodes.
#
# The score of a good subset is the sum of the values of its nodes.
#
# Define an array maxScore of length n, where maxScore[u] represents the maximum possible sum of values of a good subset of nodes that belong to the subtree rooted at node u, including u itself and all its descendants.
#
# Return the sum of all values in maxScore.
#
# Since the answer may be large, return it modulo 109 + 7.
#
# Example:
# Input: vals = [2,3], par = [-1,0]
#
# Output: 8
#
# Explanation:
#
#
#
#
# 	The subtree rooted at node 0 includes nodes {0, 1}. The subset {2, 3} is good as the digits 2 and 3 appear only once. The score of this subset is 2 + 3 = 5.
# 	The subtree rooted at node 1 includes only node {1}. The subset {3} is good. The score of this subset is 3.
# 	The maxScore array is [5, 3], and the sum of all values in maxScore is 5 + 3 = 8. Thus, the answer is 8.
#
# Constraints:
# 1 <= n == vals.length <= 500
# 	1 <= vals[i] <= 109
# 	par.length == n
# 	par[0] == -1
# 	0 <= par[i] < n for i in [1, n - 1]
# 	The input is generated such that the parent array par represents a valid tree.
#

class Solution(object):
    def goodSubtreeSum(self, vals, par):
        """
        :type vals: List[int]
        :type par: List[int]
        :rtype: int
        """
        from collections import defaultdict

        MOD = 10**9 + 7
        n = len(vals)
        tree = defaultdict(list)
        for child in range(1, n):
            parent = par[child]
            tree[parent].append(child)

        def get_digit_mask(value):
            mask = 0
            while value > 0:
                digit = value % 10
                if (mask >> digit) & 1:
                    return -1  # Duplicate digit found
                mask |= (1 << digit)
                value //= 10
            return mask

        memo = {}

        def dfs(node):
            if node in memo:
                return memo[node]

            current_mask = get_digit_mask(vals[node])
            if current_mask == -1:
                memo[node] = (0, 0)
                return memo[node]

            total_sum = vals[node]
            total_mask = current_mask

            for child in tree[node]:
                child_sum, child_mask = dfs(child)
                if child_mask != -1 and (total_mask & child_mask) == 0:
                    total_sum += child_sum
                    total_mask |= child_mask

            memo[node] = (total_sum, total_mask)
            return memo[node]

        total_good_subtree_sum = 0
        for u in range(n):
            good_sum, _ = dfs(u)
            total_good_subtree_sum = (total_good_subtree_sum + good_sum) % MOD

        return total_good_subtree_sum