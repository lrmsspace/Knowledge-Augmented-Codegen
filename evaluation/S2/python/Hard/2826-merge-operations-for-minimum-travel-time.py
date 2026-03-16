# Source: https://leetcode.com/problems/merge-operations-for-minimum-travel-time/   |   Difficulty: Hard
#
# Problem Description:
# You are given a straight road of length l km, an integer n, an integer k, and two integer arrays, position and time, each of length n.
#
# The array position lists the positions (in km) of signs in strictly increasing order (with position[0] = 0 and position[n - 1] = l).
#
# Each time[i] represents the time (in minutes) required to travel 1 km between position[i] and position[i + 1].
#
# You must perform exactly k merge operations. In one merge, you can choose any two adjacent signs at indices i and i + 1 (with i > 0 and i + 1 < n) and:
#
#
#  Update the sign at index i + 1 so that its time becomes time[i] + time[i + 1].
#  Remove the sign at index i.
#
#
# Return the minimum total travel time (in minutes) to travel from 0 to l after exactly k merges.
#
# Example:
# Input: l = 10, n = 4, k = 1, position = [0,3,8,10], time = [5,8,3,6]
#
# Output: 62
#
# Explanation:
#
#
#  
#  Merge the signs at indices 1 and 2. Remove the sign at index 1, and change the time at index 2 to 8 + 3 = 11.
#  
#  After the merge:
#  
#   position array: [0, 8, 10]
#   time array: [5, 11, 6]
#    
#  
#  
#  
#  
#   
#    
#     Segment
#     Distance (km)
#     Time per km (min)
#     Segment Travel Time (min)
#    
#   
#   
#    
#     0 → 8
#     8
#     5
#     8 × 5 = 40
#    
#    
#     8 → 10
#     2
#     11
#     2 × 11 = 22
#    
#   
#  
#  
#  Total Travel Time: 40 + 22 = 62, which is the minimum possible time after exactly 1 merge.
#
# Constraints:
# 1 <= l <= 105
#  2 <= n <= min(l + 1, 50)
#  0 <= k <= min(n - 2, 10)
#  position.length == n
#  position[0] = 0 and position[n - 1] = l
#  position is sorted in strictly increasing order.
#  time.length == n
#  1 <= time[i] <= 100​
#  1 <= sum(time) <= 100​​​​​​
#
# Helpful references (internal KB):
# - interval-dp (array, interval-dp, prefix-sum)
#   • When to use: Use when finding an optimal value (min/max) for operations on contiguous subarrays or segments, especially when subproblems are defined by intervals and can be combined from smaller adjacent intervals. Useful for problems involving circular arrangements by duplicating the array.
#   • Idea: Interval DP is a dynamic programming technique that solves problems by breaking them into subproblems defined over contiguous intervals. It typically computes solutions for smaller intervals first, then uses these to build solutions for larger intervals, often with an O(N^3) time complexity.
#   • Invariants: For any `len`, `dp[l][r]` for `r - l + 1 < len` are already computed.; `dp[l][r]` represents the optimal cost for the operation on the range `[l, r]`.
#   • Tips: Define dp[i][j] as the optimal solution for the interval [i, j].; Iterate by interval length first, then by start index.
#   • Pitfalls: Incorrectly defining base cases for intervals of length 1.; Off-by-one errors in interval boundaries or split points.
# - kth-largest-element-in-an-array (array, merge-sort)
#   • When to use: Use Merge Sort when a stable, guaranteed O(N log N) time complexity is required, especially for large datasets or linked lists where random access is costly.
#   • Idea: Merge Sort is a divide-and-conquer algorithm that recursively divides an array into halves, sorts them, and then merges the sorted halves. It has a time complexity of O(N log N) and a space complexity of O(N).
#   • Invariants: Each sub-array passed to merge is sorted.; The merge operation combines two sorted sub-arrays into a single sorted array.
#   • Tips: Implement the merge step carefully to maintain stability.; Consider iterative implementation to avoid recursion depth limits.
#   • Pitfalls: High space complexity due to auxiliary arrays.; Overhead of recursion can be significant for small inputs.
# - Number of paths of fixed length / Shortest paths of fixed length (graph, simulation, counting, floyd-warshall)
#   • When to use: Use this approach when you need to count the number of paths or find the shortest path between two nodes in a graph, specifically constrained to an exact number of edges or at most a certain number of edges.
#   • Idea: This technique leverages matrix exponentiation on an adjacency matrix to find paths of a fixed length k. For problems involving paths of length up to k, the graph is modified by duplicating vertices and adding specific edges.
#   • Invariants: After p matrix multiplications, M^p[i][j] represents the count/shortest path length between i and j using exactly p edges.; The modified graph for 'at most k' paths ensures a path of length m <= k in the original graph corresponds to a path of length k+1 in the new graph.
#   • Tips: For exactly K edges, compute the K-th power of the adjacency matrix.; For at most K edges, duplicate each vertex v to v' and add edges (v, v') and (v', v') with appropriate weights (1 for counting, 0 for shortest path).
#   • Pitfalls: Naive matrix multiplication is O(N^3), leading to high complexity for large N.; Incorrectly handling edge weights (e.g., for shortest paths) can lead to wrong results.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def minTravelTime(self, l, n, k, position, time):
        """
        :type l: int
        :type n: int
        :type k: int
        :type position: List[int]
        :type time: List[int]
        :rtype: int
        """
        # Step 1: Calculate the initial travel times for each segment
        segments = []
        for i in range(n - 1):
            distance = position[i + 1] - position[i]
            segments.append(distance * time[i])

        # Step 2: Use a min-heap to store the potential merges and their costs
        import heapq
        heap = []
        for i in range(1, n - 1):
            merge_cost = (position[i + 1] - position[i - 1]) * (time[i - 1] + time[i])
            heapq.heappush(heap, (merge_cost, i))

        # Step 3: Perform k merges
        for _ in range(k):
            merge_cost, idx = heapq.heappop(heap)

            # Update the time for the merged segment
            time[idx] += time[idx - 1]

            # Remove the merged segment from the list
            segments[idx - 1] = (position[idx + 1] - position[idx - 1]) * time[idx]

            # Update the heap with new potential merges
            if idx > 2:
                new_merge_cost = (position[idx] - position[idx - 2]) * (time[idx - 2] + time[idx])
                heapq.heappush(heap, (new_merge_cost, idx - 1))
            if idx < n - 2:
                new_merge_cost = (position[idx + 2] - position[idx]) * (time[idx] + time[idx + 1])
                heapq.heappush(heap, (new_merge_cost, idx + 1))

        # Step 4: Calculate the total travel time after all merges
        total_time = sum(segments)
        return total_time