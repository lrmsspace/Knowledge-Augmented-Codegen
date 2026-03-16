# Source: https://leetcode.com/problems/maximize-count-of-distinct-primes-after-split/   |   Difficulty: Hard
#
# Problem Description:
# You are given an integer array nums having length n and a 2D integer array queries where queries[i] = [idx, val].
#
# For each query:
#
#
# 	Update nums[idx] = val.
# 	Choose an integer k with 1 <= k < n to split the array into the non-empty prefix nums[0..k-1] and suffix nums[k..n-1] such that the sum of the counts of distinct prime values in each part is maximum.
#
#
# Note: The changes made to the array in one query persist into the next query.
#
# Return an array containing the result for each query, in the order they are given.
#
# Example:
# Input: nums = [2,1,3,1,2], queries = [[1,2],[3,3]]
#
# Output: [3,4]
#
# Explanation:
#
#
# 	Initially nums = [2, 1, 3, 1, 2].
# 	After 1st query, nums = [2, 2, 3, 1, 2]. Split nums into [2] and [2, 3, 1, 2]. [2] consists of 1 distinct prime and [2, 3, 1, 2] consists of 2 distinct primes. Hence, the answer for this query is 1 + 2 = 3.
# 	After 2nd query, nums = [2, 2, 3, 3, 2]. Split nums into [2, 2, 3] and [3, 2] with an answer of 2 + 2 = 4.
# 	The output is [3, 4].
#
# Constraints:
# 2 <= n == nums.length <= 5 * 104
# 	1 <= queries.length <= 5 * 104
# 	1 <= nums[i] <= 105
# 	0 <= queries[i][0] < nums.length
# 	1 <= queries[i][1] <= 105
#

class Solution(object):
    def maximumCount(self, nums, queries):
        """
        :type nums: List[int]
        :type queries: List[List[int]]
        :rtype: List[int]
        """
        # Precompute primes up to 10^5 using Sieve of Eratosthenes
        MAX_NUM = 10**5
        is_prime = [True] * (MAX_NUM + 1)
        is_prime[0] = is_prime[1] = False
        for i in range(2, int(MAX_NUM**0.5) + 1):
            if is_prime[i]:
                for j in range(i*i, MAX_NUM + 1, i):
                    is_prime[j] = False

        def count_distinct_primes(arr):
            return len(set(x for x in arr if is_prime[x]))

        results = []
        for idx, val in queries:
            nums[idx] = val
            max_count = 0
            for k in range(1, len(nums)):
                prefix_count = count_distinct_primes(nums[:k])
                suffix_count = count_distinct_primes(nums[k:])
                max_count = max(max_count, prefix_count + suffix_count)
            results.append(max_count)

        return results