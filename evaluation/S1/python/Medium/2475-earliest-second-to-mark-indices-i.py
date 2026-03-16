# Source: https://leetcode.com/problems/earliest-second-to-mark-indices-i/   |   Difficulty: Medium
#
# Problem Description:
# You are given two 1-indexed integer arrays, nums and, changeIndices, having lengths n and m, respectively.
#
# Initially, all indices in nums are unmarked. Your task is to mark all indices in nums.
#
# In each second, s, in order from 1 to m (inclusive), you can perform one of the following operations:
#
#
# 	Choose an index i in the range [1, n] and decrement nums[i] by 1.
# 	If nums[changeIndices[s]] is equal to 0, mark the index changeIndices[s].
# 	Do nothing.
#
#
# Return an integer denoting the earliest second in the range [1, m] when all indices in nums can be marked by choosing operations optimally, or -1 if it is impossible.
#
# Example:
# Input: nums = [2,2,0], changeIndices = [2,2,2,2,3,2,2,1]
# Output: 8
# Explanation: In this example, we have 8 seconds. The following operations can be performed to mark all indices:
# Second 1: Choose index 1 and decrement nums[1] by one. nums becomes [1,2,0].
# Second 2: Choose index 1 and decrement nums[1] by one. nums becomes [0,2,0].
# Second 3: Choose index 2 and decrement nums[2] by one. nums becomes [0,1,0].
# Second 4: Choose index 2 and decrement nums[2] by one. nums becomes [0,0,0].
# Second 5: Mark the index changeIndices[5], which is marking index 3, since nums[3] is equal to 0.
# Second 6: Mark the index changeIndices[6], which is marking index 2, since nums[2] is equal to 0.
# Second 7: Do nothing.
# Second 8: Mark the index changeIndices[8], which is marking index 1, since nums[1] is equal to 0.
# Now all indices have been marked.
# It can be shown that it is not possible to mark all indices earlier than the 8th second.
# Hence, the answer is 8.
#
# Constraints:
# 1 <= n == nums.length <= 2000
# 	0 <= nums[i] <= 109
# 	1 <= m == changeIndices.length <= 2000
# 	1 <= changeIndices[i] <= n
#
# Helpful references (internal KB):
# - Binary search (interval, number, binary-search-answer, enumeration)
#   • When to use: When searching for a specific element in a sorted collection or finding an optimal value over a monotonic function within a defined range. It efficiently reduces the search space by half in each step.
#   • Idea: A search algorithm that finds the position of a target value within a sorted array or determines a value that satisfies a monotonic predicate. It operates in logarithmic time complexity, O(log N).
#   • Invariants: The potential answer always lies within the current search interval `[low, high]`.; All elements strictly less than `low` have been determined not to be the answer.
#   • Tips: Ensure the search space exhibits a monotonic property.; Carefully define the `low` and `high` bounds for the search interval.
#   • Pitfalls: Incorrectly updating `low` or `high` bounds leading to infinite loops.; Off-by-one errors in array indexing or loop conditions.
# - Prüfer code (tree, heap, simulation, greedy)
#   • When to use: Use to uniquely encode a labeled tree into a sequence of numbers or reconstruct a labeled tree from such a sequence. It's valuable for counting labeled trees and problems involving tree generation.
#   • Idea: Prüfer code uniquely encodes a labeled tree into a sequence by iteratively removing the smallest-labeled leaf and recording its neighbor. This process, which can be implemented in O(N log N) or O(N) time, continues until only two nodes remain.
#   • Invariants: The generated sequence contains `k` elements after `k` leaf removals.; All nodes with degree 1 are correctly identified as leaves.
#   • Tips: Maintain an array of node degrees for O(1) degree updates.; Use a min-priority queue or a `next_leaf` pointer for efficient smallest leaf retrieval.
#   • Pitfalls: Forgetting to update neighbor degrees after removing a leaf.; Incorrectly identifying the next smallest leaf, especially when new leaves are formed.
# - Range Minimum Query (array, sparse-table)
#   • When to use: When performing many range minimum queries on a static array, especially when query time needs to be logarithmic after initial preprocessing.
#   • Idea: A data structure that precomputes minimums for all possible ranges of power-of-two lengths, allowing O(1) query time after O(N log N) preprocessing. It efficiently answers range minimum queries on an immutable array.
#   • Invariants: For any `j`, `dp[i][j]` stores the minimum value in the segment starting at `i` with length `2^j`.; The `log_table[k]` stores `floor(log2(k))` for efficient length calculation.
#   • Tips: Precompute log values or use `std::log2` for efficient length calculations.; The `dp[i][j]` entry stores the minimum in the range `[i, i + 2^j - 1]`.
#   • Pitfalls: Does not support updates to the array elements; it's for static data only.; Higher memory consumption compared to some other range query structures.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def earliestSecondToMarkIndices(self, nums, changeIndices):
        """
        :type nums: List[int]
        :type changeIndices: List[int]
        :rtype: int
        """
        n = len(nums)
        m = len(changeIndices)
        
        def can_mark_all_by(second):
            decrements = [0] * n
            marks = [False] * n
            
            for s in range(second):
                idx = changeIndices[s] - 1
                if nums[idx] == 0:
                    marks[idx] = True
                else:
                    decrements[idx] += 1
            
            for i in range(n):
                if not marks[i]:
                    if decrements[i] < nums[i]:
                        return False
            return True
        
        left, right = 1, len(changeIndices)
        answer = -1
        
        while left <= right:
            mid = (left + right) // 2
            if can_mark_all_by(mid):
                answer = mid
                right = mid - 1
            else:
                left = mid + 1
        
        return answer