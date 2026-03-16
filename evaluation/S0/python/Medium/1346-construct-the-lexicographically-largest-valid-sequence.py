# Source: https://leetcode.com/problems/construct-the-lexicographically-largest-valid-sequence/   |   Difficulty: Medium
#
# Problem Description:
# Given an integer n, find a sequence with elements in the range [1, n] that satisfies all of the following:
#
#
# 	The integer 1 occurs once in the sequence.
# 	Each integer between 2 and n occurs twice in the sequence.
# 	For every integer i between 2 and n, the distance between the two occurrences of i is exactly i.
#
#
# The distance between two numbers on the sequence, a[i] and a[j], is the absolute difference of their indices, |j - i|.
#
# Return the lexicographically largest sequence. It is guaranteed that under the given constraints, there is always a solution. 
#
# A sequence a is lexicographically larger than a sequence b (of the same length) if in the first position where a and b differ, sequence a has a number greater than the corresponding number in b. For example, [0,1,9,0] is lexicographically larger than [0,1,5,6] because the first position they differ is at the third number, and 9 is greater than 5.
#
# Example:
# Input: n = 3
# Output: [3,1,2,3,2]
# Explanation: [2,3,2,1,3] is also a valid sequence, but [3,1,2,3,2] is the lexicographically largest valid sequence.
#
# Constraints:
# 1 <= n <= 20
#

class Solution(object):
    def constructDistancedSequence(self, n):
        """
        :type n: int
        :rtype: List[int]
        """
        size = 2 * n - 1
        res = [0] * size
        used = [False] * (n + 1)

        def backtrack(index):
            if index == size:
                return True
            if res[index] != 0:
                return backtrack(index + 1)

            for num in range(n, 1, -1):
                if not used[num]:
                    if index + num < size and res[index + num] == 0:
                        res[index] = num
                        res[index + num] = num
                        used[num] = True

                        if backtrack(index + 1):
                            return True

                        res[index] = 0
                        res[index + num] = 0
                        used[num] = False

            if not used[1]:
                res[index] = 1
                used[1] = True

                if backtrack(index + 1):
                    return True

                res[index] = 0
                used[1] = False

            return False

        backtrack(0)
        return res