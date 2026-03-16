# Source: https://leetcode.com/problems/find-the-number-of-subsequences-with-equal-gcd/   |   Difficulty: Hard
#
# Problem Description:
# You are given an integer array nums.
#
# Your task is to find the number of pairs of non-empty subsequences (seq1, seq2) of nums that satisfy the following conditions:
#
#
# 	The subsequences seq1 and seq2 are disjoint, meaning no index of nums is common between them.
# 	The GCD of the elements of seq1 is equal to the GCD of the elements of seq2.
#
#
# Return the total number of such pairs.
#
# Since the answer may be very large, return it modulo 109 + 7.
#
# Example:
# Input: nums = [1,2,3,4]
#
# Output: 10
#
# Explanation:
#
# The subsequence pairs which have the GCD of their elements equal to 1 are:
#
#
# 	([1, 2, 3, 4], [1, 2, 3, 4])
# 	([1, 2, 3, 4], [1, 2, 3, 4])
# 	([1, 2, 3, 4], [1, 2, 3, 4])
# 	([1, 2, 3, 4], [1, 2, 3, 4])
# 	([1, 2, 3, 4], [1, 2, 3, 4])
# 	([1, 2, 3, 4], [1, 2, 3, 4])
# 	([1, 2, 3, 4], [1, 2, 3, 4])
# 	([1, 2, 3, 4], [1, 2, 3, 4])
# 	([1, 2, 3, 4], [1, 2, 3, 4])
# 	([1, 2, 3, 4], [1, 2, 3, 4])
#
# Constraints:
# 1 <= nums.length <= 200
# 	1 <= nums[i] <= 200
#

class Solution(object):
    def subsequencePairCount(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        MOD = 10**9 + 7
        max_num = max(nums)
        freq = [0] * (max_num + 1)
        
        for num in nums:
            freq[num] += 1
        
        dp = [0] * (max_num + 1)
        
        for g in range(max_num, 0, -1):
            count = 0
            for multiple in range(g, max_num + 1, g):
                count += freq[multiple]
            if count == 0:
                continue
            
            total_subseq = pow(2, count, MOD) - 1
            dp[g] = (total_subseq * total_subseq) % MOD
            
            for multiple in range(2 * g, max_num + 1, g):
                dp[g] = (dp[g] - dp[multiple]) % MOD
        
        return dp[1]