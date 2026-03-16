# Source: https://leetcode.com/problems/maximize-value-of-function-in-a-ball-passing-game/   |   Difficulty: Hard
#
# Problem Description:
# You are given an integer array receiver of length n and an integer k. n players are playing a ball-passing game.
#
# You choose the starting player, i. The game proceeds as follows: player i passes the ball to player receiver[i], who then passes it to receiver[receiver[i]], and so on, for k passes in total. The game's score is the sum of the indices of the players who touched the ball, including repetitions, i.e. i + receiver[i] + receiver[receiver[i]] + ... + receiver(k)[i].
#
# Return the maximum possible score.
#
# Example:
# Input: receiver = [2,0,1], k = 4
#
# Output: 6
#
# Explanation:
#
# Starting with player i = 2 the initial score is 2:
#
#
# 	
# 		
# 			Pass
# 			Sender Index
# 			Receiver Index
# 			Score
# 		
# 		
# 			1
# 			2
# 			1
# 			3
# 		
# 		
# 			2
# 			1
# 			0
# 			3
# 		
# 		
# 			3
# 			0
# 			2
# 			5
# 		
# 		
# 			4
# 			2
# 			1
# 			6
#
# Constraints:
# 1 <= receiver.length == n <= 105
# 	0 <= receiver[i] <= n - 1
# 	1 <= k <= 1010
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def getMaxFunctionValue(self, receiver, k):
        """
        :type receiver: List[int]
        :type k: int
        :rtype: int
        """
        n = len(receiver)
        max_value = 0

        for start in range(n):
            visited = {}
            current = start
            total = 0
            steps = 0

            while steps < k:
                if current in visited:
                    cycle_length = steps - visited[current][0]
                    cycle_sum = total - visited[current][1]
                    remaining_steps = k - steps

                    if cycle_length > 0:
                        full_cycles = remaining_steps // cycle_length
                        total += full_cycles * cycle_sum
                        steps += full_cycles * cycle_length

                    break

                visited[current] = (steps, total)
                total += current
                current = receiver[current]
                steps += 1

            while steps < k:
                total += current
                current = receiver[current]
                steps += 1

            max_value = max(max_value, total)

        return max_value