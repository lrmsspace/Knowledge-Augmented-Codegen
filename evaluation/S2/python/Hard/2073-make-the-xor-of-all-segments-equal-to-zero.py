# Source: https://leetcode.com/problems/make-the-xor-of-all-segments-equal-to-zero/   |   Difficulty: Hard
#
# Problem Description:
# You are given an array nums​​​ and an integer k​​​​​. The XOR of a segment [left, right] where left <= right is the XOR of all the elements with indices between left and right, inclusive: nums[left] XOR nums[left+1] XOR ... XOR nums[right].
#
# Return the minimum number of elements to change in the array such that the XOR of all segments of size k​​​​​​ is equal to zero.
#
# Example:
# Input: nums = [1,2,0,3,0], k = 1
# Output: 3
# Explanation: Modify the array from [1,2,0,3,0] to from [0,0,0,0,0].
#
# Constraints:
# 1 <= k <= nums.length <= 2000
# 	​​​​​​0 <= nums[i] < 210
#
# Helpful references (internal KB):
# - Sprague-Grundy theorem. Nim (array, number, game-theory, prefix-xor)
#   • When to use: Use when analyzing impartial games with perfect information and no draws, especially to determine winning/losing states or to find a winning strategy. It's particularly useful for games that can be reduced to Nim.
#   • Idea: The Sprague-Grundy theorem states that every impartial game under the normal play convention is equivalent to a Nim pile of a certain size (its nim-value or grundy number). For Nim, a position is a winning position if and only if the XOR sum of all pile sizes is non-zero, allowing for O(N) classification.
#   • Invariants: The XOR sum of the pile sizes (nim-sum) represents the game's current nim-value.; If the nim-sum is zero, any valid move will result in a non-zero nim-sum for the opponent.
#   • Tips: Understand the definition of impartial games and their properties.; Calculate the XOR sum of game components to determine the nim-sum.
#   • Pitfalls: Confusing impartial games with partisan games where players have different moves.; Incorrectly calculating the XOR sum, leading to wrong state classifications.
# -  
# Kth order statistic in O(N) (array, enumeration)
#   • When to use: Use when you need to find the Kth smallest or largest element in an unsorted array efficiently, without sorting the entire dataset. It's ideal for problems requiring a specific order statistic in linear average time.
#   • Idea: This algorithm finds the Kth smallest (or largest) element in an unsorted array in expected linear time, O(N), by repeatedly partitioning the array around a pivot. It is a selection algorithm, conceptually similar to quicksort but only recursing on one side.
#   • Invariants: All elements to the left of the chosen pivot are less than or equal to the pivot.; All elements to the right of the chosen pivot are greater than or equal to the pivot.
#   • Tips: Choose a good pivot (e.g., random element) to minimize the chance of worst-case performance.; The algorithm can be implemented iteratively to avoid potential recursion depth limits for very large inputs.
#   • Pitfalls: Poor pivot selection can lead to a worst-case time complexity of O(N^2).; Off-by-one errors are common when translating K (1-based) to array indices (0-based).
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
    def minChanges(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        from collections import Counter

        n = len(nums)
        max_xor = 1 << 10  # Since nums[i] < 2^10
        dp = [float('inf')] * max_xor
        dp[0] = 0

        for i in range(k):
            count = Counter()
            for j in range(i, n, k):
                count[nums[j]] += 1
            
            total = sum(count.values())
            new_dp = [float('inf')] * max_xor
            
            for x in range(max_xor):
                if dp[x] == float('inf'):
                    continue
                for num, freq in count.items():
                    new_dp[x ^ num] = min(new_dp[x ^ num], dp[x] + total - freq)
            
            dp = new_dp
        
        return dp[0]