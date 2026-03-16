# Source: https://leetcode.com/problems/maximum-value-at-a-given-index-in-a-bounded-array/   |   Difficulty: Medium
#
# Problem Description:
# You are given three positive integers: n, index, and maxSum. You want to construct an array nums (0-indexed) that satisfies the following conditions:
#
#
# 	nums.length == n
# 	nums[i] is a positive integer where 0 <= i < n.
# 	abs(nums[i] - nums[i+1]) <= 1 where 0 <= i < n-1.
# 	The sum of all the elements of nums does not exceed maxSum.
# 	nums[index] is maximized.
#
#
# Return nums[index] of the constructed array.
#
# Note that abs(x) equals x if x >= 0, and -x otherwise.
#
# Example:
# Input: n = 4, index = 2,  maxSum = 6
# Output: 2
# Explanation: nums = [1,2,2,1] is one array that satisfies all the conditions.
# There are no arrays that satisfy all the conditions and have nums[2] == 3, so 2 is the maximum nums[2].
#
# Constraints:
# 1 <= n <= maxSum <= 109
# 	0 <= index < n
#

class Solution(object):
    def maxValue(self, n, index, maxSum):
        """
        :type n: int
        :type index: int
        :type maxSum: int
        :rtype: int
        """
        def check(mid):
            left_len = index
            right_len = n - index - 1

            left_sum = 0
            if mid - 1 >= left_len:
                left_sum = (mid - 1 + mid - left_len) * left_len // 2
            else:
                left_sum = (mid - 1) * mid // 2 + (left_len - (mid - 1))

            right_sum = 0
            if mid - 1 >= right_len:
                right_sum = (mid - 1 + mid - right_len) * right_len // 2
            else:
                right_sum = (mid - 1) * mid // 2 + (right_len - (mid - 1))

            total = left_sum + right_sum + mid
            return total <= maxSum

        low, high = 1, maxSum
        ans = 1
        while low <= high:
            mid = (low + high) // 2
            if check(mid):
                ans = mid
                low = mid + 1
            else:
                high = mid - 1

        return ans