# Source: https://leetcode.com/problems/recover-the-original-array/   |   Difficulty: Hard
#
# Problem Description:
# Alice had a 0-indexed array arr consisting of n positive integers. She chose an arbitrary positive integer k and created two new 0-indexed integer arrays lower and higher in the following manner:
#
#
# 	lower[i] = arr[i] - k, for every index i where 0 <= i < n
# 	higher[i] = arr[i] + k, for every index i where 0 <= i < n
#
#
# Unfortunately, Alice lost all three arrays. However, she remembers the integers that were present in the arrays lower and higher, but not the array each integer belonged to. Help Alice and recover the original array.
#
# Given an array nums consisting of 2n integers, where exactly n of the integers were present in lower and the remaining in higher, return the original array arr. In case the answer is not unique, return any valid array.
#
# Note: The test cases are generated such that there exists at least one valid array arr.
#
# Example:
# Input: nums = [2,10,6,4,8,12]
# Output: [3,7,11]
# Explanation:
# If arr = [3,7,11] and k = 1, we get lower = [2,6,10] and higher = [4,8,12].
# Combining lower and higher gives us [2,6,10,4,8,12], which is a permutation of nums.
# Another valid possibility is that arr = [5,7,9] and k = 3. In that case, lower = [2,4,6] and higher = [8,10,12].
#
# Constraints:
# 2 * n == nums.length
# 	1 <= n <= 1000
# 	1 <= nums[i] <= 109
# 	The test cases are generated such that there exists at least one valid array arr.
#
# Helpful references (internal KB):
# - bucket-sort (array, bucket-sort)
#   • When to use: Use when sorting elements with a known, uniform distribution over a specific range. It is efficient for numbers that are uniformly distributed across a range, often achieving linear time complexity.
#   • Idea: Bucket sort distributes elements into a fixed number of buckets, sorts each bucket individually, and then concatenates them. It can achieve O(N+K) average time complexity for uniformly distributed data.
#   • Invariants: After distributing elements, each element `x` is in bucket `floor(N * x)`.; After sorting buckets, every bucket `buckets[i]` contains its elements in sorted order.
#   • Tips: Choose the number of buckets appropriately based on data distribution and range.; Normalize input data to a [0, 1) range for simpler bucket indexing.
#   • Pitfalls: Poor performance with non-uniform data distribution, potentially degrading to O(N^2).; Requires extra space for the buckets, proportional to N+K.
# - Minkowski sum of convex polygons (geometry, array, two-pointers)
#   • When to use: When needing to compute the sum of two convex polygons, or efficiently determine the minimum distance or intersection between them.
#   • Idea: The Minkowski sum of two convex polygons P and Q is a new convex polygon formed by vector addition of all points from P and Q. It can be computed in O(|P| + |Q|) time by merging their edge vectors.
#   • Invariants: The current edge added to the Minkowski sum is the one with the smallest angle among the remaining edges from both polygons.; The sequence of edges in the Minkowski sum maintains convexity.
#   • Tips: The vertices of P+Q are sums of vertices of P and Q.; The edges of P+Q are the edges of P and Q, sorted by angle.
#   • Pitfalls: Incorrectly handling edge cases like collinear edges or degenerate polygons.; Floating point precision issues in geometric calculations.
# - Search the subarray with the maximum/minimum sum (array, binary-search-answer)
#   • When to use: Use when the problem asks for the minimum or maximum value that satisfies a monotonic condition.
#   • Idea: This technique finds a target value within a range by repeatedly dividing the search interval in half, based on a monotonic condition. It typically achieves O(log N) time complexity for a search space of size N.
#   • Invariants: The optimal answer always lies within the current search range [low, high].; All values less than 'low' (for min search) or greater than 'high' (for max search) are known to be non-optimal.
#   • Tips: Clearly define the search space [low, high] for the answer.; Implement a `check` function that determines if a given `mid` value is a feasible solution.
#   • Pitfalls: Incorrectly defining the search range [low, high] for the answer.; Errors in the `check` function leading to incorrect monotonicity or logic.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def recoverArray(self, nums):
        """
        :type nums: List[int]
        :rtype: List[int]
        """
        nums.sort()
        n = len(nums) // 2

        for i in range(1, len(nums)):
            k = nums[i] - nums[0]
            if k <= 0 or k % 2 != 0:
                continue

            lower, higher = [], []
            used = [False] * len(nums)

            for j in range(len(nums)):
                if used[j]:
                    continue
                lower.append(nums[j])
                used[j] = True
                target = nums[j] + k
                idx = self.binary_search(nums, target, used)
                if idx == -1:
                    break
                higher.append(nums[idx])
                used[idx] = True

            if len(lower) == n and len(higher) == n:
                return [(lower[i] + higher[i]) // 2 for i in range(n)]

        return []