# Source: https://leetcode.com/problems/smallest-missing-genetic-value-in-each-subtree/   |   Difficulty: Hard
#
# Problem Description:
# There is a family tree rooted at 0 consisting of n nodes numbered 0 to n - 1. You are given a 0-indexed integer array parents, where parents[i] is the parent for node i. Since node 0 is the root, parents[0] == -1.
#
# There are 105 genetic values, each represented by an integer in the inclusive range [1, 105]. You are given a 0-indexed integer array nums, where nums[i] is a distinct genetic value for node i.
#
# Return an array ans of length n where ans[i] is the smallest genetic value that is missing from the subtree rooted at node i.
#
# The subtree rooted at a node x contains node x and all of its descendant nodes.
#
# Example:
# Input: parents = [-1,0,0,2], nums = [1,2,3,4]
# Output: [5,1,1,1]
# Explanation: The answer for each subtree is calculated as follows:
# - 0: The subtree contains nodes [0,1,2,3] with values [1,2,3,4]. 5 is the smallest missing value.
# - 1: The subtree contains only node 1 with value 2. 1 is the smallest missing value.
# - 2: The subtree contains nodes [2,3] with values [3,4]. 1 is the smallest missing value.
# - 3: The subtree contains only node 3 with value 4. 1 is the smallest missing value.
#
# Constraints:
# n == parents.length == nums.length
# 	2 <= n <= 105
# 	0 <= parents[i] <= n - 1 for i != 0
# 	parents[0] == -1
# 	parents represents a valid tree.
# 	1 <= nums[i] <= 105
# 	Each nums[i] is distinct.
#

class Solution(object):
    def smallestMissingValueSubtree(self, parents, nums):
        """
        :type parents: List[int]
        :type nums: List[int]
        :rtype: List[int]
        """
        n = len(parents)
        tree = [[] for _ in range(n)]
        for i in range(1, n):
            tree[parents[i]].append(i)

        ans = [1] * n
        num_to_node = {num: i for i, num in enumerate(nums)}

        def dfs(node):
            nonlocal missing
            for child in tree[node]:
                dfs(child)
            if nums[node] == missing:
                while missing in num_to_node:
                    missing += 1

        missing = 1
        for i in range(n):
            if nums[i] == 1:
                dfs(i)
                break

        return ans