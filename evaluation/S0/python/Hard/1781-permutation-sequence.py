# Source: https://leetcode.com/problems/permutation-sequence/   |   Difficulty: Hard
#
# Problem Description:
# The set [1, 2, 3, ..., n] contains a total of n! unique permutations.
#
# By listing and labeling all of the permutations in order, we get the following sequence for n = 3:
#
#
# 	"123"
# 	"132"
# 	"213"
# 	"231"
# 	"312"
# 	"321"
#
#
# Given n and k, return the kth permutation sequence.
#
# Example:
# Input: n = 3, k = 3
# Output: "213"
#
# Constraints:
# 1 <= n <= 9
# 	1 <= k <= n!
#

class Solution(object):
    def getPermutation(self, n, k):
        """
        :type n: int
        :type k: int
        :rtype: str
        """
        import math
        numbers = list(range(1, n + 1))
        k -= 1  # Convert k to zero-based index
        permutation = []

        for i in range(n, 0, -1):
            fact = math.factorial(i - 1)
            index = k // fact
            permutation.append(str(numbers[index]))
            numbers.pop(index)
            k %= fact

        return ''.join(permutation)