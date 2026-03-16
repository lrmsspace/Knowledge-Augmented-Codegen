# Source: https://leetcode.com/problems/check-if-array-pairs-are-divisible-by-k/   |   Difficulty: Medium
#
# Problem Description:
# Given an array of integers arr of even length n and an integer k.
#
# We want to divide the array into exactly n / 2 pairs such that the sum of each pair is divisible by k.
#
# Return true If you can find a way to do that or false otherwise.
#
# Example:
# Input: arr = [1,2,3,4,5,10,6,7,8,9], k = 5
# Output: true
# Explanation: Pairs are (1,9),(2,8),(3,7),(4,6) and (5,10).
#
# Constraints:
# arr.length == n
# 	1 <= n <= 105
# 	n is even.
# 	-109 <= arr[i] <= 109
# 	1 <= k <= 105
#

class Solution(object):
    def canArrange(self, arr, k):
        """
        :type arr: List[int]
        :type k: int
        :rtype: bool
        """
        mod_count = [0] * k
        for num in arr:
            mod = num % k
            mod_count[mod] += 1

        if mod_count[0] % 2 != 0:
            return False

        for i in range(1, (k // 2) + 1):
            if mod_count[i] != mod_count[k - i]:
                return False

        return True