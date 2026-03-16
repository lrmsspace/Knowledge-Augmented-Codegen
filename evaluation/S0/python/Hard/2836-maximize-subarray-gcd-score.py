# Source: https://leetcode.com/problems/maximize-subarray-gcd-score/   |   Difficulty: Hard
#
# Problem Description:
# You are given an array of positive integers nums and an integer k.
#
# You may perform at most k operations. In each operation, you can choose one element in the array and double its value. Each element can be doubled at most once.
#
# The score of a contiguous subarray is defined as the product of its length and the greatest common divisor (GCD) of all its elements.
#
# Your task is to return the maximum score that can be achieved by selecting a contiguous subarray from the modified array.
#
# Note:
#
#
#  The greatest common divisor (GCD) of an array is the largest integer that evenly divides all the array elements.
#
# Example:
# Input: nums = [2,4], k = 1
#
# Output: 8
#
# Explanation:
#
#
#  Double nums[0] to 4 using one operation. The modified array becomes [4, 4].
#  The GCD of the subarray [4, 4] is 4, and the length is 2.
#  Thus, the maximum possible score is 2 × 4 = 8.
#
# Constraints:
# 1 <= n == nums.length <= 1500
#  1 <= nums[i] <= 109
#  1 <= k <= n
#

class Solution(object):
    def maxGCDScore(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        from math import gcd
        from collections import defaultdict

        n = len(nums)
        max_score = 0

        for i in range(n):
            gcd_count = defaultdict(int)
            for j in range(i, n):
                current_gcd = nums[j] * 2 if (j - i) < k else nums[j]
                if j == i:
                    gcd_count[current_gcd] = 1
                else:
                    new_gcd_count = defaultdict(int)
                    for g, count in gcd_count.items():
                        new_g = gcd(g, current_gcd)
                        new_gcd_count[new_g] += count
                    new_gcd_count[current_gcd] += 1
                    gcd_count = new_gcd_count

                for g, count in gcd_count.items():
                    length = j - i + 1
                    if length <= k + count:
                        max_score = max(max_score, g * length)

        return max_score