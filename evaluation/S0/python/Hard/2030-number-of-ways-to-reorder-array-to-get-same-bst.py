# Source: https://leetcode.com/problems/number-of-ways-to-reorder-array-to-get-same-bst/   |   Difficulty: Hard
#
# Problem Description:
# Given an array nums that represents a permutation of integers from 1 to n. We are going to construct a binary search tree (BST) by inserting the elements of nums in order into an initially empty BST. Find the number of different ways to reorder nums so that the constructed BST is identical to that formed from the original array nums.
#
#
# 	For example, given nums = [2,1,3], we will have 2 as the root, 1 as a left child, and 3 as a right child. The array [2,3,1] also yields the same BST but [3,2,1] yields a different BST.
#
#
# Return the number of ways to reorder nums such that the BST formed is identical to the original BST formed from nums.
#
# Since the answer may be very large, return it modulo 109 + 7.
#
# Example:
# Input: nums = [2,1,3]
# Output: 1
# Explanation: We can reorder nums to be [2,3,1] which will yield the same BST. There are no other ways to reorder nums which will yield the same BST.
#
# Constraints:
# 1 <= nums.length <= 1000
# 	1 <= nums[i] <= nums.length
# 	All integers in nums are distinct.
#

class Solution(object):
    def numOfWays(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        MOD = 10**9 + 7
        n = len(nums)

        # Precompute binomial coefficients
        comb = [[0] * (n + 1) for _ in range(n + 1)]
        for i in range(n + 1):
            comb[i][0] = comb[i][i] = 1
            for j in range(1, i):
                comb[i][j] = (comb[i - 1][j - 1] + comb[i - 1][j]) % MOD

        def count_ways(arr):
            if len(arr) <= 2:
                return 1

            root = arr[0]
            left_subtree = [x for x in arr if x < root]
            right_subtree = [x for x in arr if x > root]

            left_ways = count_ways(left_subtree)
            right_ways = count_ways(right_subtree)

            total_ways = (comb[len(left_subtree) + len(right_subtree)][len(left_subtree)] *
                          left_ways % MOD * right_ways % MOD) % MOD
            return total_ways

        return (count_ways(nums) - 1) % MOD