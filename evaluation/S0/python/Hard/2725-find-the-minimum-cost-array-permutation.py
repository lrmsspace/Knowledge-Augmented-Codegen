# Source: https://leetcode.com/problems/find-the-minimum-cost-array-permutation/   |   Difficulty: Hard
#
# Problem Description:
# You are given an array nums which is a permutation of [0, 1, 2, ..., n - 1]. The score of any permutation of [0, 1, 2, ..., n - 1] named perm is defined as:
#
# score(perm) = |perm[0] - nums[perm[1]]| + |perm[1] - nums[perm[2]]| + ... + |perm[n - 1] - nums[perm[0]]|
#
# Return the permutation perm which has the minimum possible score. If multiple permutations exist with this score, return the one that is lexicographically smallest among them.
#
# Example:
# Input: nums = [1,0,2]
#
# Output: [0,1,2]
#
# Explanation:
#
#
#
# The lexicographically smallest permutation with minimum cost is [0,1,2]. The cost of this permutation is |0 - 0| + |1 - 2| + |2 - 1| = 2.
#
# Constraints:
# 2 <= n == nums.length <= 14
# 	nums is a permutation of [0, 1, 2, ..., n - 1].
#

class Solution(object):
    def findPermutation(self, nums):
        """
        :type nums: List[int]
        :rtype: List[int]
        """
        n = len(nums)
        min_score = float('inf')
        best_perm = None

        from itertools import permutations

        for perm in permutations(range(n)):
            score = sum(abs(perm[i] - nums[perm[(i + 1) % n]]) for i in range(n))
            if score < min_score or (score == min_score and (best_perm is None or perm < best_perm)):
                min_score = score
                best_perm = perm

        return list(best_perm)