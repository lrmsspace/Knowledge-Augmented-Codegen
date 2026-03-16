# Source: https://leetcode.com/problems/find-the-maximum-length-of-valid-subsequence-ii/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer array nums and a positive integer k.
# A subsequence sub of nums with length x is called valid if it satisfies:
#
#
# 	(sub[0] + sub[1]) % k == (sub[1] + sub[2]) % k == ... == (sub[x - 2] + sub[x - 1]) % k.
#
# Return the length of the longest valid subsequence of nums.
#
# Example:
# Input: nums = [1,2,3,4,5], k = 2
#
# Output: 5
#
# Explanation:
#
# The longest valid subsequence is [1, 2, 3, 4, 5].
#
# Constraints:
# 2 <= nums.length <= 103
# 	1 <= nums[i] <= 107
# 	1 <= k <= 103
#

class Solution(object):
    def maximumLength(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        from collections import defaultdict

        dp = defaultdict(int)
        max_length = 0

        for num in nums:
            mod_value = num % k
            prev_mod = (k - mod_value) % k

            dp[mod_value] = max(dp[mod_value], dp[prev_mod] + 1)
            max_length = max(max_length, dp[mod_value])

        return max_length