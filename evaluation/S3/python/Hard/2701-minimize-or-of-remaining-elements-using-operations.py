# Source: https://leetcode.com/problems/minimize-or-of-remaining-elements-using-operations/   |   Difficulty: Hard
#
# Problem Description:
# You are given a 0-indexed integer array nums and an integer k.
#
# In one operation, you can pick any index i of nums such that 0 <= i < nums.length - 1 and replace nums[i] and nums[i + 1] with a single occurrence of nums[i] & nums[i + 1], where & represents the bitwise AND operator.
#
# Return the minimum possible value of the bitwise OR of the remaining elements of nums after applying at most k operations.
#
# Example:
# Input: nums = [3,5,3,2,7], k = 2
# Output: 3
# Explanation: Let's do the following operations:
# 1. Replace nums[0] and nums[1] with (nums[0] & nums[1]) so that nums becomes equal to [1,3,2,7].
# 2. Replace nums[2] and nums[3] with (nums[2] & nums[3]) so that nums becomes equal to [1,3,2].
# The bitwise-or of the final array is 3.
# It can be shown that 3 is the minimum possible value of the bitwise OR of the remaining elements of nums after applying at most k operations.
#
# Constraints:
# 1 <= nums.length <= 105
# 	0 <= nums[i] < 230
# 	0 <= k < nums.length
#
# Helpful references (internal KB):
# - Non-negative Integers without Consecutive Ones (number, recursion, backtracking)
#   • When to use: Use when counting numbers within a range that satisfy a specific digit-based or bit-based pattern constraint, especially when the constraint involves adjacent digits or bits.
#   • Idea: This algorithm recursively generates binary numbers bit by bit, ensuring no two consecutive ones are formed. It prunes branches that exceed a given upper limit or violate the consecutive one constraint, effectively counting valid numbers up to N in O(log N) time.
#   • Invariants: The `sum` generated so far never exceeds the target `num`.; The `prev` boolean accurately reflects whether the last bit added was a '1'.
#   • Tips: Generate numbers bit by bit, typically from LSB or MSB, to build up valid sequences.; Maintain state about the previously placed bit to enforce the 'no consecutive ones' rule.
#   • Pitfalls: Failing to correctly handle the base cases for the recursive function.; Incorrectly managing the 'previous bit' state, leading to invalid sequences.
# - Bit manipulation (number, enumeration, simulation)
#   • When to use: When problems involve manipulating individual bits of numbers, representing sets as bitmasks, or optimizing operations on powers of two. It is also useful for certain combinatorics and dynamic programming problems.
#   • Idea: Bit manipulation involves directly operating on the binary representation of numbers using bitwise operators. This technique is often used to optimize computations, manage boolean flags efficiently, or represent subsets, typically achieving O(1) complexity for fixed-size integers.
#   • Invariants: Each bit in the mask accurately reflects the inclusion or exclusion status of its corresponding element.; Bitwise operations maintain the integrity of unaffected bits.
#   • Tips: Use (1 << k) to create a mask with the k-th bit set.; n & (n-1) clears the least significant set bit.
#   • Pitfalls: Incorrect operator precedence can lead to subtle bugs.; Mixing signed and unsigned integers in bitwise operations can yield unexpected results.
# - Submask Enumeration
#  (number, bitset, enumeration, bitmask-dp)
#   • When to use: When a problem requires iterating through all possible submasks for each given mask. This is common in bitmask dynamic programming problems where relationships between a set and its subsets are crucial.
#   • Idea: This algorithm efficiently iterates through all submasks for every mask from 0 to 2^N - 1. It has a total time complexity of O(3^N) for all masks and their submasks.
#   • Invariants: For a given `mask`, `submask` always represents a subset of `mask`.; Each `submask` is visited exactly once for its corresponding `mask`.
#   • Tips: The `submask = (submask - 1) & mask` trick is crucial for efficient iteration.; Ensure the outer loop iterates through all masks from 0 to 2^N - 1.
#   • Pitfalls: Forgetting the `& mask` part in the inner loop can lead to incorrect submasks or infinite loops.; Misunderstanding the O(3^N) total complexity, leading to Time Limit Exceeded for large N.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def minOrAfterOperations(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        from collections import Counter
        n = len(nums)
        if k == 0:
            return reduce(lambda x, y: x | y, nums)

        # Count the frequency of each number in nums
        freq = Counter(nums)

        # Sort the unique numbers in ascending order
        unique_nums = sorted(freq.keys())

        # We will try to combine the smallest numbers first to minimize the OR result
        for num in unique_nums:
            count = freq[num]
            if count > 1:
                # We can combine pairs of this number
                pairs_to_combine = min(count // 2, k)
                k -= pairs_to_combine
                freq[num] -= pairs_to_combine * 2
                freq[num & num] += pairs_to_combine  # This is just num itself

            if k == 0:
                break

        # Now we need to calculate the OR of the remaining numbers
        result = 0
        for num, count in freq.items():
            if count > 0:
                result |= num

        return result