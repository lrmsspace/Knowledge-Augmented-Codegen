# Source: https://leetcode.com/problems/longest-special-path-ii/   |   Difficulty: Hard
#
# Problem Description:
# You are given an undirected tree rooted at node 0, with n nodes numbered from 0 to n - 1. This is represented by a 2D array edges of length n - 1, where edges[i] = [ui, vi, lengthi] indicates an edge between nodes ui and vi with length lengthi. You are also given an integer array nums, where nums[i] represents the value at node i.
#
# A special path is defined as a downward path from an ancestor node to a descendant node in which all node values are distinct, except for at most one value that may appear twice.
#
# Return an array result of size 2, where result[0] is the length of the longest special path, and result[1] is the minimum number of nodes in all possible longest special paths.
#
# Example:
# Input: edges = [[0,1,1],[1,2,3],[1,3,1],[2,4,6],[4,7,2],[3,5,2],[3,6,5],[6,8,3]], nums = [1,1,0,3,1,2,1,1,0]
#
# Output: [9,3]
#
# Explanation:
#
# In the image below, nodes are colored by their corresponding values in nums.
#
#
#
# The longest special paths are 1 -> 2 -> 4 and 1 -> 3 -> 6 -> 8, both having a length of 9. The minimum number of nodes across all longest special paths is 3.
#
# Constraints:
# 2 <= n <= 5 * 104
# 	edges.length == n - 1
# 	edges[i].length == 3
# 	0 <= ui, vi < n
# 	1 <= lengthi <= 103
# 	nums.length == n
# 	0 <= nums[i] <= 5 * 104
# 	The input is generated such that edges represents a valid tree.
#

class Solution(object):
    def longestSpecialPath(self, edges, nums):
        """
        :type edges: List[List[int]]
        :type nums: List[int]
        :rtype: List[int]
        """
        from collections import defaultdict

        n = len(nums)
        tree = defaultdict(list)
        for u, v, length in edges:
            tree[u].append((v, length))
            tree[v].append((u, length))

        self.max_length = 0
        self.min_nodes = float('inf')

        def dfs(node, parent):
            current_value = nums[node]
            max1, max2 = 0, 0
            count1, count2 = 0, 0
            seen = {current_value: 1}

            for neighbor, length in tree[node]:
                if neighbor == parent:
                    continue
                child_length, child_count, child_seen = dfs(neighbor, node)

                overlap = any(val in seen for val in child_seen)
                if overlap:
                    if seen.get(current_value, 0) < 2 and child_seen.get(current_value, 0) < 2:
                        total_length = child_length + length
                        total_count = child_count + 1
                    else:
                        continue
                else:
                    total_length = child_length + length
                    total_count = child_count + 1

                if total_length > max1 or (total_length == max1 and total_count < count1):
                    max2, count2 = max1, count1
                    max1, count1 = total_length, total_count
                elif total_length > max2 or (total_length == max2 and total_count < count2):
                    max2, count2 = total_length, total_count

                for val, cnt in child_seen.items():
                    seen[val] = seen.get(val, 0) + cnt

            path_length = max1 + max2
            path_nodes = count1 + count2 + 1 if max2 > 0 else count1 + 1

            if path_length > self.max_length or (path_length == self.max_length and path_nodes < self.min_nodes):
                self.max_length = path_length
                self.min_nodes = path_nodes

            return max1, count1 + 1, seen

        dfs(0, -1)
        return [self.max_length, self.min_nodes]    