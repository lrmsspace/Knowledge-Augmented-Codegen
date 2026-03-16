# Source: https://leetcode.com/problems/sliding-subarray-beauty/   |   Difficulty: Medium
#
# Problem Description:
# Given an integer array nums containing n integers, find the beauty of each subarray of size k.
#
# The beauty of a subarray is the xth smallest integer in the subarray if it is negative, or 0 if there are fewer than x negative integers.
#
# Return an integer array containing n - k + 1 integers, which denote the beauty of the subarrays in order from the first index in the array.
#
#
# 	
# 	A subarray is a contiguous non-empty sequence of elements within an array.
#
# Example:
# Input: nums = [1,-1,-3,-2,3], k = 3, x = 2
# Output: [-1,-2,-2]
# Explanation: There are 3 subarrays with size k = 3. 
# The first subarray is [1, -1, -3] and the 2nd smallest negative integer is -1. 
# The second subarray is [-1, -3, -2] and the 2nd smallest negative integer is -2. 
# The third subarray is [-3, -2, 3] and the 2nd smallest negative integer is -2.
#
# Constraints:
# n == nums.length 
# 	1 <= n <= 105
# 	1 <= k <= n
# 	1 <= x <= k 
# 	-50 <= nums[i] <= 50
#
# Helpful references (internal KB):
# - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
#   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
#   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
#   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
#   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
#   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
# - Sqrt Decomposition (array, ds, sliding-window, two-pointers)
#   • When to use: Use when performing frequent range queries and point updates on an array, especially when a segment tree is too complex or memory-intensive, or when query types are diverse. It offers a balanced time complexity for both operations.
#   • Idea: Sqrt decomposition divides an array into blocks of size approximately sqrt(N) to optimize range queries and point updates. It achieves O(sqrt(N)) time complexity for both operations.
#   • Invariants: Each element `arr[i]` belongs to exactly one block `block[i / block_size]`.; The summary for each block `block_summary[j]` accurately reflects the state of elements within block `j`.
#   • Tips: Choose block size carefully, typically sqrt(N) for balanced performance.; Precompute block summaries (e.g., sum, min, max) for efficient queries.
#   • Pitfalls: Off-by-one errors when calculating block indices or boundaries.; Forgetting to update the block's summary after a point update.
# - Convex Hull construction (geometry, array, enumeration)
#   • When to use: Use when you need to find the smallest convex polygon that encloses a given set of points in a plane. It is fundamental for various geometric algorithms and optimization problems.
#   • Idea: Convex hull construction identifies the subset of points that form the vertices of the smallest convex polygon containing all given points. Common algorithms achieve this in O(N log N) time complexity.
#   • Invariants: The sequence of points currently forming the hull maintains a convex property.; All points considered up to the current iteration are either part of the hull or lie within the polygon defined by the hull.
#   • Tips: Sort points by X-coordinate (and Y for ties) as a common preprocessing step.; Consider algorithms like Graham Scan or Monotone Chain for efficiency.
#   • Pitfalls: Floating point precision issues can lead to incorrect orientation calculations.; Incorrectly handling collinear points can result in non-minimal hulls or errors.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def getSubarrayBeauty(self, nums, k, x):
        """
        :type nums: List[int]
        :type k: int
        :type x: int
        :rtype: List[int]
        """
        from bisect import insort, bisect_left

        n = len(nums)
        result = []
        window = []

        for i in range(n):
            # Add new element to the window
            insort(window, nums[i])

            # Remove the element that is sliding out of the window
            if i >= k:
                out_elem = nums[i - k]
                index = bisect_left(window, out_elem)
                window.pop(index)

            # Once we have a full window, calculate the beauty
            if i >= k - 1:
                neg_count = sum(1 for num in window if num < 0)
                if neg_count < x:
                    result.append(0)
                else:
                    result.append(window[x - 1])

        return result