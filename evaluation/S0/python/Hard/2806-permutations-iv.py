# Source: https://leetcode.com/problems/permutations-iv/   |   Difficulty: Hard
#
# Problem Description:
# Given two integers, n and k, an alternating permutation is a permutation of the first n positive integers such that no two adjacent elements are both odd or both even.
#
# Return the k-th alternating permutation sorted in lexicographical order. If there are fewer than k valid alternating permutations, return an empty list.
#
# Example:
# Input: n = 4, k = 6
#
# Output: [3,4,1,2]
#
# Explanation:
#
# The lexicographically-sorted alternating permutations of [1, 2, 3, 4] are:
#
#
# 	[1, 2, 3, 4]
# 	[1, 4, 3, 2]
# 	[2, 1, 4, 3]
# 	[2, 3, 4, 1]
# 	[3, 2, 1, 4]
# 	[3, 4, 1, 2] ← 6th permutation
# 	[4, 1, 2, 3]
# 	[4, 3, 2, 1]
#
#
# Since k = 6, we return [3, 4, 1, 2].
#
# Constraints:
# 1 <= n <= 100
# 	1 <= k <= 1015
#

class Solution(object):
    def permute(self, n, k):
        """
        :type n: int
        :type k: int
        :rtype: List[int]
        """
        from math import comb

        if n == 1:
            return [1] if k == 1 else []

        half = (n + 1) // 2
        odd_nums = list(range(1, n + 1, 2))
        even_nums = list(range(2, n + 1, 2))

        def count_permutations(odds_left, evens_left, last_was_odd):
            if odds_left == 0 and evens_left == 0:
                return 1
            total = 0
            if last_was_odd and evens_left > 0:
                total += evens_left * count_permutations(odds_left, evens_left - 1, False)
            elif not last_was_odd and odds_left > 0:
                total += odds_left * count_permutations(odds_left - 1, evens_left, True)
            return total

        result = []
        odds_left, evens_left = half, n - half
        last_was_odd = None

        for _ in range(n):
            for is_odd in [True, False]:
                if is_odd and odds_left == 0:
                    continue
                if not is_odd and evens_left == 0:
                    continue

                num_count = odds_left if is_odd else evens_left
                permutations_count = num_count * count_permutations(
                    odds_left - (1 if is_odd else 0),
                    evens_left - (0 if is_odd else 1),
                    is_odd
                )

                if k <= permutations_count:
                    if is_odd:
                        result.append(odd_nums.pop(0))
                        odds_left -= 1
                    else:
                        result.append(even_nums.pop(0))
                        evens_left -= 1
                    last_was_odd = is_odd
                    break
                else:
                    k -= permutations_count

        return result