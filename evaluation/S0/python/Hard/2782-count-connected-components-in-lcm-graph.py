# Source: https://leetcode.com/problems/count-connected-components-in-lcm-graph/   |   Difficulty: Hard
#
# Problem Description:
# You are given an array of integers nums of size n and a positive integer threshold.
#
# There is a graph consisting of n nodes with the ith node having a value of nums[i]. Two nodes i and j in the graph are connected via an undirected edge if lcm(nums[i], nums[j]) <= threshold.
#
# Return the number of connected components in this graph.
#
# A connected component is a subgraph of a graph in which there exists a path between any two vertices, and no vertex of the subgraph shares an edge with a vertex outside of the subgraph.
#
# The term lcm(a, b) denotes the least common multiple of a and b.
#
# Example:
# Input: nums = [2,4,8,3,9], threshold = 5
#
# Output: 4
#
# Explanation: 
#
#
#
#  
#
# The four connected components are (2, 4), (3), (8), (9).
#
# Constraints:
# 1 <= nums.length <= 105
# 	1 <= nums[i] <= 109
# 	All elements of nums are unique.
# 	1 <= threshold <= 2 * 105
#

class Solution(object):
    def countComponents(self, nums, threshold):
        """
        :type nums: List[int]
        :type threshold: int
        :rtype: int
        """
        parent = {}
        rank = {}
        
        def find(x):
            if parent[x] != x:
                parent[x] = find(parent[x])
            return parent[x]
        
        def union(x, y):
            rootX = find(x)
            rootY = find(y)
            if rootX != rootY:
                if rank[rootX] > rank[rootY]:
                    parent[rootY] = rootX
                elif rank[rootX] < rank[rootY]:
                    parent[rootX] = rootY
                else:
                    parent[rootY] = rootX
                    rank[rootX] += 1
        
        nums_set = set(nums)
        
        for num in nums:
            parent[num] = num
            rank[num] = 0
        
        for i in range(threshold + 1, max(nums) + 1):
            multiple = 2 * i
            while multiple <= max(nums):
                if i in nums_set and multiple in nums_set:
                    union(i, multiple)
                multiple += i
        
        components = set()
        for num in nums:
            components.add(find(num))
        
        return len(components)