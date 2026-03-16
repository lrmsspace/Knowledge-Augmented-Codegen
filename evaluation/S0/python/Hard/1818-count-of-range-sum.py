# Source: https://leetcode.com/problems/count-of-range-sum/   |   Difficulty: Hard
#
# Problem Description:
# Given an integer array nums and two integers lower and upper, return the number of range sums that lie in [lower, upper] inclusive.
#
# Range sum S(i, j) is defined as the sum of the elements in nums between indices i and j inclusive, where i <= j.
#
# Example:
# Input: nums = [-2,5,-1], lower = -2, upper = 2
# Output: 3
# Explanation: The three ranges are: [0,0], [2,2], and [0,2] and their respective sums are: -2, -1, 2.
#
# Constraints:
# 1 <= nums.length <= 105
# 	-231 <= nums[i] <= 231 - 1
# 	-105 <= lower <= upper <= 105
# 	The answer is guaranteed to fit in a 32-bit integer.
#

class Solution(object):
    def countRangeSum(self, nums, lower, upper):
        """
        :type nums: List[int]
        :type lower: int
        :type upper: int
        :rtype: int
        """
        def sort_and_count(sums, left, right):
            if right - left <= 1:
                return 0
            mid = (left + right) // 2
            count = sort_and_count(sums, left, mid) + sort_and_count(sums, mid, right)
            j = k = t = mid
            cache = []
            for i in range(left, mid):
                while k < right and sums[k] - sums[i] < lower:
                    k += 1
                while j < right and sums[j] - sums[i] <= upper:
                    j += 1
                while t < right and sums[t] < sums[i]:
                    cache.append(sums[t])
                    t += 1
                cache.append(sums[i])
                count += j - k
            while t < right:
                cache.append(sums[t])
                t += 1
            sums[left:left+len(cache)] = cache
            return count

        prefix_sums = [0]
        for num in nums:
            prefix_sums.append(prefix_sums[-1] + num)
        return sort_and_count(prefix_sums, 0, len(prefix_sums))