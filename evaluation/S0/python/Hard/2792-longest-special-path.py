# Source: https://leetcode.com/problems/longest-special-path/   |   Difficulty: Hard
#
# Problem Description:
# You are given an undirected tree rooted at node 0 with n nodes numbered from 0 to n - 1, represented by a 2D array edges of length n - 1, where edges[i] = [ui, vi, lengthi] indicates an edge between nodes ui and vi with length lengthi. You are also given an integer array nums, where nums[i] represents the value at node i.
#
# A special path is defined as a downward path from an ancestor node to a descendant node such that all the values of the nodes in that path are unique.
#
# Note that a path may start and end at the same node.
#
# Return an array result of size 2, where result[0] is the length of the longest special path, and result[1] is the minimum number of nodes in all possible longest special paths.
#
# Example:
# Input: edges = [[0,1,2],[1,2,3],[1,3,5],[1,4,4],[2,5,6]], nums = [2,1,2,1,3,1]
#
# Output: [6,2]
#
# Explanation:
#
# In the image below, nodes are colored by their corresponding values in nums
#
#
#
# The longest special paths are 2 -> 5 and 0 -> 1 -> 4, both having a length of 6. The minimum number of nodes across all longest special paths is 2.
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
        
        def dfs(node, parent, seen):
            seen.add(nums[node])
            max1, max2 = 0, 0
            count1, count2 = 0, 0
            
            for neighbor, length in tree[node]:
                if neighbor == parent:
                    continue
                if nums[neighbor] not in seen:
                    path_length, path_count = dfs(neighbor, node, seen)
                    path_length += length
                    
                    if path_length > max1:
                        max2, count2 = max1, count1
                        max1, count1 = path_length, path_count
                    elif path_length > max2:
                        max2, count2 = path_length, path_count
            
            total_length = max1 + max2
            total_nodes = (count1 if max1 > 0 else 0) + (count2 if max2 > 0 else 0) + 1
            
            if total_length > self.max_length:
                self.max_length = total_length
                self.min_nodes = total_nodes
            elif total_length == self.max_length:
                self.min_nodes = min(self.min_nodes, total_nodes)
            
            seen.remove(nums[node])
            return max1, count1 + 1 if max1 > 0 else 1
        
        dfs(0, -1, set())
        return [self.max_length, self.min_nodes]