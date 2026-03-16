# Source: https://leetcode.com/problems/push-dominoes/   |   Difficulty: Medium
#
# Problem Description:
# There are n dominoes in a line, and we place each domino vertically upright. In the beginning, we simultaneously push some of the dominoes either to the left or to the right.
#
# After each second, each domino that is falling to the left pushes the adjacent domino on the left. Similarly, the dominoes falling to the right push their adjacent dominoes standing on the right.
#
# When a vertical domino has dominoes falling on it from both sides, it stays still due to the balance of the forces.
#
# For the purposes of this question, we will consider that a falling domino expends no additional force to a falling or already fallen domino.
#
# You are given a string dominoes representing the initial state where:
#
#
# 	dominoes[i] = 'L', if the ith domino has been pushed to the left,
# 	dominoes[i] = 'R', if the ith domino has been pushed to the right, and
# 	dominoes[i] = '.', if the ith domino has not been pushed.
#
#
# Return a string representing the final state.
#
# Example:
# Input: dominoes = "RR.L"
# Output: "RR.L"
# Explanation: The first domino expends no additional force on the second domino.
#
# Constraints:
# n == dominoes.length
# 	1 <= n <= 105
# 	dominoes[i] is either 'L', 'R', or '.'.
#

class Solution(object):
    def pushDominoes(self, dominoes):
        """
        :type dominoes: str
        :rtype: str
        """
        symbols = []
        for i, d in enumerate(dominoes):
            if d != '.':
                symbols.append((i, d))
        
        symbols = [(-1, 'L')] + symbols + [(len(dominoes), 'R')]
        res = list(dominoes)
        
        for (i, x), (j, y) in zip(symbols, symbols[1:]):
            if x == y:
                for k in range(i + 1, j):
                    res[k] = x
            elif x == 'R' and y == 'L':
                left, right = i + 1, j - 1
                while left < right:
                    res[left] = 'R'
                    res[right] = 'L'
                    left += 1
                    right -= 1
        
        return ''.join(res)