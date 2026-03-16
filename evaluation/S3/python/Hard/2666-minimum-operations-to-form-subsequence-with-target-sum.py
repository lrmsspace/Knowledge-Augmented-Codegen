# Source: https://leetcode.com/problems/minimum-operations-to-form-subsequence-with-target-sum/   |   Difficulty: Hard
#
# Problem Description:
# You are given a 0-indexed array nums consisting of non-negative powers of 2, and an integer target.
#
# In one operation, you must apply the following changes to the array:
#
#
# 	Choose any element of the array nums[i] such that nums[i] > 1.
# 	Remove nums[i] from the array.
# 	Add two occurrences of nums[i] / 2 to the end of nums.
#
#
# Return the minimum number of operations you need to perform so that nums contains a subsequence whose elements sum to target. If it is impossible to obtain such a subsequence, return -1.
#
# A subsequence is an array that can be derived from another array by deleting some or no elements without changing the order of the remaining elements.
#
# Example:
# Input: nums = [1,2,8], target = 7
# Output: 1
# Explanation: In the first operation, we choose element nums[2]. The array becomes equal to nums = [1,2,4,4].
# At this stage, nums contains the subsequence [1,2,4] which sums up to 7.
# It can be shown that there is no shorter sequence of operations that results in a subsequnce that sums up to 7.
#
# Constraints:
# 1 <= nums.length <= 1000
# 	1 <= nums[i] <= 230
# 	nums consists only of non-negative powers of two.
# 	1 <= target < 231
#
# Helpful references (internal KB):
# - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
#   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
#   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
#   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
#   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
#   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
# - MEX (minimal excluded) of a sequence (array, enumeration)
#   • When to use: Use when you need to find the smallest non-negative integer that is not present in a given collection of numbers. It's often applied in problems involving game theory or combinatorial analysis.
#   • Idea: This algorithm finds the smallest non-negative integer not present in a given sequence or set. It typically involves marking present numbers and then iterating from zero to find the first unmarked number, achieving O(N) or O(N log N) complexity.
#   • Invariants: All non-negative integers less than the current candidate MEX value have been found in the input sequence.; The data structure used for presence tracking accurately reflects which non-negative integers up to a certain bound are present.
#   • Tips: Use a boolean array or hash set for efficient presence checking.; The MEX value is at most N (for N elements) if all numbers are distinct and within [0, N-1].
#   • Pitfalls: Forgetting to handle the case where all numbers from 0 to N-1 are present, meaning MEX is N.; Using an inefficient method for presence checking, leading to higher time complexity.
# - Non-negative Integers without Consecutive Ones (number, recursion, backtracking)
#   • When to use: Use when counting numbers within a range that satisfy a specific digit-based or bit-based pattern constraint, especially when the constraint involves adjacent digits or bits.
#   • Idea: This algorithm recursively generates binary numbers bit by bit, ensuring no two consecutive ones are formed. It prunes branches that exceed a given upper limit or violate the consecutive one constraint, effectively counting valid numbers up to N in O(log N) time.
#   • Invariants: The `sum` generated so far never exceeds the target `num`.; The `prev` boolean accurately reflects whether the last bit added was a '1'.
#   • Tips: Generate numbers bit by bit, typically from LSB or MSB, to build up valid sequences.; Maintain state about the previously placed bit to enforce the 'no consecutive ones' rule.
#   • Pitfalls: Failing to correctly handle the base cases for the recursive function.; Incorrectly managing the 'previous bit' state, leading to invalid sequences.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def minOperations(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: int
        """
        from collections import Counter
        count = Counter(nums)
        operations = 0

        for i in range(31):
            bit_mask = 1 << i
            if target & bit_mask:
                if count[bit_mask] > 0:
                    count[bit_mask] -= 1
                else:
                    j = i + 1
                    while j < 31 and count[1 << j] == 0:
                        j += 1
                    if j == 31:
                        return -1
                    while j > i:
                        count[1 << j] -= 1
                        count[1 << (j - 1)] += 2
                        operations += 1
                        j -= 1
                    count[bit_mask] -= 1

            count[bit_mask << 1] += count[bit_mask] // 2

        return operations