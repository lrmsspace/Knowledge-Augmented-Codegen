# Source: https://leetcode.com/problems/minimum-operations-to-make-elements-within-k-subarrays-equal/   |   Difficulty: Hard
#
# Problem Description:
# You are given an integer array nums and two integers, x and k. You can perform the following operation any number of times (including zero):
#
#
# 	Increase or decrease any element of nums by 1.
#
#
# Return the minimum number of operations needed to have at least k non-overlapping subarrays of size exactly x in nums, where all elements within each subarray are equal.
#
# Example:
# Input: nums = [5,-2,1,3,7,3,6,4,-1], x = 3, k = 2
#
# Output: 8
#
# Explanation:
#
#
# 	Use 3 operations to add 3 to nums[1] and use 2 operations to subtract 2 from nums[3]. The resulting array is [5, 1, 1, 1, 7, 3, 6, 4, -1].
# 	Use 1 operation to add 1 to nums[5] and use 2 operations to subtract 2 from nums[6]. The resulting array is [5, 1, 1, 1, 7, 4, 4, 4, -1].
# 	Now, all elements within each subarray [1, 1, 1] (from indices 1 to 3) and [4, 4, 4] (from indices 5 to 7) are equal. Since 8 total operations were used, 8 is the output.
#
# Constraints:
# 2 <= nums.length <= 105
# 	-106 <= nums[i] <= 106
# 	2 <= x <= nums.length
# 	1 <= k <= 15
# 	2 <= k * x <= nums.length
#
# Helpful references (internal KB):
# - Generating all K-combinations (array, enumeration, greedy)
#   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
#   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
#   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
#   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
#   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
# - Number of paths of fixed length / Shortest paths of fixed length (graph, simulation, counting, floyd-warshall)
#   • When to use: Use this approach when you need to count the number of paths or find the shortest path between two nodes in a graph, specifically constrained to an exact number of edges or at most a certain number of edges.
#   • Idea: This technique leverages matrix exponentiation on an adjacency matrix to find paths of a fixed length k. For problems involving paths of length up to k, the graph is modified by duplicating vertices and adding specific edges.
#   • Invariants: After p matrix multiplications, M^p[i][j] represents the count/shortest path length between i and j using exactly p edges.; The modified graph for 'at most k' paths ensures a path of length m <= k in the original graph corresponds to a path of length k+1 in the new graph.
#   • Tips: For exactly K edges, compute the K-th power of the adjacency matrix.; For at most K edges, duplicate each vertex v to v' and add edges (v, v') and (v', v') with appropriate weights (1 for counting, 0 for shortest path).
#   • Pitfalls: Naive matrix multiplication is O(N^3), leading to high complexity for large N.; Incorrectly handling edge weights (e.g., for shortest paths) can lead to wrong results.
# - Manhattan Distance (array, number, enumeration, max-window)
#   • When to use: When calculating distances on a grid where movement is restricted to cardinal directions, or when optimizing expressions involving sums of absolute differences of coordinates.
#   • Idea: Manhattan distance, or L1 distance, measures the distance between two points as the sum of the absolute differences of their Cartesian coordinates. It is commonly used to find optimal paths on a grid or to transform coordinate systems for specific optimizations, often with O(N) or O(N log N) complexity for common problems like farthest pair.
#   • Invariants: For any two points P1(x1, y1) and P2(x2, y2), the Manhattan distance is |x1-x2| + |y1-y2|.; The maximum Manhattan distance between any two points is found by considering the maximum of (max(x+y) - min(x+y)) and (max(x-y) - min(x-y)) over all points.
#   • Tips: For 2D points (x, y), Manhattan distance can be transformed by rotating coordinates: (x', y') = (x+y, x-y).; After coordinate rotation, the Manhattan distance problem often simplifies to finding min/max values of the transformed coordinates.
#   • Pitfalls: Confusing Manhattan distance with Euclidean distance (L2 distance) or Chebyshev distance (L-infinity).; Incorrectly applying coordinate rotation for problems not involving sums of absolute differences.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def minOperations(self, nums, x, k):
        """
        :type nums: List[int]
        :type x: int
        :type k: int
        :rtype: int
        """
        from collections import defaultdict
        import heapq

        n = len(nums)
        if k * x > n:
            return -1

        # Step 1: Group indices by value
        value_to_indices = defaultdict(list)
        for i, num in enumerate(nums):
            value_to_indices[num].append(i)

        # Step 2: For each value, find the minimum operations to form subarrays of size x
        min_heap = []
        for value, indices in value_to_indices.items():
            if len(indices) < x:
                continue
            
            # Calculate the cost to make a subarray of size x with this value
            costs = []
            for i in range(len(indices) - x + 1):
                cost = 0
                for j in range(x):
                    cost += abs(nums[indices[i + j]] - value)
                costs.append(cost)
            
            # Add the minimum cost for this value to the heap
            heapq.heappush(min_heap, (min(costs), value))

        # Step 3: Extract the k smallest costs from the heap
        total_cost = 0
        for _ in range(k):
            if not min_heap:
                return -1
            cost, _ = heapq.heappop(min_heap)
            total_cost += cost

        return total_cost