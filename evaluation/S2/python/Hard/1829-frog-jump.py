# Source: https://leetcode.com/problems/frog-jump/   |   Difficulty: Hard
#
# Problem Description:
# A frog is crossing a river. The river is divided into some number of units, and at each unit, there may or may not exist a stone. The frog can jump on a stone, but it must not jump into the water.
#
# Given a list of stones positions (in units) in sorted ascending order, determine if the frog can cross the river by landing on the last stone. Initially, the frog is on the first stone and assumes the first jump must be 1 unit.
#
# If the frog's last jump was k units, its next jump must be either k - 1, k, or k + 1 units. The frog can only jump in the forward direction.
#
# Example:
# Input: stones = [0,1,3,5,6,8,12,17]
# Output: true
# Explanation: The frog can jump to the last stone by jumping 1 unit to the 2nd stone, then 2 units to the 3rd stone, then 2 units to the 4th stone, then 3 units to the 6th stone, 4 units to the 7th stone, and 5 units to the 8th stone.
#
# Constraints:
# 2 <= stones.length <= 2000
# 	0 <= stones[i] <= 231 - 1
# 	stones[0] == 0
# 	stones is sorted in a strictly increasing order.
#
# Helpful references (internal KB):
# - N/A
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def canCross(self, stones):
        """
        :type stones: List[int]
        :rtype: bool
        """
        stone_positions = set(stones)
        last_stone = stones[-1]
        jumps = {0: 0}  # position: last jump size
        
        for stone in stones:
            if stone in jumps:
                jump_size = jumps[stone]
                for next_jump in [jump_size - 1, jump_size, jump_size + 1]:
                    if next_jump > 0 and (stone + next_jump) in stone_positions:
                        jumps[stone + next_jump] = next_jump
                        if stone + next_jump == last_stone:
                            return True
        
        return False