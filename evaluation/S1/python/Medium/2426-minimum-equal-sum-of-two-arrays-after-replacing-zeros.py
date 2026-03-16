# Source: https://leetcode.com/problems/minimum-equal-sum-of-two-arrays-after-replacing-zeros/   |   Difficulty: Medium
#
# Problem Description:
# You are given two arrays nums1 and nums2 consisting of positive integers.
#
# You have to replace all the 0's in both arrays with strictly positive integers such that the sum of elements of both arrays becomes equal.
#
# Return the minimum equal sum you can obtain, or -1 if it is impossible.
#
# Example:
# Input: nums1 = [3,2,0,1,0], nums2 = [6,5,0]
# Output: 12
# Explanation: We can replace 0's in the following way:
# - Replace the two 0's in nums1 with the values 2 and 4. The resulting array is nums1 = [3,2,2,1,4].
# - Replace the 0 in nums2 with the value 1. The resulting array is nums2 = [6,5,1].
# Both arrays have an equal sum of 12. It can be shown that it is the minimum sum we can obtain.
#
# Constraints:
# 1 <= nums1.length, nums2.length <= 105
# 	0 <= nums1[i], nums2[i] <= 106
#
# Helpful references (internal KB):
# - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
#   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
#   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
#   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
#   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
#   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
# - Scheduling jobs on two machines (array, greedy)
#   • When to use: Use when optimizing the order of a sequence of tasks on two machines to minimize total idle time or makespan. It is typically applied when a greedy exchange argument can prove optimality.
#   • Idea: This algorithm determines an optimal sequence for jobs on two machines by iteratively applying a greedy choice, often proven optimal via an exchange argument. It typically achieves an optimal solution in polynomial time, commonly O(N log N) or O(N^2).
#   • Invariants: The relative order of jobs already placed in the schedule is optimal.; The total idle time for the current prefix of scheduled jobs is correctly calculated.
#   • Tips: Focus on the local effect of swapping adjacent elements to derive the greedy criterion.; Identify a metric (e.g., total idle time or makespan) that changes predictably with swaps.
#   • Pitfalls: The greedy choice might not be globally optimal for problems with more than two machines.; Incorrectly defining the cost function for idle time or makespan can lead to suboptimal solutions.
# - Sqrt Decomposition (array, enumeration, difference-array)
#   • When to use: Efficiently calculate sums or properties over various ranges in a static array. Useful for many range queries or when combining range updates with point queries.
#   • Idea: Prefix sums allow O(1) range sum queries after O(N) preprocessing. Difference arrays enable O(1) range updates and O(N) point queries after O(N) reconstruction.
#   • Invariants: The prefix sum array P[i] stores the sum of elements from A[0] to A[i-1].; The difference array D[i] stores A[i] - A[i-1] (for i > 0).
#   • Tips: Precompute prefix sums to answer range sum queries in constant time.; Use a difference array to apply range updates efficiently.
#   • Pitfalls: Off-by-one errors in range boundaries for prefix sums.; Forgetting to initialize the difference array correctly (e.g., diff[0] = arr[0] for 0-indexed).
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def minSum(self, nums1, nums2):
        """
        :type nums1: List[int]
        :type nums2: List[int]
        :rtype: int
        """
        sum1 = sum(nums1)
        sum2 = sum(nums2)
        
        zero_count1 = nums1.count(0)
        zero_count2 = nums2.count(0)
        
        diff = abs(sum1 - sum2)
        
        if sum1 == sum2:
            return sum1
        
        # Ensure sum1 is the smaller one
        if sum1 > sum2:
            sum1, sum2 = sum2, sum1
            zero_count1, zero_count2 = zero_count2, zero_count1
        
        # Now sum1 < sum2
        needed_increase = sum2 - sum1
        
        max_increase_from_zeros1 = zero_count1 * 10**6
        max_decrease_from_zeros2 = zero_count2 * 10**6
        
        total_possible_adjustment = max_increase_from_zeros1 + max_decrease_from_zeros2
        
        if total_possible_adjustment < needed_increase:
            return -1
        
        # Calculate the minimum equal sum
        min_equal_sum = max(sum1 + needed_increase, sum2 - needed_increase)
        
        return min_equal_sum