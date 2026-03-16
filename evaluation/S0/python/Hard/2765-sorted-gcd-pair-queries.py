# Source: https://leetcode.com/problems/sorted-gcd-pair-queries/   |   Difficulty: Hard
#
# Problem Description:
# You are given an integer array nums of length n and an integer array queries.
#
# Let gcdPairs denote an array obtained by calculating the GCD of all possible pairs (nums[i], nums[j]), where 0 <= i < j < n, and then sorting these values in ascending order.
#
# For each query queries[i], you need to find the element at index queries[i] in gcdPairs.
#
# Return an integer array answer, where answer[i] is the value at gcdPairs[queries[i]] for each query.
#
# The term gcd(a, b) denotes the greatest common divisor of a and b.
#
# Example:
# Input: nums = [2,3,4], queries = [0,2,2]
#
# Output: [1,2,2]
#
# Explanation:
#
# gcdPairs = [gcd(nums[0], nums[1]), gcd(nums[0], nums[2]), gcd(nums[1], nums[2])] = [1, 2, 1].
#
# After sorting in ascending order, gcdPairs = [1, 1, 2].
#
# So, the answer is [gcdPairs[queries[0]], gcdPairs[queries[1]], gcdPairs[queries[2]]] = [1, 2, 2].
#
# Constraints:
# 2 <= n == nums.length <= 105
# 	1 <= nums[i] <= 5 * 104
# 	1 <= queries.length <= 105
# 	0 <= queries[i] < n * (n - 1) / 2
#

class Solution(object):
    def gcdValues(self, nums, queries):
        """
        :type nums: List[int]
        :type queries: List[int]
        :rtype: List[int]
        """
        from math import gcd
        from collections import Counter

        max_num = max(nums)
        freq = [0] * (max_num + 1)
        for num in nums:
            freq[num] += 1

        count = [0] * (max_num + 1)
        for i in range(1, max_num + 1):
            for j in range(i, max_num + 1, i):
                count[i] += freq[j]

        gcd_count = [0] * (max_num + 1)
        for i in range(max_num, 0, -1):
            total_pairs = count[i] * (count[i] - 1) // 2
            for j in range(2 * i, max_num + 1, i):
                total_pairs -= gcd_count[j]
            gcd_count[i] = total_pairs

        gcd_pairs = []
        for i in range(1, max_num + 1):
            gcd_pairs.extend([i] * gcd_count[i])

        result = [gcd_pairs[q] for q in queries]
        return result