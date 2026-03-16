# Source: https://leetcode.com/problems/find-in-mountain-array/   |   Difficulty: Hard
#
# Problem Description:
# (This problem is an interactive problem.)
#
# You may recall that an array arr is a mountain array if and only if:
#
#
# 	arr.length >= 3
# 	There exists some i with 0 < i < arr.length - 1 such that:
# 	
# 		arr[0] < arr[1] < ... < arr[i - 1] < arr[i]
# 		arr[i] > arr[i + 1] > ... > arr[arr.length - 1]
# 	
# 	
#
#
# Given a mountain array mountainArr, return the minimum index such that mountainArr.get(index) == target. If such an index does not exist, return -1.
#
# You cannot access the mountain array directly. You may only access the array using a MountainArray interface:
#
#
# 	MountainArray.get(k) returns the element of the array at index k (0-indexed).
# 	MountainArray.length() returns the length of the array.
#
#
# Submissions making more than 100 calls to MountainArray.get will be judged Wrong Answer. Also, any solutions that attempt to circumvent the judge will result in disqualification.
#
# Example:
# Input: mountainArr = [1,2,3,4,5,3,1], target = 3
# Output: 2
# Explanation: 3 exists in the array, at index=2 and index=5. Return the minimum index, which is 2.
#
# Constraints:
# 3 <= mountainArr.length() <= 104
# 	0 <= target <= 109
# 	0 <= mountainArr.get(index) <= 109
#
# Helpful references (internal KB):
# - Binary search (interval, number, binary-search-answer, recursion)
#   • When to use: Use when optimizing a unimodal function (finding its maximum or minimum) over a continuous interval, where direct differentiation is hard or impossible.
#   • Idea: This algorithm finds the extremum (maximum or minimum) of a unimodal function over a given interval by repeatedly narrowing the search space. It evaluates the function at two internal points to achieve logarithmic convergence.
#   • Invariants: The extremum of the unimodal function f(x) is always within the current interval [l, r].; The function f(x) remains unimodal within the current interval [l, r].
#   • Tips: Use a fixed number of iterations as a stopping criterion instead of an epsilon value for robustness against floating point errors.; For golden section search, reuse one function evaluation from the previous step to minimize expensive computations.
#   • Pitfalls: Applying this algorithm to a non-unimodal function will yield an incorrect result.; Floating point precision issues can lead to incorrect comparisons or infinite loops if `eps` is too small.
# - Binary search (interval, number, binary-search-answer, enumeration)
#   • When to use: When searching for a specific element in a sorted collection or finding an optimal value over a monotonic function within a defined range. It efficiently reduces the search space by half in each step.
#   • Idea: A search algorithm that finds the position of a target value within a sorted array or determines a value that satisfies a monotonic predicate. It operates in logarithmic time complexity, O(log N).
#   • Invariants: The potential answer always lies within the current search interval `[low, high]`.; All elements strictly less than `low` have been determined not to be the answer.
#   • Tips: Ensure the search space exhibits a monotonic property.; Carefully define the `low` and `high` bounds for the search interval.
#   • Pitfalls: Incorrectly updating `low` or `high` bounds leading to infinite loops.; Off-by-one errors in array indexing or loop conditions.
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

# """
# This is MountainArray's API interface.
# You should not implement it, or speculate about its implementation
# """
#class MountainArray(object):
#    def get(self, index):
#        """
#        :type index: int
#        :rtype int
#        """
#
#    def length(self):
#        """
#        :rtype int
#        """

class Solution(object):
    def findInMountainArray(self, target, mountainArr):
        """
        :type target: integer
        :type mountain_arr: MountainArray
        :rtype: integer
        """
        n = mountainArr.length()
        
        # Find the peak index
        def find_peak():
            left, right = 1, n - 2
            while left < right:
                mid = (left + right) // 2
                if mountainArr.get(mid) < mountainArr.get(mid + 1):
                    left = mid + 1
                else:
                    right = mid
            return left
        
        peak_index = find_peak()
        
        # Binary search in ascending part
        def binary_search_ascending(left, right):
            while left <= right:
                mid = (left + right) // 2
                val = mountainArr.get(mid)
                if val == target:
                    return mid
                elif val < target:
                    left = mid + 1
                else:
                    right = mid - 1
            return -1
        
        # Binary search in descending part
        def binary_search_descending(left, right):
            while left <= right:
                mid = (left + right) // 2
                val = mountainArr.get(mid)
                if val == target:
                    return mid
                elif val > target:
                    left = mid + 1
                else:
                    right = mid - 1
            return -1
        
        # Search in ascending part first (from start to peak)
        result = binary_search_ascending(0, peak_index)
        if result != -1:
            return result
        
        # If not found in ascending part, search in descending part (from peak to end)
        return binary_search_descending(peak_index + 1, n - 1)  