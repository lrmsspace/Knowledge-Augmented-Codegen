# Source: https://leetcode.com/problems/maximum-total-beauty-of-the-gardens/   |   Difficulty: Hard
#
# Problem Description:
# Alice is a caretaker of n gardens and she wants to plant flowers to maximize the total beauty of all her gardens.
#
# You are given a 0-indexed integer array flowers of size n, where flowers[i] is the number of flowers already planted in the ith garden. Flowers that are already planted cannot be removed. You are then given another integer newFlowers, which is the maximum number of flowers that Alice can additionally plant. You are also given the integers target, full, and partial.
#
# A garden is considered complete if it has at least target flowers. The total beauty of the gardens is then determined as the sum of the following:
#
#
# 	The number of complete gardens multiplied by full.
# 	The minimum number of flowers in any of the incomplete gardens multiplied by partial. If there are no incomplete gardens, then this value will be 0.
#
#
# Return the maximum total beauty that Alice can obtain after planting at most newFlowers flowers.
#
# Example:
# Input: flowers = [1,3,1,1], newFlowers = 7, target = 6, full = 12, partial = 1
# Output: 14
# Explanation: Alice can plant
# - 2 flowers in the 0th garden
# - 3 flowers in the 1st garden
# - 1 flower in the 2nd garden
# - 1 flower in the 3rd garden
# The gardens will then be [3,6,2,2]. She planted a total of 2 + 3 + 1 + 1 = 7 flowers.
# There is 1 garden that is complete.
# The minimum number of flowers in the incomplete gardens is 2.
# Thus, the total beauty is 1 * 12 + 2 * 1 = 12 + 2 = 14.
# No other way of planting flowers can obtain a total beauty higher than 14.
#
# Constraints:
# 1 <= flowers.length <= 105
# 	1 <= flowers[i], target <= 105
# 	1 <= newFlowers <= 1010
# 	1 <= full, partial <= 105
#

class Solution(object):
    def maximumBeauty(self, flowers, newFlowers, target, full, partial):
        """
        :type flowers: List[int]
        :type newFlowers: int
        :type target: int
        :type full: int
        :type partial: int
        :rtype: int
        """
        n = len(flowers)
        flowers.sort()
        prefix = [0] * (n + 1)
        for i in range(n):
            prefix[i + 1] = prefix[i] + flowers[i]

        def can_make(min_flower, count):
            idx = bisect.bisect_left(flowers, min_flower)
            idx = min(idx, count)
            need = min_flower * idx - prefix[idx]
            return need

        max_beauty = 0
        complete_gardens = 0

        for i in range(n, -1, -1):
            if i < n:
                newFlowers += max(0, target - flowers[i])
                complete_gardens += 1

            if newFlowers < 0:
                break

            left, right = flowers[0], target - 1
            best_min_flower = 0

            while left <= right:
                mid = (left + right) // 2
                if can_make(mid, i) <= newFlowers:
                    best_min_flower = mid
                    left = mid + 1
                else:
                    right = mid - 1

            current_beauty = complete_gardens * full + best_min_flower * partial
            max_beauty = max(max_beauty, current_beauty)

        return max_beauty