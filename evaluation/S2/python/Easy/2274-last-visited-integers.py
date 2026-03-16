# Source: https://leetcode.com/problems/last-visited-integers/   |   Difficulty: Easy
#
# Problem Description:
# Given an integer array nums where nums[i] is either a positive integer or -1. We need to find for each -1 the respective positive integer, which we call the last visited integer.
#
# To achieve this goal, let's define two empty arrays: seen and ans.
#
# Start iterating from the beginning of the array nums.
#
#
# 	If a positive integer is encountered, prepend it to the front of seen.
# 	If -1 is encountered, let k be the number of consecutive -1s seen so far (including the current -1),
# 	
# 		If k is less than or equal to the length of seen, append the k-th element of seen to ans.
# 		If k is strictly greater than the length of seen, append -1 to ans.
# 	
# 	
#
#
# Return the array ans.
#
# Example:
# Input: nums = [1,2,-1,-1,-1]
#
# Output: [2,1,-1]
#
# Explanation:
#
# Start with seen = [] and ans = [].
#
#
# 	Process nums[0]: The first element in nums is 1. We prepend it to the front of seen. Now, seen == [1].
# 	Process nums[1]: The next element is 2. We prepend it to the front of seen. Now, seen == [2, 1].
# 	Process nums[2]: The next element is -1. This is the first occurrence of -1, so k == 1. We look for the first element in seen. We append 2 to ans. Now, ans == [2].
# 	Process nums[3]: Another -1. This is the second consecutive -1, so k == 2. The second element in seen is 1, so we append 1 to ans. Now, ans == [2, 1].
# 	Process nums[4]: Another -1, the third in a row, making k = 3. However, seen only has two elements ([2, 1]). Since k is greater than the number of elements in seen, we append -1 to ans. Finally, ans == [2, 1, -1].
#
# Constraints:
# 1 <= nums.length <= 100
# 	nums[i] == -1 or 1 <= nums[i] <= 100
#
# Helpful references (internal KB):
# - Prüfer code (tree, array, simulation, two-pointers)
#   • When to use: When needing to encode a labeled tree into a unique sequence of N-2 numbers, particularly when an efficient linear-time construction is required.
#   • Idea: The Prüfer code algorithm converts a labeled tree with N vertices into a unique sequence of N-2 numbers by iteratively removing the smallest-numbered leaf and recording its neighbor. This process can be optimized to run in O(N) time.
#   • Invariants: After 'k' iterations, 'k' leaves have been removed and 'k' numbers have been added to the Prüfer code.; The current tree always contains 'N - k' vertices and 'N - k - 1' edges.
#   • Tips: Use a degree array to efficiently track vertex degrees.; Maintain a pointer to the current smallest leaf candidate for linear time.
#   • Pitfalls: Incorrectly identifying the smallest-numbered leaf after removals.; Not updating degrees correctly, leading to wrong leaf identification.
# - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
#   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
#   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
#   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
#   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
#   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
# - MEX (minimal excluded) of a sequence (array, enumeration)
#   • When to use: Use when you need to find the smallest non-negative integer that is not present in a given collection of numbers. It's often applied in problems involving game theory or combinatorial analysis.
#   • Idea: This algorithm finds the smallest non-negative integer not present in a given sequence or set. It typically involves marking present numbers and then iterating from zero to find the first unmarked number, achieving O(N) or O(N log N) complexity.
#   • Invariants: All non-negative integers less than the current candidate MEX value have been found in the input sequence.; The data structure used for presence tracking accurately reflects which non-negative integers up to a certain bound are present.
#   • Tips: Use a boolean array or hash set for efficient presence checking.; The MEX value is at most N (for N elements) if all numbers are distinct and within [0, N-1].
#   • Pitfalls: Forgetting to handle the case where all numbers from 0 to N-1 are present, meaning MEX is N.; Using an inefficient method for presence checking, leading to higher time complexity.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def lastVisitedIntegers(self, nums):
        """
        :type nums: List[int]
        :rtype: List[int]
        """
        seen = []
        ans = []

        for num in nums:
            if num != -1:
                seen.insert(0, num)  # Prepend to the front of seen
            else:
                k = len(ans) + 1  # Number of consecutive -1s seen so far
                if k <= len(seen):
                    ans.append(seen[k - 1])  # Append the k-th element of seen to ans
                else:
                    ans.append(-1)  # Append -1 to ans if k is greater than the length of seen

        return ans