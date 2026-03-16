# Source: https://leetcode.com/problems/maximum-xor-score-subarray-queries/   |   Difficulty: Hard
#
# Problem Description:
# You are given an array nums of n integers, and a 2D integer array queries of size q, where queries[i] = [li, ri].
#
# For each query, you must find the maximum XOR score of any subarray of nums[li..ri].
#
# The XOR score of an array a is found by repeatedly applying the following operations on a so that only one element remains, that is the score:
#
#
# 	Simultaneously replace a[i] with a[i] XOR a[i + 1] for all indices i except the last one.
# 	Remove the last element of a.
#
#
# Return an array answer of size q where answer[i] is the answer to query i.
#
# Example:
# Input: nums = [2,8,4,32,16,1], queries = [[0,2],[1,4],[0,5]]
#
# Output: [12,60,60]
#
# Explanation:
#
# In the first query, nums[0..2] has 6 subarrays [2], [8], [4], [2, 8], [8, 4], and [2, 8, 4] each with a respective XOR score of 2, 8, 4, 10, 12, and 6. The answer for the query is 12, the largest of all XOR scores.
#
# In the second query, the subarray of nums[1..4] with the largest XOR score is nums[1..4] with a score of 60.
#
# In the third query, the subarray of nums[0..5] with the largest XOR score is nums[1..4] with a score of 60.
#
# Constraints:
# 1 <= n == nums.length <= 2000
# 	0 <= nums[i] <= 231 - 1
# 	1 <= q == queries.length <= 105
# 	queries[i].length == 2 
# 	queries[i] = [li, ri]
# 	0 <= li <= ri <= n - 1
#

class Solution(object):
    def maximumSubarrayXor(self, nums, queries):
        """
        :type nums: List[int]
        :type queries: List[List[int]]
        :rtype: List[int]
        """
        n = len(nums)
        prefix_xor = [0] * (n + 1)
        for i in range(n):
            prefix_xor[i + 1] = prefix_xor[i] ^ nums[i]

        results = []
        for l, r in queries:
            max_xor = 0
            for i in range(l, r + 1):
                for j in range(i, r + 1):
                    current_xor = prefix_xor[j + 1] ^ prefix_xor[i]
                    max_xor = max(max_xor, current_xor)
            results.append(max_xor)

        return results  