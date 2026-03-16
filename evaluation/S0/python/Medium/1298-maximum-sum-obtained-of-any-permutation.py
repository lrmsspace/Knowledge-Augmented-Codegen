# Source: https://leetcode.com/problems/maximum-sum-obtained-of-any-permutation/   |   Difficulty: Medium
#
# Problem Description:
# We have an array of integers, nums, and an array of requests where requests[i] = [starti, endi]. The ith request asks for the sum of nums[starti] + nums[starti + 1] + ... + nums[endi - 1] + nums[endi]. Both starti and endi are 0-indexed.
#
# Return the maximum total sum of all requests among all permutations of nums.
#
# Since the answer may be too large, return it modulo 109 + 7.
#
# Example:
# Input: nums = [1,2,3,4,5], requests = [[1,3],[0,1]]
# Output: 19
# Explanation: One permutation of nums is [2,1,3,4,5] with the following result: 
# requests[0] -> nums[1] + nums[2] + nums[3] = 1 + 3 + 4 = 8
# requests[1] -> nums[0] + nums[1] = 2 + 1 = 3
# Total sum: 8 + 3 = 11.
# A permutation with a higher total sum is [3,5,4,2,1] with the following result:
# requests[0] -> nums[1] + nums[2] + nums[3] = 5 + 4 + 2 = 11
# requests[1] -> nums[0] + nums[1] = 3 + 5  = 8
# Total sum: 11 + 8 = 19, which is the best that you can do.
#
# Constraints:
# n == nums.length
# 	1 <= n <= 105
# 	0 <= nums[i] <= 105
# 	1 <= requests.length <= 105
# 	requests[i].length == 2
# 	0 <= starti <= endi < n
#

class Solution(object):
    def maxSumRangeQuery(self, nums, requests):
        """
        :type nums: List[int]
        :type requests: List[List[int]]
        :rtype: int
        """
        MOD = 10**9 + 7
        n = len(nums)
        freq = [0] * (n + 1)

        for start, end in requests:
            freq[start] += 1
            freq[end + 1] -= 1

        for i in range(1, n):
            freq[i] += freq[i - 1]

        freq.pop()  # Remove the extra element used for difference array

        nums.sort()
        freq.sort()

        total_sum = 0
        for i in range(n):
            total_sum = (total_sum + nums[i] * freq[i]) % MOD

        return total_sum