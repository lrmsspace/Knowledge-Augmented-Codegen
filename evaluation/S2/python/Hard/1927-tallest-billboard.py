# Source: https://leetcode.com/problems/tallest-billboard/   |   Difficulty: Hard
#
# Problem Description:
# You are installing a billboard and want it to have the largest height. The billboard will have two steel supports, one on each side. Each steel support must be an equal height.
#
# You are given a collection of rods that can be welded together. For example, if you have rods of lengths 1, 2, and 3, you can weld them together to make a support of length 6.
#
# Return the largest possible height of your billboard installation. If you cannot support the billboard, return 0.
#
# Example:
# Input: rods = [1,2,3,6]
# Output: 6
# Explanation: We have two disjoint subsets {1,2,3} and {6}, which have the same sum = 6.
#
# Constraints:
# 1 <= rods.length <= 20
# 	1 <= rods[i] <= 1000
# 	sum(rods[i]) <= 5000
#
# Helpful references (internal KB):
# - N/A
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def tallestBillboard(self, rods):
        """
        :type rods: List[int]
        :rtype: int
        """
        from collections import defaultdict
        
        dp = {0: 0}  # difference: max height of the smaller support
        
        for rod in rods:
            new_dp = defaultdict(int, dp)
            for diff, height in dp.items():
                # Case 1: Add rod to the taller support
                new_dp[diff + rod] = max(new_dp[diff + rod], height)
                
                # Case 2: Add rod to the shorter support
                new_diff = abs(diff - rod)
                new_height = height + min(diff, rod)
                new_dp[new_diff] = max(new_dp[new_diff], new_height)
            
            dp = new_dp
        
        return dp[0]