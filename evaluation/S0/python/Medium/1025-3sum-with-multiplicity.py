# Source: https://leetcode.com/problems/3sum-with-multiplicity/   |   Difficulty: Medium
#
# Problem Description:
# Given an integer array arr, and an integer target, return the number of tuples i, j, k such that i < j < k and arr[i] + arr[j] + arr[k] == target.
#
# As the answer can be very large, return it modulo 109 + 7.
#
# Example:
# Input: arr = [1,1,2,2,3,3,4,4,5,5], target = 8
# Output: 20
# Explanation: 
# Enumerating by the values (arr[i], arr[j], arr[k]):
# (1, 2, 5) occurs 8 times;
# (1, 3, 4) occurs 8 times;
# (2, 2, 4) occurs 2 times;
# (2, 3, 3) occurs 2 times.
#
# Constraints:
# 3 <= arr.length <= 3000
# 	0 <= arr[i] <= 100
# 	0 <= target <= 300
#

class Solution(object):
    def threeSumMulti(self, arr, target):
        """
        :type arr: List[int]
        :type target: int
        :rtype: int
        """
        MOD = 10**9 + 7
        count = [0] * 101
        for num in arr:
            count[num] += 1

        result = 0

        for i in range(101):
            for j in range(i, 101):
                k = target - i - j
                if k < j or k > 100:
                    continue

                if i == j == k:
                    result += count[i] * (count[i] - 1) * (count[i] - 2) // 6
                elif i == j != k:
                    result += count[i] * (count[i] - 1) // 2 * count[k]
                elif i < j == k:
                    result += count[i] * count[j] * (count[j] - 1) // 2
                elif i < j < k:
                    result += count[i] * count[j] * count[k]

        return result % MOD