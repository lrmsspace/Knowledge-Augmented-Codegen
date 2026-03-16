# Source: https://leetcode.com/problems/create-components-with-same-value/   |   Difficulty: Hard
#
# Problem Description:
# There is an undirected tree with n nodes labeled from 0 to n - 1.
#
# You are given a 0-indexed integer array nums of length n where nums[i] represents the value of the ith node. You are also given a 2D integer array edges of length n - 1 where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the tree.
#
# You are allowed to delete some edges, splitting the tree into multiple connected components. Let the value of a component be the sum of all nums[i] for which node i is in the component.
#
# Return the maximum number of edges you can delete, such that every connected component in the tree has the same value.
#
# Example:
# Input: nums = [6,2,2,2,6], edges = [[0,1],[1,2],[1,3],[3,4]] 
# Output: 2 
# Explanation: The above figure shows how we can delete the edges [0,1] and [3,4]. The created components are nodes [0], [1,2,3] and [4]. The sum of the values in each component equals 6. It can be proven that no better deletion exists, so the answer is 2.
#
# Constraints:
# 1 <= n <= 2 * 104
# 	nums.length == n
# 	1 <= nums[i] <= 50
# 	edges.length == n - 1
# 	edges[i].length == 2
# 	0 <= edges[i][0], edges[i][1] <= n - 1
# 	edges represents a valid tree.
#

class Solution(object):
    def componentValue(self, nums, edges):
        """
        :type nums: List[int]
        :type edges: List[List[int]]
        :rtype: int
        """
        total = sum(nums)
        n = len(nums)
        
        def can_divide(target):
            from collections import defaultdict, deque
            
            graph = defaultdict(list)
            degree = [0] * n
            for u, v in edges:
                graph[u].append(v)
                graph[v].append(u)
                degree[u] += 1
                degree[v] += 1
            
            queue = deque()
            for i in range(n):
                if degree[i] == 1:
                    queue.append(i)
            
            curr_sum = nums[:]
            components = 0
            
            while queue:
                node = queue.popleft()
                
                if curr_sum[node] > target:
                    return False
                
                if curr_sum[node] == target:
                    components += 1
                
                for neighbor in graph[node]:
                    if degree[neighbor] == 0:
                        continue
                    
                    curr_sum[neighbor] += curr_sum[node]
                    degree[neighbor] -= 1
                    
                    if degree[neighbor] == 1:
                        queue.append(neighbor)
                
                degree[node] = 0
            
            return components * target == total
        
        for k in range(n, 0, -1):
            if total % k == 0:
                if can_divide(total // k):
                    return k - 1
        
        return 0