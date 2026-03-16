# Source: https://leetcode.com/problems/sum-of-variable-length-subarrays/   |   Difficulty: Easy
#
# Problem Description:
# You are given an integer array nums of size n. For each index i where 0 <= i < n, define a subarray nums[start ... i] where start = max(0, i - nums[i]).
#
# Return the total sum of all elements from the subarray defined for each index in the array.
#
# Example:
# Input: nums = [2,3,1]
#
# Output: 11
#
# Explanation:
#
#
# 	
# 		
# 			i
# 			Subarray
# 			Sum
# 		
# 		
# 			0
# 			nums[0] = [2]
# 			2
# 		
# 		
# 			1
# 			nums[0 ... 1] = [2, 3]
# 			5
# 		
# 		
# 			2
# 			nums[1 ... 2] = [3, 1]
# 			4
# 		
# 		
# 			Total Sum
# 			 
# 			11
# 		
# 	
#
#
# The total sum is 11. Hence, 11 is the output.
#
# Constraints:
# 1 <= n == nums.length <= 100
# 	1 <= nums[i] <= 1000
#
# Helpful references (internal KB):
# - Sqrt Decomposition (array, enumeration, difference-array)
#   • When to use: Efficiently calculate sums or properties over various ranges in a static array. Useful for many range queries or when combining range updates with point queries.
#   • Idea: Prefix sums allow O(1) range sum queries after O(N) preprocessing. Difference arrays enable O(1) range updates and O(N) point queries after O(N) reconstruction.
#   • Invariants: The prefix sum array P[i] stores the sum of elements from A[0] to A[i-1].; The difference array D[i] stores A[i] - A[i-1] (for i > 0).
#   • Tips: Precompute prefix sums to answer range sum queries in constant time.; Use a difference array to apply range updates efficiently.
#   • Pitfalls: Off-by-one errors in range boundaries for prefix sums.; Forgetting to initialize the difference array correctly (e.g., diff[0] = arr[0] for 0-indexed).
# - Finding area of simple polygon in O(N) (geometry, array, enumeration, prefix-sum)
#   • When to use: When you need to calculate the area of a simple polygon given its vertices in sequential order. It efficiently handles both convex and non-convex polygons.
#   • Idea: This algorithm calculates the area of a simple polygon by summing the signed areas of trapezoids or triangles formed by its edges and a reference point/axis. It achieves O(N) time complexity.
#   • Invariants: The sum accumulates the signed area contribution of processed edges.; The current vertex and the next vertex define an edge of the polygon.
#   • Tips: Ensure vertices are provided in sequential order (clockwise or counter-clockwise).; The absolute value of the final result is the polygon's area.
#   • Pitfalls: Supplying vertices in a non-sequential or arbitrary order will yield an incorrect area.; Applying the formula to self-intersecting polygons will not give the true geometric area.
# - Sqrt Decomposition (array, enumeration, prefix-sum)
#   • When to use: Use when frequent range queries and point/range updates are needed on an array, offering a balanced O(sqrt(N)) time complexity for both operations. It's a good alternative when a segment tree is too complex or overkill.
#   • Idea: Sqrt decomposition divides an array into blocks of size approximately sqrt(N) to optimize range queries and updates. It achieves an O(sqrt(N)) time complexity for both query and update operations.
#   • Invariants: Each block maintains an up-to-date aggregate of its elements.; For any query, fully contained blocks are processed using their precomputed aggregates.
#   • Tips: Choose block size carefully, typically sqrt(N) for optimal balance.; Precompute block aggregates (sum, min, max) for efficient queries.
#   • Pitfalls: Incorrectly handling partial blocks or boundary conditions.; Off-by-one errors in block indices or element indices within blocks.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def subarraySum(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        total_sum = 0
        n = len(nums)

        for i in range(n):
            start = max(0, i - nums[i])
            total_sum += sum(nums[start:i+1])

        return total_sum