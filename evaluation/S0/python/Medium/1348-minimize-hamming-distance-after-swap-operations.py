# Source: https://leetcode.com/problems/minimize-hamming-distance-after-swap-operations/   |   Difficulty: Medium
#
# Problem Description:
# You are given two integer arrays, source and target, both of length n. You are also given an array allowedSwaps where each allowedSwaps[i] = [ai, bi] indicates that you are allowed to swap the elements at index ai and index bi (0-indexed) of array source. Note that you can swap elements at a specific pair of indices multiple times and in any order.
#
# The Hamming distance of two arrays of the same length, source and target, is the number of positions where the elements are different. Formally, it is the number of indices i for 0 <= i <= n-1 where source[i] != target[i] (0-indexed).
#
# Return the minimum Hamming distance of source and target after performing any amount of swap operations on array source.
#
# Example:
# Input: source = [1,2,3,4], target = [2,1,4,5], allowedSwaps = [[0,1],[2,3]]
# Output: 1
# Explanation: source can be transformed the following way:
# - Swap indices 0 and 1: source = [2,1,3,4]
# - Swap indices 2 and 3: source = [2,1,4,3]
# The Hamming distance of source and target is 1 as they differ in 1 position: index 3.
#
# Constraints:
# n == source.length == target.length
# 	1 <= n <= 105
# 	1 <= source[i], target[i] <= 105
# 	0 <= allowedSwaps.length <= 105
# 	allowedSwaps[i].length == 2
# 	0 <= ai, bi <= n - 1
# 	ai != bi
#

class Solution(object):
    def minimumHammingDistance(self, source, target, allowedSwaps):
        """
        :type source: List[int]
        :type target: List[int]
        :type allowedSwaps: List[List[int]]
        :rtype: int
        """
        from collections import defaultdict, Counter
        
        parent = list(range(len(source)))
        
        def find(x):
            if parent[x] != x:
                parent[x] = find(parent[x])
            return parent[x]
        
        def union(x, y):
            rootX = find(x)
            rootY = find(y)
            if rootX != rootY:
                parent[rootY] = rootX
        
        for a, b in allowedSwaps:
            union(a, b)
        
        groups = defaultdict(list)
        for i in range(len(source)):
            root = find(i)
            groups[root].append(i)
        
        hamming_distance = 0
        
        for indices in groups.values():
            source_count = Counter()
            target_count = Counter()
            
            for i in indices:
                source_count[source[i]] += 1
                target_count[target[i]] += 1
            
            for val in source_count:
                if val in target_count:
                    matched = min(source_count[val], target_count[val])
                    source_count[val] -= matched
                    target_count[val] -= matched
            
            hamming_distance += sum(source_count.values())
        
        return hamming_distance