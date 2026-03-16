# Source: https://leetcode.com/problems/most-frequent-prime/   |   Difficulty: Medium
#
# Problem Description:
# You are given a m x n 0-indexed 2D matrix mat. From every cell, you can create numbers in the following way:
#
#
# 	There could be at most 8 paths from the cells namely: east, south-east, south, south-west, west, north-west, north, and north-east.
# 	Select a path from them and append digits in this path to the number being formed by traveling in this direction.
# 	Note that numbers are generated at every step, for example, if the digits along the path are 1, 9, 1, then there will be three numbers generated along the way: 1, 19, 191.
#
#
# Return the most frequent prime number greater than 10 out of all the numbers created by traversing the matrix or -1 if no such prime number exists. If there are multiple prime numbers with the highest frequency, then return the largest among them.
#
# Note: It is invalid to change the direction during the move.
#
# Example:
# Input: mat = [[1,1],[9,9],[1,1]]
# Output: 19
# Explanation: 
# From cell (0,0) there are 3 possible directions and the numbers greater than 10 which can be created in those directions are:
# East: [11], South-East: [19], South: [19,191].
# Numbers greater than 10 created from the cell (0,1) in all possible directions are: [19,191,19,11].
# Numbers greater than 10 created from the cell (1,0) in all possible directions are: [99,91,91,91,91].
# Numbers greater than 10 created from the cell (1,1) in all possible directions are: [91,91,99,91,91].
# Numbers greater than 10 created from the cell (2,0) in all possible directions are: [11,19,191,19].
# Numbers greater than 10 created from the cell (2,1) in all possible directions are: [11,19,19,191].
# The most frequent prime number among all the created numbers is 19.
#
# Constraints:
# m == mat.length
# 	n == mat[i].length
# 	1 <= m, n <= 6
# 	1 <= mat[i][j] <= 9
#

class Solution(object):
    def mostFrequentPrime(self, mat):
        """
        :type mat: List[List[int]]
        :rtype: int
        """
        from collections import defaultdict
        
        def is_prime(num):
            if num < 2:
                return False
            for i in range(2, int(num**0.5) + 1):
                if num % i == 0:
                    return False
            return True

        directions = [
            (0, 1),   # east
            (1, 1),   # south-east
            (1, 0),   # south
            (1, -1),  # south-west
            (0, -1),  # west
            (-1, -1), # north-west
            (-1, 0),  # north
            (-1, 1)   # north-east
        ]
        
        prime_count = defaultdict(int)
        rows, cols = len(mat), len(mat[0])
        
        for r in range(rows):
            for c in range(cols):
                for dr, dc in directions:
                    num = 0
                    x, y = r, c
                    while 0 <= x < rows and 0 <= y < cols:
                        num = num * 10 + mat[x][y]
                        if num > 10 and is_prime(num):
                            prime_count[num] += 1
                        x += dr
                        y += dc
        
        if not prime_count:
            return -1
        
        max_freq = max(prime_count.values())
        candidates = [num for num, freq in prime_count.items() if freq == max_freq]
        
        return max(candidates)