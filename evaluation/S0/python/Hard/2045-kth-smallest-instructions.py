# Source: https://leetcode.com/problems/kth-smallest-instructions/   |   Difficulty: Hard
#
# Problem Description:
# Bob is standing at cell (0, 0), and he wants to reach destination: (row, column). He can only travel right and down. You are going to help Bob by providing instructions for him to reach destination.
#
# The instructions are represented as a string, where each character is either:
#
#
# 	'H', meaning move horizontally (go right), or
# 	'V', meaning move vertically (go down).
#
#
# Multiple instructions will lead Bob to destination. For example, if destination is (2, 3), both "HHHVV" and "HVHVH" are valid instructions.
#
# However, Bob is very picky. Bob has a lucky number k, and he wants the kth lexicographically smallest instructions that will lead him to destination. k is 1-indexed.
#
# Given an integer array destination and an integer k, return the kth lexicographically smallest instructions that will take Bob to destination.
#
# Example:
# Input: destination = [2,3], k = 1
# Output: "HHHVV"
# Explanation: All the instructions that reach (2, 3) in lexicographic order are as follows:
# ["HHHVV", "HHVHV", "HHVVH", "HVHHV", "HVHVH", "HVVHH", "VHHHV", "VHHVH", "VHVHH", "VVHHH"].
#
# Constraints:
# destination.length == 2
# 	1 <= row, column <= 15
# 	1 <= k <= nCr(row + column, row), where nCr(a, b) denotes a choose b​​​​​.
#

class Solution(object):
    def kthSmallestPath(self, destination, k):
        """
        :type destination: List[int]
        :type k: int
        :rtype: str
        """
        row, col = destination
        total_moves = row + col
        
        # Precompute the binomial coefficients
        comb = [[0] * (col + 1) for _ in range(total_moves + 1)]
        for i in range(total_moves + 1):
            comb[i][0] = 1
            for j in range(1, min(i, col) + 1):
                comb[i][j] = comb[i - 1][j - 1] + comb[i - 1][j]
        
        result = []
        for _ in range(total_moves):
            if col == 0:
                result.append('V')
                row -= 1
            elif row == 0:
                result.append('H')
                col -= 1
            else:
                count_h_first = comb[row + col - 1][col - 1]
                if k <= count_h_first:
                    result.append('H')
                    col -= 1
                else:
                    result.append('V')
                    k -= count_h_first
                    row -= 1
        
        return ''.join(result)